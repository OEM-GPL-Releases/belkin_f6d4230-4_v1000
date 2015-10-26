/*
 *	Generic parts
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 *
 *	$Id: br.c,v 1.1.1.1 2007-05-25 06:50:00 bruce Exp $
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/init.h>
#include <linux/llc.h>
#include <net/llc.h>
#include <linux/proc_fs.h>

#include "br_private.h"

int (*br_should_route_hook) (struct sk_buff **pskb) = NULL;

static struct llc_sap *br_stp_sap;

#ifdef _SC_BUILD_ // for guest access control
#define PROC_GUEST_IFNAME    "guest_iface_name"
static char guest_ifname[IFNAMSIZ] = {"unknown"};
extern int guest_ifidx;

static struct proc_dir_entry *procGuestIfname;
static ssize_t proc_read_guest_ifname_fops(struct file *filp, char *buf,size_t count , loff_t *offp)
{
	int len = 0;
	
	if(*offp!=0)
		return 0;
	
	len = strlen(guest_ifname);
	
	copy_to_user(buf,guest_ifname,len);
	buf[len] = '\n';
	len++;
	
	*offp = len;
	return len;
}

static ssize_t proc_write_guest_ifname_fops(struct file * file, const char *buf, size_t count, loff_t *ppos)
{
    int len;
    struct net_device *dev;
    
    len = sizeof(guest_ifname) - 1;
    if(len > count)
        len = count;
    
    if (copy_from_user(guest_ifname, buf, len))
			return -EFAULT;
    
    /* remove '\n' */
    guest_ifname[len - 1] = '\0';
    if( (dev = dev_get_by_name(guest_ifname)) )
    {
        guest_ifidx = dev->ifindex;
        dev_put(dev);
    }
        
    printk("set guest iface name to <%s>\n", guest_ifname);
    
	return count;
}

static struct file_operations guest_ifname_fops = {
	read: proc_read_guest_ifname_fops,        
	write: proc_write_guest_ifname_fops,
	//ioctl: NULL,
};
#endif // _SC_BUILD_

static int __init br_init(void)
{
	int err;

	br_stp_sap = llc_sap_open(LLC_SAP_BSPAN, br_stp_rcv);
	if (!br_stp_sap) {
		printk(KERN_ERR "bridge: can't register sap for STP\n");
		return -EADDRINUSE;
	}

	br_fdb_init();

	err = br_netfilter_init();
	if (err)
		goto err_out1;

	err = register_netdevice_notifier(&br_device_notifier);
	if (err)
		goto err_out2;

#ifdef _SC_BUILD_
    if ((procGuestIfname = create_proc_entry(PROC_GUEST_IFNAME, 0777, NULL)))
    {
        procGuestIfname->proc_fops = &guest_ifname_fops;
    	procGuestIfname->owner 	  = THIS_MODULE;
    	procGuestIfname->mode 	  = S_IFREG | S_IRUGO;
    	procGuestIfname->uid 	  = 0;
    	procGuestIfname->gid 	  = 0;
    }
#endif // _SC_BUILD_

	br_netlink_init();
	brioctl_set(br_ioctl_deviceless_stub);
	br_handle_frame_hook = br_handle_frame;

	br_fdb_get_hook = br_fdb_get;
	br_fdb_put_hook = br_fdb_put;

	return 0;

err_out2:
	br_netfilter_fini();
err_out1:
	llc_sap_put(br_stp_sap);
	return err;
}

static void __exit br_deinit(void)
{
	rcu_assign_pointer(br_stp_sap->rcv_func, NULL);

	br_netlink_fini();
	br_netfilter_fini();
	unregister_netdevice_notifier(&br_device_notifier);
	brioctl_set(NULL);

	br_cleanup_bridges();

	synchronize_net();

	llc_sap_put(br_stp_sap);
	br_fdb_get_hook = NULL;
	br_fdb_put_hook = NULL;

	br_handle_frame_hook = NULL;
#ifdef _SC_BUILD_
    if (procGuestIfname)
    	remove_proc_entry(PROC_GUEST_IFNAME, &proc_root);
#endif
	br_fdb_fini();
}

EXPORT_SYMBOL(br_should_route_hook);

module_init(br_init)
module_exit(br_deinit)
MODULE_LICENSE("GPL");
MODULE_VERSION(BR_VERSION);
