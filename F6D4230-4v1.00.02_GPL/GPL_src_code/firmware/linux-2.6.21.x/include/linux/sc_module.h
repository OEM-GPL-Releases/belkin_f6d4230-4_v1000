#ifndef _SC_MODULE_
#define _SC_MODULE_

#include "linux/skbuff.h"
#include "linux/netdevice.h"

typedef struct sc_entry_s
{
    void (*sc_os_entry)(void);
    int (*sc_os_rcv)(struct sk_buff *skb);
}sc_entry_t;

void run_sc_os_entry(void);
int run_sc_os_rcv(struct sk_buff *skb);

void insert_sc_os_entry(void (*p)(void));
void insert_sc_os_rcv(int (*p)(struct sk_buff *skb));

#endif

