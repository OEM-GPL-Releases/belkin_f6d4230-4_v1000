/*
 * (C) Copyright 2003
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

/*
 * This file contains the configuration parameters for the RT2880 board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * Run U-Boot in SDRAM for debugging 
 * a. modify TEXT_BASE in /board/rt2880/config.mk
 * b. define CFG_RUN_CODE_IN_RAM
 */
 //kaiker ,for RUN from Flash

#if (TEXT_BASE == 0x8B000000)
//#define CFG_RUN_CODE_IN_RAM  

#endif

#define DEBUG				1
//#define ET_DEBUG

#define CONFIG_RT2880_ETH		1	/* Enable built-in 10/100 Ethernet */

#define CONFIG_MIPS32		1	/* MIPS 4Kc CPU core	*/
//CONFIG_INCA_IP
#if defined (RT3052_FPGA_BOARD) || defined (RT2883_FPGA_BOARD) 
#define FPGA_BOARD_CLOCK_RATE 40000000
#else
#define FPGA_BOARD_CLOCK_RATE 25000000
#endif
#define PALMCHIP_CLOCK_DIVISOR 16
#define FPGA_BOARD_CLOCK_DIVISOR 32

/* allowed values: 100000000, 133000000, and 150000000 */
#if 1 /* for CFG_HZ only */

#ifdef RT2880_ASIC_BOARD
#define CPU_CLOCK_RATE	266000000 /* default: 150 MHz clock for the MIPS core */
#elif defined (RT3052_ASIC_BOARD)
#define CPU_CLOCK_RATE	384000000 
#else
#define CPU_CLOCK_RATE	FPGA_BOARD_CLOCK_RATE /* default: 150 MHz clock for the MIPS core */
#endif

#endif 

#define SERIAL_CLOCK_DIVISOR 16

#define CONFIG_BOOTDELAY	5	/* autoboot after 5 seconds	*/

#define CONFIG_BAUDRATE		57600

#define CONFIG_SERVERIP 10.10.10.3
#define CONFIG_IPADDR 10.10.10.123
#define CONFIG_ETHADDR "00:AA:BB:CC:DD:10"
#define CONFIG_ENV_OVERWRITE	//overwrite "ethaddr" and "serial#"
/* valid baudrates */
#define CFG_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define	CONFIG_TIMESTAMP		/* Print image info with timestamp */

#define CONFIG_PREBOOT	"echo;"	\
	"echo"

#undef	CONFIG_BOOTARGS

#define	CONFIG_EXTRA_ENV_SETTINGS					\
	"ramargs=setenv bootargs root=/dev/ram rw\0"			\
	"addip=setenv bootargs $(bootargs) "				\
		"ip=$(ipaddr):$(serverip):$(gatewayip):$(netmask)"	\
		":$(hostname):$(netdev):off\0"				\
	"addmisc=setenv bootargs $(bootargs) "				\
		"console=ttyS0,$(baudrate) "				\
		"ethaddr=$(ethaddr) "					\
		"panic=1\0"						\
	"flash_self=run ramargs addip addmisc;"				\
		"bootm $(kernel_addr) $(ramdisk_addr)\0"		\
	"kernel_addr=BFC40000\0"					\
	"u-boot=u-boot.bin\0"				\
	"load=tftp 8A100000 $(u-boot)\0"				\
	"u_b=protect off 1:0-1;era 1:0-1;"				\
		"cp.b 8A100000 BC400000 $(filesize)\0"			\
	"loadfs=tftp 8A100000 root.cramfs\0"				\
	"u_fs=era bc540000 bc83ffff;"				\
		"cp.b 8A100000 BC540000 $(filesize)\0"			\
	"test_tftp=tftp 8A100000 root.cramfs;run test_tftp\0"				\
	""
#define CONFIG_BOOTCOMMAND	"tftp" //"run flash_self"

#if defined(CFG_RUN_CODE_IN_RAM)
#define CONFIG_COMMANDS		(\
				(CONFIG_CMD_DFL |\
				 CFG_CMD_ASKENV	|\
				 CFG_CMD_DHCP	|\
				 CFG_CMD_ELF	|\
				 CFG_CMD_SPI	|\
				 CFG_CMD_I2C	|\
				 CFG_CMD_PING	))
#else
#define CONFIG_COMMANDS		(\
				((CONFIG_CMD_DFL|CFG_CMD_SPI) & ~(CFG_CMD_LOADS|CFG_CMD_ITEST|CFG_CMD_AUTOSCRIPT|\
				 CFG_CMD_IMLS|CFG_CMD_FPGA|CFG_CMD_NFS)\
				))
#endif


#include <cmd_confdefs.h>

/*
 * Miscellaneous configurable options
 */
#define	CFG_LONGHELP				/* undef to save memory      */

#if defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD) 
#define	CFG_PROMPT		"RT2880 # "	/* Monitor Command Prompt    */
#elif defined (RT2883_FPGA_BOARD) || defined (RT2883_ASIC_BOARD) 
#define	CFG_PROMPT		"RT2883 # "	/* Monitor Command Prompt    */
#elif defined (RT3052_FPGA_BOARD) || defined (RT3052_ASIC_BOARD) 
#define	CFG_PROMPT		"RT3052 # "	/* Monitor Command Prompt    */
#else
#define	CFG_PROMPT		"RTxxxx # "	/* Monitor Command Prompt    */
#endif
#define	CFG_CBSIZE		256		/* Console I/O Buffer Size   */
#define	CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16)  /* Print Buffer Size */
#define	CFG_MAXARGS		16		/* max number of command args*/

#define CFG_MALLOC_LEN		128*1024

#define CFG_BOOTPARAMS_LEN	128*1024

#define CFG_HZ			CPU_CLOCK_RATE/2

#if defined (RT2883_FPGA_BOARD) || defined (RT3052_FPGA_BOARD) || defined (RT3052_ASIC_BOARD) || defined (RT2883_ASIC_BOARD)
#define CFG_SDRAM_BASE		0x80000000
#else /* RT2880_FPGA_BOARD & RT2880_ASIC_BOARD */
#define CFG_SDRAM_BASE		0x8A000000
#endif


/* 
 * for TEST 
 */
#define CFG_CONSOLE_INFO_QUIET	

#if defined (RT2883_FPGA_BOARD) || defined (RT3052_FPGA_BOARD) || defined (RT3052_ASIC_BOARD) || defined (RT2883_ASIC_BOARD)
#define	CFG_LOAD_ADDR		0x80100000	/* default load address	*/

#define CFG_MEMTEST_START	0x80100000
#define CFG_MEMTEST_END		0x80400000
#else
#define	CFG_LOAD_ADDR		0x8A100000	/* default load address	*/

#define CFG_MEMTEST_START	0x8A100000
#define CFG_MEMTEST_END		0x8A400000
#endif


#define CFG_EMBEDED_SRAM_START 0xA0800000
#define CFG_EMBEDED_SRAM_FOR_RXRING0_DESC 0xA0800000
#define CFG_EMBEDED_SRAM_FOR_TXRING0_DESC 0xA0800100
#define CFG_EMBEDED_SRAM_FOR_TXRING1_DESC 0xA0800200
#define CFG_EMBEDED_SRAM_BUF_START 0xA0800300
#define CFG_EMBEDED_SRAM_SDP0_BUF_START 0xA0804000
#define CFG_EMBEDED_SRAM_END   0xA0807FFF

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CFG_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CFG_MAX_FLASH_SECT	(263)	/* max number of sectors on one chip */

#if defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD)
#ifdef ON_BOARD_8M_FLASH_COMPONENT
#define PHYS_FLASH_1		0xBC400000 /* Flash Bank #1 */
#else
#define PHYS_FLASH_1		0xBCC00000 /* Flash Bank #1 */
#endif
#define PHYS_FLASH_2		0xBC000000 /* Flash Bank #2 */
#else //non 2880
#ifdef RT3052_MP1
#ifdef ON_BOARD_8M_FLASH_COMPONENT
#define PHYS_FLASH_1		0xBF400000 /* Flash Bank #1 */
#else
#define PHYS_FLASH_1		0xBFC00000 /* Flash Bank #1 */
#endif
#define PHYS_FLASH_2		0xBF000000 /* Flash Bank #2 */
#else // RT3052_MP2
#define PHYS_FLASH_1		0xBF000000 /* Flash Bank #1 */
#endif // RT3052_MP1
#endif // defined (RT2880_FPGA_BOARD) || defined (RT2880_ASIC_BOARD)

/* The following #defines are needed to get flash environment right */
#define	CFG_MONITOR_BASE	TEXT_BASE

#define	CFG_MONITOR_LEN		(192 << 10)

#define CFG_INIT_SP_OFFSET	0x400000

#define CFG_FLASH_BASE		PHYS_FLASH_1

/* timeout values are in ticks */
#define CFG_FLASH_ERASE_TOUT	(15UL * CFG_HZ) /* Timeout for Flash Erase */
#define CFG_FLASH_WRITE_TOUT	(5 * CFG_HZ) /* Timeout for Flash Write */
#define CFG_ETH_AN_TOUT	(5 * CFG_HZ) /* Timeout for Flash Write */
#define CFG_ETH_LINK_UP_TOUT	(5 * CFG_HZ) /* Timeout for Flash Write */
#define CFG_FLASH_STATE_DISPLAY_TOUT  (2 * CFG_HZ) /* Timeout for Flash Write */


#define	CFG_ENV_IS_IN_FLASH		1
//#define CFG_ENV_IS_NOWHERE		1

/* Address and size of Primary Environment Sector	*/
#if 0       /* wanles change for uboot(0 - 0x2ffff), uboot_nv(0x2E000 - 0x2Efff)*/
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + 0x30000)
#define CFG_ENV_SIZE		0x10000
#else
#define CFG_ENV_ADDR		(CFG_FLASH_BASE + 0x2E000)
#define CFG_ENV_SIZE		0x1000
#define CFG_ENV_SECT_SIZE	0x10000
#endif
#define CFG_OS_ADDR	(CFG_FLASH_BASE + 0x40000)

#define CONFIG_FLASH_16BIT

#define CONFIG_NR_DRAM_BANKS	1

#define CONFIG_NET_MULTI
#define CFG_RX_ETH_BUFFER		60

//#define CFG_JFFS2_FIRST_BANK	1
//#define CFG_JFFS2_NUM_BANKS		1

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE		(16*1024)
#define CFG_ICACHE_SIZE		(16*1024)
#define CFG_CACHELINE_SIZE	16


#define CONFIG_LZMA		1


#define RT2880_REGS_BASE			0xA0000000


/*
 * System Controller	(0x00300000)
 *   Offset
 *   0x10  -- SYSCFG		System Configuration Register
 *   0x34  -- RSTCTRL		Reset Control Register
 *   0x38  -- RSTSTAT		Reset Status Register 
 *   0x60  -- GPIOMODE		GPIO Mode Control Register 
 */
#define RT2880_SYS_CNTL_BASE			(RALINK_SYSCTL_BASE)
#define RT2880_SYSCFG_REG			(RT2880_SYS_CNTL_BASE+0x10)
#define RT2880_RSTCTRL_REG			(RT2880_SYS_CNTL_BASE+0x34)
#define RT2880_RSTSTAT_REG			(RT2880_SYS_CNTL_BASE+0x38)
#define RT2880_GPIOMODE_REG			(RT2880_SYS_CNTL_BASE+0x60)

#define RT2880_PRGIO_ADDR       (RALINK_SYSCTL_BASE + 0x600) // Programmable I/O
#define RT2880_REG_PIOINT       (RT2880_PRGIO_ADDR + 0)
#define RT2880_REG_PIOEDGE      (RT2880_PRGIO_ADDR + 0x04)
#define RT2880_REG_PIORENA      (RT2880_PRGIO_ADDR + 0x08)
#define RT2880_REG_PIOFENA      (RT2880_PRGIO_ADDR + 0x0C)
#define RT2880_REG_PIODATA      (RT2880_PRGIO_ADDR + 0x20)
#define RT2880_REG_PIODIR       (RT2880_PRGIO_ADDR + 0x24)

#define RT2882_REG(x)		(*((volatile u32 *)(x)))	

#define RT2880_WDRST            (1<<1)
#define RT2880_SWSYSRST         (1<<2)
#define RT2880_SWCPURST         (1<<3)

#endif	/* __CONFIG_H */
