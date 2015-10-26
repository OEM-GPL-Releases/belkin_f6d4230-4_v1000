/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef	__VERSION_H__
#define	__VERSION_H__

#include "../uboot_version.h"

#define U_BOOT_VERSION	"U-Boot 1.1.3"

#if defined (RT2880_ASIC_BOARD) || defined (RT2883_ASIC_BOARD) || defined (RT3052_ASIC_BOARD)
#define CHIP_TYPE	"ASIC"
#elif defined (RT2880_FPGA_BOARD) || defined (RT2883_FPGA_BOARD) || defined (RT3052_FPGA_BOARD)
#define CHIP_TYPE	"FPGA"
#else
#error "PLATFORM_TYPE not defined in config.mk"
#endif

#if defined (RT2880_SHUTTLE)
#define CHIP_VERSION	"2880_Shuttle"
#elif defined (RT2880_MP)
#define CHIP_VERSION	"2880_MP"
#elif defined (RT2883_MP)
#define CHIP_VERSION	"2883_MP"
#elif defined (RT3052_MP1)
#define CHIP_VERSION	"3052_MP1"
#elif defined (RT3052_MP2)
#define CHIP_VERSION	"3052_MP2"
#else
#error "CHIP_VER not defined in config.mk"
#endif


#if defined (MAC_TO_100PHY_MODE)
#define GMAC_MODE	"(MAC to 100PHY Mode)"
#elif defined (MAC_TO_GIGAPHY_MODE)
#define GMAC_MODE	"(MAC to GigaPHY Mode)"
#ifndef MAC_TO_GIGAPHY_MODE_ADDR
#error "MAC_TO_GIGAPHY_MODE_ADDR not defined in config.mk"
#endif
#elif defined (MAC_TO_GIGAMAC_MODE)
#define GMAC_MODE	"(MAC to GigaMAC Mode)"
#else
#error	"GMAC_MODE not defined"
#endif


#if defined (ON_BOARD_64M_DRAM_COMPONENT)
#define DRAM_COMPONENT	"DRAM COMPONENT: 64Mbits"
#define DRAM_PARAMETER_1 8
#elif defined (ON_BOARD_128M_DRAM_COMPONENT)
#define DRAM_COMPONENT	"DRAM COMPONENT: 128Mbits"
#define DRAM_PARAMETER_1 16
#elif defined (ON_BOARD_256M_DRAM_COMPONENT)
#define DRAM_COMPONENT	"DRAM COMPONENT: 256Mbits"
#define DRAM_PARAMETER_1 32
#else
#error "DRAM SIZE not defined"
#endif

#if defined (ON_BOARD_16BIT_DRAM_BUS)
#define DRAM_BUS	"DRAM BUS: 16BIT"
#define DRAM_PARAMETER_2 1
#elif defined (ON_BOARD_32BIT_DRAM_BUS)
#define DRAM_BUS	"DRAM BUS: 32BIT"
#define DRAM_PARAMETER_2 2
#else
#error "DRAM BUS not defined"
#endif

#define DRAM_SIZE ((DRAM_PARAMETER_1)*(DRAM_PARAMETER_2))


#define SHOW_VER_STR()	\
	do {	\
		printf("============================================ \n"); \
		printf("Ralink UBoot Version: %s\n", RALINK_LOCAL_VERSION); \
		printf("-------------------------------------------- \n"); \
		printf("%s %s %s\n",CHIP_TYPE, CHIP_VERSION, GMAC_MODE); \
		printf("%s \n", DRAM_COMPONENT); \
		printf("%s \n", DRAM_BUS); \
		printf("Total memory: %dMbytes\n", DRAM_SIZE); \
		printf("%s\n", "Date:" __DATE__ "  Time:" __TIME__ ); \
		printf("============================================ \n"); \
	}while(0)

#endif	/* __VERSION_H__ */
