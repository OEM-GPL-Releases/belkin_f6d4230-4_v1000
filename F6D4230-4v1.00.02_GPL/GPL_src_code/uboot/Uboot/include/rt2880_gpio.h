/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************
 */

#ifndef __RT2880_GPIO_H__
#define __RT2880_GPIO_H__

#include <configs/rt2880.h>
/*
 * Address of RT2880 Registers
 */
#define RT2880_SYSCTL_ADDR		RT2880_SYS_CNTL_BASE // system control
#define RT2880_REG_GPIOMODE		(RT2880_SYSCTL_ADDR + 0x60)


#define RT2880_IRQ_ADDR			(RT2880_SYS_CNTL_BASE + 0x200)
#define RT2880_REG_INTENA		(RT2880_IRQ_ADDR + 0x34)
#define RT2880_REG_INTDIS		(RT2880_IRQ_ADDR + 0x38)

#define RT2880_PRGIO_ADDR		(RT2880_SYS_CNTL_BASE + 0x600) // Programmable I/O
/* gpio 0~23 */
#define RT2880_REG_PIOINT		(RT2880_PRGIO_ADDR + 0)
#define RT2880_REG_PIOEDGE		(RT2880_PRGIO_ADDR + 0x04)
#define RT2880_REG_PIORENA		(RT2880_PRGIO_ADDR + 0x08)
#define RT2880_REG_PIOFENA		(RT2880_PRGIO_ADDR + 0x0C)
#define RT2880_REG_PIODATA		(RT2880_PRGIO_ADDR + 0x20)
#define RT2880_REG_PIODIR		(RT2880_PRGIO_ADDR + 0x24)
/* gpio 24~39 */
#define RT2880_REG_PIO1INT		(RT2880_PRGIO_ADDR + 0x38)
#define RT2880_REG_PIO1EDGE		(RT2880_PRGIO_ADDR + 0x3c)
#define RT2880_REG_PIO1RENA		(RT2880_PRGIO_ADDR + 0x40)
#define RT2880_REG_PIO1FENA		(RT2880_PRGIO_ADDR + 0x44)
#define RT2880_REG_PIO1DATA		(RT2880_PRGIO_ADDR + 0x48)
#define RT2880_REG_PIO1DIR		(RT2880_PRGIO_ADDR + 0x4c)
/* gpio 40~71 */
#define RT2880_REG_PIO2INT		(RT2880_PRGIO_ADDR + 0x60)
#define RT2880_REG_PIO2EDGE		(RT2880_PRGIO_ADDR + 0x64)
#define RT2880_REG_PIO2RENA		(RT2880_PRGIO_ADDR + 0x68)
#define RT2880_REG_PIO2FENA		(RT2880_PRGIO_ADDR + 0x6C)
#define RT2880_REG_PIO2DATA		(RT2880_PRGIO_ADDR + 0x70)
#define RT2880_REG_PIO2DIR		(RT2880_PRGIO_ADDR + 0x74)

/*
 * Values for the GPIOMODE Register
 */
/* wanles add for GPIO, 2008-07-08 */
#if 1
#define RT2880_GPIOMODE_I2C		0x01  /*bit [0]   */
#define RT2880_GPIOMODE_SPI		0x02  /*bit [1]   */
#define RT2880_GPIOMODE_UARTF		0x1C  /*bit [4:2] */
#define RT2880_GPIOMODE_UARTL		0x20  /*bit [5]   */
#define RT2880_GPIOMODE_JTAG		0x40  /*bit [6]   */
#define RT2880_GPIOMODE_MDIO		0x80  /*bit [7]   */
#define RT2880_GPIOMODE_SDRAM		0x100  /*bit [8]   */
#define RT2880_GPIOMODE_RGMII		0x200  /*bit [9]   */
#else
#define RT2880_GPIOMODE_I2C		0x01
#define RT2880_GPIOMODE_UARTF		0x02
#define RT2880_GPIOMODE_SPI		0x04
#define RT2880_GPIOMODE_UARTL		0x08
#define RT2880_GPIOMODE_JTAG		0x10
#define RT2880_GPIOMODE_MDIO		0x20
#define RT2880_GPIOMODE_SDRAM		0x40
#define RT2880_GPIOMODE_PCI		0x80
#endif
// if you would like to enable GPIO mode for other pins, please modify this value
// !! Warning: changing this value may make other features(MDIO, PCI, etc) lose efficacy
#define RT2880_GPIOMODE_DFT		(RT2880_GPIOMODE_UARTF)


/* values for RT2880_REG_INTENA & RT2880_REG_INTDIS */
#define RT2880_INTENA_PIO	0x8	//Programmable IO Interrupt Status interrupt enable
/*
 * bit is the unit of length
 */
#define RT2880GPIO_DATA_MASK		0x00FFFFFF
#define RT2880GPIO_DATA_LEN		24
#define RT2880GPIO_DIR_IN		0
#define RT2880GPIO_DIR_OUT		1
#define RT2880GPIO_DIR_ALLIN		0
#define RT2880GPIO_DIR_ALLOUT		0x00FFFFFF

int rt2880gpio_init(void);
void rt2880gpio_exit(void);
#if 0
void rt2880gpio_set_dir(unsigned int value);
unsigned int rt2880gpio_read(void);
void rt2880gpio_write(unsigned int value);
#else
void rt2880gpio_set_dir(unsigned int gpio, unsigned int value);
void rt2880gpio_set(unsigned int gpio, unsigned int value);
unsigned int rt2880gpio_get(unsigned int gpio);
#endif

#endif
