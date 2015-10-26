#ifndef _SC_DEBUG_H_
#define _SC_DEBUG_H_

#include <linux/module.h>
typedef void (*get_pannic_info_func)(char *pBuf);
typedef void (*write_panic_info_func)(char info);
typedef char (*get_kernel_info_flag_func)(void);
typedef void (*panic_print_func)(const char *fmt, va_list args);
typedef struct tag_KERNEL_PANIC_INFO{
    get_pannic_info_func pGetPanicInfo;
    write_panic_info_func pWritePanicInfo;
    get_kernel_info_flag_func pGetKernelInfoFlag;
    write_panic_info_func pSetKernelInfoFlag;
    panic_print_func pPanicPrint;
}KERNEL_PANIC_INFO, *PKERNEL_PANIC_INFO;
KERNEL_PANIC_INFO *get_kernel_panic_handler(void);
#endif

