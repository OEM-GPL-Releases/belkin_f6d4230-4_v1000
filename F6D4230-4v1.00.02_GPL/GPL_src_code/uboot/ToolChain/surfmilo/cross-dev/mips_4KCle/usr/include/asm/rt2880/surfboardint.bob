/*
 * Copyright (C) 2001 Palmchip Corporation.  All rights reserved.
 *
 * ########################################################################
 *
 *  This program is free software; you can distribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 * ########################################################################
 *
 * Defines for the Surfboard interrupt controller.
 *
 */
#ifndef _SURFBOARDINT_H
#define _SURFBOARDINT_H

/* Number of IRQ supported on hw interrupt 0. */
#define SURFBOARDINT_UART	 2	/* UART0 */
#define SURFBOARDINT_UART1	 8	/* UART1 */
#define SURFBOARDINT_END	30

//kaiker
#define RT2880_INTERINT_START 40



/* Global interrupt bit definitions */
#define C_SURFBOARD_GLOBAL_INT	31
#define M_SURFBOARD_GLOBAL_INT	(1 << C_SURFBOARD_GLOBAL_INT)

/*
 * Surfboard registers are memory mapped on 32-bit aligned boundaries and
 * only word access are allowed.
 */
struct surfboard_ictrl_regs {
        volatile unsigned long irq0Status;
        volatile unsigned long irq1Status;
	long reserved[6];
	volatile unsigned long intType;
	long reserved1[3];
	volatile unsigned long rawStatus;
	volatile unsigned long intEnable;
	volatile unsigned long intDisable;
};

/* bobtseng added ++, 2006.3.6. */
#define read_32bit_cp0_register(source)                         \
({ int __res;                                                   \
        __asm__ __volatile__(                                   \
        ".set\tpush\n\t"                                        \
        ".set\treorder\n\t"                                     \
        "mfc0\t%0,"STR(source)"\n\t"                            \
        ".set\tpop"                                             \
        : "=r" (__res));                                        \
        __res;})
/* bobtseng added --, 2006.3.6. */

extern void surfboardint_init(void);

#endif /* !(_SURFBOARDINT_H) */
