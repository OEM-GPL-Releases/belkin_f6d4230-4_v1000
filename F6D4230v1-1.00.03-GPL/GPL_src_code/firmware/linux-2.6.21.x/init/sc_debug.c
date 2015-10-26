#include <linux/config.h>
#include <linux/proc_fs.h>
#include <linux/unistd.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/delay.h>
#include <linux/utsname.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/smp_lock.h>
#include <linux/hdreg.h>
#include <linux/bootmem.h>
#include <linux/file.h>
#include <linux/tty.h>
#include <asm/io.h>
#include <asm/bugs.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>

#include <linux/mm.h>
#include "linux/sc_debug.h"

static KERNEL_PANIC_INFO *pScKernelInfo = NULL;

void register_sc_kernel_panic_handler(KERNEL_PANIC_INFO *pHandler)
{
    pScKernelInfo = pHandler;
} 
KERNEL_PANIC_INFO *get_kernel_panic_handler(void)
{
    return pScKernelInfo;
} 
EXPORT_SYMBOL(register_sc_kernel_panic_handler);