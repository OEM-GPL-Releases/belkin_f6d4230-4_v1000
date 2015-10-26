/*
 * This is a module which is used for rejecting packets.
 * Added support for customized reject packets (Jozsef Kadlecsik).
 * Added support for ICMP type-3-code-13 (Maciej Soltysiak). [RFC 1812]
 */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <net/icmp.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/route.h>
#include <net/dst.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_REJECT.h>
#ifdef CONFIG_BRIDGE_NETFILTER
#include <linux/netfilter_bridge.h>
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("iptables REJECT target module");

#if 0
#define DEBUGP printk
#else
#define DEBUGP(format, args...)
#endif

#ifdef _SC_BUILD_
#define BLKPAGE_DEF "HTTP/1.0 200 OK\r\nServer: Router\r\nConten-Type:text/html\r\n\r\n<html><BODY  onLoad=\"window.location.href = 'http://networking.belkin.com/update/files/F5D8888-4/v1/WW/version.html'\"></body></html>"
#endif

static inline struct rtable *route_reverse(struct sk_buff *skb, int hook)
{
	struct iphdr *iph = skb->nh.iph;
	struct dst_entry *odst;
	struct flowi fl = {};
	struct rtable *rt;

	/* We don't require ip forwarding to be enabled to be able to
	 * send a RST reply for bridged traffic. */
	if (hook != NF_IP_FORWARD
#ifdef CONFIG_BRIDGE_NETFILTER
	    || (skb->nf_bridge && skb->nf_bridge->mask & BRNF_BRIDGED)
#endif
	   ) {
		fl.nl_u.ip4_u.daddr = iph->saddr;
		if (hook == NF_IP_LOCAL_IN)
			fl.nl_u.ip4_u.saddr = iph->daddr;
		fl.nl_u.ip4_u.tos = RT_TOS(iph->tos);

		if (ip_route_output_key(&rt, &fl) != 0)
			return NULL;
	} else {
		/* non-local src, find valid iif to satisfy
		 * rp-filter when calling ip_route_input. */
		fl.nl_u.ip4_u.daddr = iph->daddr;
		if (ip_route_output_key(&rt, &fl) != 0)
			return NULL;

		odst = skb->dst;
		if (ip_route_input(skb, iph->saddr, iph->daddr,
		                   RT_TOS(iph->tos), rt->u.dst.dev) != 0) {
			dst_release(&rt->u.dst);
			return NULL;
		}
		dst_release(&rt->u.dst);
		rt = (struct rtable *)skb->dst;
		skb->dst = odst;
	}

	if (rt->u.dst.error) {
		dst_release(&rt->u.dst);
		rt = NULL;
	}

	return rt;
}

#ifdef _SC_BUILD_
#define HH_DATA_MOD     16
#define HH_DATA_OFF(__len) \
        (HH_DATA_MOD - ((__len) & (HH_DATA_MOD - 1)))
#define HH_DATA_ALIGN(__len) \
	        (((__len)+(HH_DATA_MOD-1))&~(HH_DATA_MOD - 1))

/* Stolen from ip_finish_output2 */
static void ip_direct_send(struct sk_buff *skb)
{
	struct dst_entry *dst = skb->dst;
	struct hh_cache *hh = dst->hh;

	if (hh) {
		int hh_alen;

		read_lock_bh(&hh->hh_lock);
		hh_alen = HH_DATA_ALIGN(hh->hh_len);
  		memcpy(skb->data - hh_alen, hh->hh_data, hh_alen);
		read_unlock_bh(&hh->hh_lock);
	        skb_push(skb, hh->hh_len);
		hh->hh_output(skb);
	} else if (dst->neighbour)
		dst->neighbour->output(skb);
	else {
		//printk(KERN_DEBUG "khm in MIRROR\n");
		kfree_skb(skb);
	}
}

/* Send BLOCK reply */
static void send_block(struct sk_buff *oldskb, int hook)
{
	struct sk_buff *nskb;
	struct iphdr *iph = oldskb->nh.iph;
	struct tcphdr _otcph, *oth, *tcph;
	struct rtable *rt;
	u_int16_t tmp_port;
	u_int32_t tmp_addr;
	unsigned int tcplen;
	//int needs_ack;
	int hh_len;
    ///////
    char *http_data=NULL;
	int diff=0;
	char blockpage[1024]= BLKPAGE_DEF;
	int len;
    //////

	/* IP header checks: fragment. */
	if (oldskb->nh.iph->frag_off & htons(IP_OFFSET))
		return;

	oth = skb_header_pointer(oldskb, oldskb->nh.iph->ihl * 4,
				 sizeof(_otcph), &_otcph);
	if (oth == NULL)
 		return;

	/* No RST for RST. */
	//if (oth->rst)
	//	return;

	/* Check checksum */
	tcplen = oldskb->len - iph->ihl * 4;
	if (((hook != NF_IP_LOCAL_IN && oldskb->ip_summed != CHECKSUM_PARTIAL) ||
	     (hook == NF_IP_LOCAL_IN &&
	      oldskb->ip_summed != CHECKSUM_UNNECESSARY)) &&
	    csum_tcpudp_magic(iph->saddr, iph->daddr, tcplen, IPPROTO_TCP,
	                      oldskb->ip_summed == CHECKSUM_PARTIAL ? oldskb->csum :
	                      skb_checksum(oldskb, iph->ihl * 4, tcplen, 0)))
		return;

    ///////
    	len = strlen(blockpage);
    /////////
    
	if ((rt = route_reverse(oldskb, hook)) == NULL)
		return;

	hh_len = LL_RESERVED_SPACE(rt->u.dst.dev);

	/* We need a linear, writeable skb.  We also need to expand
	   headroom in case hh_len of incoming interface < hh_len of
	   outgoing interface */
	nskb = skb_copy_expand(oldskb, hh_len, skb_tailroom(oldskb),
			       GFP_ATOMIC);
	if (!nskb) {
		dst_release(&rt->u.dst);
		return;
	}

	dst_release(nskb->dst);
	nskb->dst = &rt->u.dst;

	/* This packet will not be the same as the other: clear nf fields */
	nf_reset(nskb);
	nskb->mark = 0;
#ifdef CONFIG_BRIDGE_NETFILTER
	nf_bridge_put(nskb->nf_bridge);
	nskb->nf_bridge = NULL;
#endif

	tcph = (struct tcphdr *)((u_int32_t*)nskb->nh.iph + nskb->nh.iph->ihl);

	/* Swap source and dest */
	tmp_addr = nskb->nh.iph->saddr;
	nskb->nh.iph->saddr = nskb->nh.iph->daddr;
	nskb->nh.iph->daddr = tmp_addr;
	tmp_port = tcph->source;
	tcph->source = tcph->dest;
	tcph->dest = tmp_port;

	/* Truncate to length (no data) */
	tcph->doff = sizeof(struct tcphdr)/4;
	skb_trim(nskb, nskb->nh.iph->ihl*4 + sizeof(struct tcphdr));
	
	//////////
	http_data=skb_put(nskb, len);	
	strcpy(http_data,blockpage);	
	
	//ip_options_echo(blockpage, nskb);
    ///////////
	nskb->nh.iph->tot_len = htons(nskb->len);

	//if (tcph->ack) {
	//	needs_ack = 0;
		tcph->seq = oth->ack_seq;
	//	tcph->ack_seq = 0;
	//} else {
	//	needs_ack = 1;
		tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin
				      + oldskb->len - oldskb->nh.iph->ihl*4
				      - (oth->doff<<2));
		//tcph->seq = 0;
	//}

	/* Reset flags */
	((u_int8_t *)tcph)[13] = 0;
	//tcph->rst = 1;
	//tcph->ack = needs_ack;
    //////////////
    	tcph->fin = 1;
	tcph->psh = 1;
	tcph->ack = 1;
	tcph->rst = 0;
    //////////
	tcph->window = 0;
	tcph->urg_ptr = 0;

	/* Adjust TCP checksum */
	tcph->check = 0;
	
	nskb->csum = csum_partial((char *)tcph + tcph->doff*4,
			len, 0);


	tcph->check = tcp_v4_check(sizeof(struct tcphdr) + len,
				   nskb->nh.iph->saddr,
				   nskb->nh.iph->daddr,
				   csum_partial((char *)tcph,
						sizeof(struct tcphdr), nskb->csum));

	/* Adjust IP TTL, DF */
	nskb->nh.iph->ttl = MAXTTL;
	/* Set DF, id = 0 */
	nskb->nh.iph->frag_off = htons(IP_DF);
	nskb->nh.iph->id = 0;

	/* Adjust IP checksum */
	nskb->nh.iph->check = 0;
	nskb->nh.iph->check = ip_fast_csum((unsigned char *)nskb->nh.iph, 
					   nskb->nh.iph->ihl);

	ip_direct_send(nskb);

	return;

 free_nskb:
	kfree_skb(nskb);
}
#endif // _SC_BUILD_

/* Send RST reply */
static void send_reset(struct sk_buff *oldskb, int hook)
{
	struct sk_buff *nskb;
	struct iphdr *iph = oldskb->nh.iph;
	struct tcphdr _otcph, *oth, *tcph;
	__be16 tmp_port;
	__be32 tmp_addr;
	int needs_ack;
	unsigned int addr_type;

	/* IP header checks: fragment. */
	if (oldskb->nh.iph->frag_off & htons(IP_OFFSET))
		return;

	oth = skb_header_pointer(oldskb, oldskb->nh.iph->ihl * 4,
				 sizeof(_otcph), &_otcph);
	if (oth == NULL)
		return;

	/* No RST for RST. */
	if (oth->rst)
		return;

	/* Check checksum */
	if (nf_ip_checksum(oldskb, hook, iph->ihl * 4, IPPROTO_TCP))
		return;

	/* We need a linear, writeable skb.  We also need to expand
	   headroom in case hh_len of incoming interface < hh_len of
	   outgoing interface */
	nskb = skb_copy_expand(oldskb, LL_MAX_HEADER, skb_tailroom(oldskb),
			       GFP_ATOMIC);
	if (!nskb)
		return;

	/* This packet will not be the same as the other: clear nf fields */
	nf_reset(nskb);
	nskb->mark = 0;
	skb_init_secmark(nskb);

	skb_shinfo(nskb)->gso_size = 0;
	skb_shinfo(nskb)->gso_segs = 0;
	skb_shinfo(nskb)->gso_type = 0;

	tcph = (struct tcphdr *)((u_int32_t*)nskb->nh.iph + nskb->nh.iph->ihl);

	/* Swap source and dest */
	tmp_addr = nskb->nh.iph->saddr;
	nskb->nh.iph->saddr = nskb->nh.iph->daddr;
	nskb->nh.iph->daddr = tmp_addr;
	tmp_port = tcph->source;
	tcph->source = tcph->dest;
	tcph->dest = tmp_port;

	/* Truncate to length (no data) */
	tcph->doff = sizeof(struct tcphdr)/4;
	skb_trim(nskb, nskb->nh.iph->ihl*4 + sizeof(struct tcphdr));
	nskb->nh.iph->tot_len = htons(nskb->len);

	if (tcph->ack) {
		needs_ack = 0;
		tcph->seq = oth->ack_seq;
		tcph->ack_seq = 0;
	} else {
		needs_ack = 1;
		tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin
				      + oldskb->len - oldskb->nh.iph->ihl*4
				      - (oth->doff<<2));
		tcph->seq = 0;
	}

	/* Reset flags */
	((u_int8_t *)tcph)[13] = 0;
	tcph->rst = 1;
	tcph->ack = needs_ack;

	tcph->window = 0;
	tcph->urg_ptr = 0;

	/* Adjust TCP checksum */
	tcph->check = 0;
	tcph->check = tcp_v4_check(sizeof(struct tcphdr),
				   nskb->nh.iph->saddr,
				   nskb->nh.iph->daddr,
				   csum_partial((char *)tcph,
						sizeof(struct tcphdr), 0));

	/* Set DF, id = 0 */
	nskb->nh.iph->frag_off = htons(IP_DF);
	nskb->nh.iph->id = 0;

	addr_type = RTN_UNSPEC;
	if (hook != NF_IP_FORWARD
#ifdef CONFIG_BRIDGE_NETFILTER
	    || (nskb->nf_bridge && nskb->nf_bridge->mask & BRNF_BRIDGED)
#endif
	   )
		addr_type = RTN_LOCAL;

	if (ip_route_me_harder(&nskb, addr_type))
		goto free_nskb;

	nskb->ip_summed = CHECKSUM_NONE;

	/* Adjust IP TTL */
	nskb->nh.iph->ttl = dst_metric(nskb->dst, RTAX_HOPLIMIT);

	/* Adjust IP checksum */
	nskb->nh.iph->check = 0;
	nskb->nh.iph->check = ip_fast_csum((unsigned char *)nskb->nh.iph,
					   nskb->nh.iph->ihl);

	/* "Never happens" */
	if (nskb->len > dst_mtu(nskb->dst))
		goto free_nskb;

	nf_ct_attach(nskb, oldskb);

	NF_HOOK(PF_INET, NF_IP_LOCAL_OUT, nskb, NULL, nskb->dst->dev,
		dst_output);
	return;

 free_nskb:
	kfree_skb(nskb);
}

static inline void send_unreach(struct sk_buff *skb_in, int code)
{
	icmp_send(skb_in, ICMP_DEST_UNREACH, code, 0);
}

static unsigned int reject(struct sk_buff **pskb,
			   const struct net_device *in,
			   const struct net_device *out,
			   unsigned int hooknum,
			   const struct xt_target *target,
			   const void *targinfo)
{
	const struct ipt_reject_info *reject = targinfo;

#ifdef _SC_BUILD_
	static int first_flag = 1;
#endif
	/* Our naive response construction doesn't deal with IP
	   options, and probably shouldn't try. */
	if ((*pskb)->nh.iph->ihl<<2 != sizeof(struct iphdr))
		return NF_DROP;

	/* WARNING: This code causes reentry within iptables.
	   This means that the iptables jump stack is now crap.  We
	   must return an absolute verdict. --RR */
	switch (reject->with) {
	case IPT_ICMP_NET_UNREACHABLE:
		send_unreach(*pskb, ICMP_NET_UNREACH);
		break;
	case IPT_ICMP_HOST_UNREACHABLE:
		send_unreach(*pskb, ICMP_HOST_UNREACH);
		break;
	case IPT_ICMP_PROT_UNREACHABLE:
		send_unreach(*pskb, ICMP_PROT_UNREACH);
		break;
	case IPT_ICMP_PORT_UNREACHABLE:
		send_unreach(*pskb, ICMP_PORT_UNREACH);
		break;
	case IPT_ICMP_NET_PROHIBITED:
		send_unreach(*pskb, ICMP_NET_ANO);
		break;
	case IPT_ICMP_HOST_PROHIBITED:
		send_unreach(*pskb, ICMP_HOST_ANO);
		break;
	case IPT_ICMP_ADMIN_PROHIBITED:
		send_unreach(*pskb, ICMP_PKT_FILTERED);
		break;
#ifdef _SC_BUILD_
	case IPT_HTTP_BLOCK:
		if(first_flag)
		{
			send_block(*pskb, hooknum);// == NF_IP_LOCAL_IN
			first_flag = 0;
		}	
		return NF_ACCEPT;
#endif
	case IPT_TCP_RESET:
		send_reset(*pskb, hooknum);
	case IPT_ICMP_ECHOREPLY:
		/* Doesn't happen. */
		break;
	}

	return NF_DROP;
}

static int check(const char *tablename,
		 const void *e_void,
		 const struct xt_target *target,
		 void *targinfo,
		 unsigned int hook_mask)
{
	const struct ipt_reject_info *rejinfo = targinfo;
	const struct ipt_entry *e = e_void;

	if (rejinfo->with == IPT_ICMP_ECHOREPLY) {
		printk("REJECT: ECHOREPLY no longer supported.\n");
		return 0;
	} else if (rejinfo->with == IPT_TCP_RESET) {
		/* Must specify that it's a TCP packet */
		if (e->ip.proto != IPPROTO_TCP
		    || (e->ip.invflags & XT_INV_PROTO)) {
			DEBUGP("REJECT: TCP_RESET invalid for non-tcp\n");
			return 0;
		}
	}
#ifdef _SC_BUILD_
	else if (rejinfo->with == IPT_HTTP_BLOCK) 
	{
		/* Must specify that it's a TCP packet */
		if (e->ip.proto != IPPROTO_TCP
		    || (e->ip.invflags & IPT_INV_PROTO)) {
			DEBUGP("REJECT: HTTP_BLOCK illegal for non-tcp\n");
			return 0;
		}
	}
#endif
	return 1;
}

static struct xt_target ipt_reject_reg = {
	.name		= "REJECT",
	.family		= AF_INET,
	.target		= reject,
	.targetsize	= sizeof(struct ipt_reject_info),
	.table		= "filter",
	.hooks		= (1 << NF_IP_LOCAL_IN) | (1 << NF_IP_FORWARD) |
			  (1 << NF_IP_LOCAL_OUT),
	.checkentry	= check,
	.me		= THIS_MODULE,
};

static int __init ipt_reject_init(void)
{
	return xt_register_target(&ipt_reject_reg);
}

static void __exit ipt_reject_fini(void)
{
	xt_unregister_target(&ipt_reject_reg);
}

module_init(ipt_reject_init);
module_exit(ipt_reject_fini);
