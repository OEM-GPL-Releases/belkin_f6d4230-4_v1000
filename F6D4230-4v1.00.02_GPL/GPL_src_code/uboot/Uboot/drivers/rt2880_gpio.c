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
 *
 * $Id: rt2880_gpio.c,v 1.2 2007-10-25 05:50:04 david_zhang Exp $
 */
#include <linux/config.h>
#include "rt2880_gpio.h"

#include <common.h>
#include <asm/types.h>
#include <asm/byteorder.h>
#include <rt_mmap.h>

#define NAME			"rt2880_gpio"
#define RT2880GPIO_DEVNAME	"gpio"
int rt2880gpio_major = 252;
u32 rt2880gpio_intp = 0;
int rt2880gpio_irqnum = 0;
u32 rt2880gpio_edge = 0;

#define RT2880GPIO_MAX_INFO (RT2880GPIO_DATA_LEN)

int rt2880gpio_init(void)
{
	u32 gpiomode;

	//config these pins to gpio mode
	gpiomode = le32_to_cpu(*(volatile u32 *)(RT2880_REG_GPIOMODE));
//	gpiomode |= RT2880_GPIOMODE_DFT;
//	gpiomode |= RT2880_GPIOMODE_PCI;	//71:40
	gpiomode |= RT2880_GPIOMODE_I2C;       /* GPIO [2:1]  */
	gpiomode |= RT2880_GPIOMODE_SPI;       /* GPIO [6:3]  */
	gpiomode |= RT2880_GPIOMODE_DFT;       /* GPIO [14:7] */
	*(volatile u32 *)(RT2880_REG_GPIOMODE) = cpu_to_le32(gpiomode);

	//enable gpio interrupt
	*(volatile u32 *)(RT2880_REG_INTENA) = cpu_to_le32(RT2880_INTENA_PIO);

	printf("Ralink RT2880 gpio driver initialized\n");
	return 0;
}

void rt2880gpio_exit(void)
{
	//config these pins to normal mode
//	*(volatile u32 *)(RT2880_REG_GPIOMODE) &= ~RT2880_GPIOMODE_DFT;
//	*(volatile u32 *)(RT2880_REG_GPIOMODE) &= ~RT2880_GPIOMODE_PCI;	
	*(volatile u32 *)(RT2880_REG_GPIOMODE) &= ~RT2880_GPIOMODE_I2C;	
	*(volatile u32 *)(RT2880_REG_GPIOMODE) &= ~RT2880_GPIOMODE_SPI;	
	*(volatile u32 *)(RT2880_REG_GPIOMODE) &= ~RT2880_GPIOMODE_DFT;	
	//disable gpio interrupt
	*(volatile u32 *)(RT2880_REG_INTDIS) = cpu_to_le32(RT2880_INTENA_PIO);
	printf("Ralink RT2880 gpio driver exited\n");
}
#if 0
void rt2880gpio_set_dir(unsigned int value)
{
	*(volatile u32 *)(RT2880_REG_PIODIR) = cpu_to_le32(value);
}

unsigned int rt2880gpio_read(void)
{
	return le32_to_cpu(*(volatile u32 *)(RT2880_REG_PIODATA));
}

void rt2880gpio_write(unsigned int value)
{
	*(volatile u32 *)(RT2880_REG_PIODATA) = cpu_to_le32(value);
}
#else
void rt2880gpio_set_dir(unsigned int gpio, unsigned int value)
{
	unsigned int regval = 0;
	unsigned int reg = RT2880_REG_PIODIR;
	unsigned int gpio_bit = 0;
		
	if (gpio <= 23)
	{
		 reg = RT2880_REG_PIODIR;
		 gpio_bit = gpio;
	}
	else if ((gpio >= 24) && (gpio <= 39))
	{
		 reg = RT2880_REG_PIO1DIR;
		 gpio_bit = gpio - 24;
	}
	else if ((gpio >= 40) && (gpio <= 71))
	{
		 reg = RT2880_REG_PIO2DIR;
		 gpio_bit = gpio - 40;
	}
	else
	{
		printf("%s error. gpio=%d\n", __FUNCTION__, gpio);
		return;
	}

	regval = le32_to_cpu(*(volatile u32 *)(reg));
	if (value)
	{
		regval |= 1<<gpio_bit;
	}
	else
	{
		regval &= ~(1<<gpio_bit);
	}
	*(volatile u32 *)(reg) = cpu_to_le32(regval);

	return;	
}

unsigned int rt2880gpio_get(unsigned int gpio)
{
	unsigned int regval = 0;
	unsigned int reg = RT2880_REG_PIODATA;
	unsigned int gpio_bit = 0;
		
	if (gpio <= 23)
	{
		 reg = RT2880_REG_PIODATA;
		 gpio_bit = gpio;
	}
	else if ((gpio >= 24) && (gpio <= 39))
	{
		 reg = RT2880_REG_PIO1DATA;
		 gpio_bit = gpio - 24;
	}
	else if ((gpio >= 40) && (gpio <= 71))
	{
		 reg = RT2880_REG_PIO2DATA;
		 gpio_bit = gpio - 40;
	}
	else
	{
		printf("%s error. gpio=%d\n", __FUNCTION__, gpio);
		return 0;
	}

	regval = le32_to_cpu(*(volatile u32 *)(reg));
	
	return ((regval>>gpio_bit) & 1);
}

void rt2880gpio_set(unsigned int gpio, unsigned int value)
{
	unsigned int regval = 0;
	unsigned int reg = RT2880_REG_PIODATA;
	unsigned int gpio_bit = 0;
		
	if (gpio <= 23)
	{
		 reg = RT2880_REG_PIODATA;
		 gpio_bit = gpio;
	}
	else if ((gpio >= 24) && (gpio <= 39))
	{
		 reg = RT2880_REG_PIO1DATA;
		 gpio_bit = gpio - 24;
	}
	else if ((gpio >= 40) && (gpio <= 71))
	{
		 reg = RT2880_REG_PIO2DATA;
		 gpio_bit = gpio - 40;
	}
	else
	{
		printf("%s error. gpio=%d\n", __FUNCTION__, gpio);
		return;
	}

	regval = le32_to_cpu(*(volatile u32 *)(reg));
	if (value)
	{
		regval |= 1<<gpio_bit;
	}
	else
	{
		regval &= ~(1<<gpio_bit);
	}
	*(volatile u32 *)(reg) = cpu_to_le32(regval);

	return;
}
#endif

