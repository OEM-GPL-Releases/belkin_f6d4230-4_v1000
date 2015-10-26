#####################################################################
# Please executes the following steps to build
# your own uboot image
#####################################################################

#********************************************************************
# Step1: Choice your Platform Type
#********************************************************************
#PLATFORM_TYPE = RT2880_FPGA
PLATFORM_TYPE = RT2880_ASIC
#PLATFORM_TYPE = RT2883_FPGA
#PLATFORM_TYPE = RT2883_ASIC
#PLATFORM_TYPE = RT3052_FPGA
#PLATFORM_TYPE = RT3052_ASIC

#********************************************************************
# Step2: Choice your Chip Type
#********************************************************************
#CHIP_VER = RT2880_SHUTTLE
CHIP_VER = RT2880_MP
#CHIP_VER = RT2883_MP
#CHIP_VER = RT3052_MP1
#CHIP_VER = RT3052_MP2

#********************************************************************
# Step3: Choice your GMAC Mode (Mode1 or Mode2 or Mode3)
#********************************************************************
#-------------------------------
#  Mode-1: Focus 100/Full Link On state 
#  Connect to: IC+175C/D, IC 100PHY, RTK 100PHY...etc
#-------------------------------
#GMAC_MODE = MAC_TO_100PHY_MODE

# Port Based VLAN for RT3052 ESW or IC+ 175C/D
# (P0~P4: Demo Board=WLLLL, EV Board=LLLLW)
#PORT_BASED_VLAN = RALINK_DEMO_BOARD_PVLAN
#PORT_BASED_VLAN = RALINK_EV_BOARD_PVLAN

#------------------------------
#  Mode-2: Focus 1000/Full Link On state 
#  Connect to : Vitesse Switch, RTK Switch, 
#		Marvell GigaPhy, RT3052 ESW...etc
#-------------------------------
#GMAC_MODE = MAC_TO_GIGAMAC_MODE

# Vitesse Switch need to turn on
#SWITH_RESET_MODE = GPIO10_RESET_MODE
#GIGA_SWITCH = VITESSE_7395

#-------------------------------
#  Mode-3: Auto-polling
#  Connect to: Marvell GigaPhy...etc
#------------------------------
GMAC_MODE = MAC_TO_GIGAPHY_MODE

# Auto-Negotiation GigaPHY Address 
MAC_TO_GIGAPHY_MODE_ADDR = 0x1f

#------------------------------
# whether RT2883 using GE2 or not (mark this to use GE1 normally)
#RT2883_ETHERNET = GE2

#********************************************************************
# Step4: Choice your DRAM Size
#********************************************************************
#DRAM_COMPONENT = 64M
DRAM_COMPONENT = 128M
#DRAM_COMPONENT = 256M

#DRAM_BUS= 16BIT
DRAM_BUS= 32BIT


#********************************************************************
# Step5: Choice your Flash Size
#********************************************************************
#FLASH_COMPONENT = 2M
FLASH_COMPONENT = 4M
#FLASH_COMPONENT = 8M
#FLASH_COMPONENT = 16M


######################################################################
# Option setting
######################################################################
#----------------------------------------
# uboot image type
#----------------------------------------
# ROM version (Burn to Flash)
TEXT_BASE = 0xBFC00000
# ROM version for RT2883,RT3052_MP2 (Burn to Flash)
#TEXT_BASE = 0xBF000000
# RAM version for RT2880 (Download to DRAM using JTAG)
#TEXT_BASE = 0x8A200000
# RAM version for RT2883,RT3052 (Download to DRAM using JTAG)
#TEXT_BASE = 0x80200000

#----------------------------------------
#If your GPIO14 connect to hardware reset circuit,
#you can turn on the definition to reset whole board
#if cpu_reset, system_reset or wdg_reset occured
#----------------------------------------
#BOARD_RESET_MODE = GPIO14_RESET_MODE

#----------------------------------------
# PCI pin config to GPIO mode
#----------------------------------------
#PCI_MODE = GPIO_FUNC
######################################################################




#################<< Test function option Configuration >>###################

# Set with ON/OFF

UN_NECESSITY_U_BOOT_CMD_OPEN = OFF

######## RT2880 test function option configuration ##########################

# Set with ON/OFF
RALINK_RUN_COMMAD_AT_ETH_RCV_FUN = OFF
RALINK_PCI_HOST_TEST_FUN = OFF
RALINK_MDIO_ACCESS_FUN = ON
#RALINK_SWITCH_DEBUG_FUN only for RT3052 Embedded Switch
RALINK_SWITCH_DEBUG_FUN = OFF
RALINK_SWITCH_LOOPBACK_DEBUG_FUN = OFF
RALINK_MEMORY_TEST_FUN = OFF
RALINK_GDMA_STATUS_DISPLAY_FUN = OFF
RALINK_GDMA_SCATTER_TEST_FUN = OFF
RALINK_GDMA_DUP_TX_RING_TEST_FUN = OFF
RALINK_MUTI_TX_DESCRIPTOR_TEST_FUN = OFF
RALINK_CACHE_STATE_DETECT_FUNC = OFF
RALINK_SEGMENT_SIZE_ALIGN_TEST_FUNC = OFF
RALINK_INTERNAL_LOOPBACK_TEST_FUNC = OFF
RALINK_SDRAM_CONTROLLER_REFRESH_CYCLE_TEST_FUNC = OFF
RALINK_RT3052_PHY_TEST = OFF

##########################################################################

# clean the slate ...
PLATFORM_RELFLAGS =
PLATFORM_CPPFLAGS =
PLATFORM_LDFLAGS =

#
# When cross-compiling on NetBSD, we have to define __PPC__ or else we
# will pick up a va_list declaration that is incompatible with the
# actual argument lists emitted by the compiler.
#
# [Tested on NetBSD/i386 1.5 + cross-powerpc-netbsd-1.3]

ifeq ($(ARCH),ppc)
ifeq ($(CROSS_COMPILE),powerpc-netbsd-)
PLATFORM_CPPFLAGS+= -D__PPC__
endif
ifeq ($(CROSS_COMPILE),powerpc-openbsd-)
PLATFORM_CPPFLAGS+= -D__PPC__
endif
endif

ifeq ($(ARCH),arm)
ifeq ($(CROSS_COMPILE),powerpc-netbsd-)
PLATFORM_CPPFLAGS+= -D__ARM__
endif
ifeq ($(CROSS_COMPILE),powerpc-openbsd-)
PLATFORM_CPPFLAGS+= -D__ARM__
endif
endif

ifdef	ARCH
sinclude $(TOPDIR)/$(ARCH)_config.mk	# include architecture dependend rules
endif
ifdef	CPU
sinclude $(TOPDIR)/cpu/$(CPU)/config.mk	# include  CPU	specific rules
endif
ifdef	SOC
sinclude $(TOPDIR)/cpu/$(CPU)/$(SOC)/config.mk	# include  SoC	specific rules
endif
ifdef	VENDOR
BOARDDIR = $(VENDOR)/$(BOARD)
else
BOARDDIR = $(BOARD)
endif
ifdef	BOARD
sinclude $(TOPDIR)/board/$(BOARDDIR)/config.mk	# include board specific rules
endif

#########################################################################

CONFIG_SHELL	:= $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
		    else if [ -x /bin/bash ]; then echo /bin/bash; \
		    else echo sh; fi ; fi)

ifeq ($(HOSTOS)-$(HOSTARCH),darwin-ppc)
HOSTCC		= cc
else
HOSTCC		= gcc
endif
HOSTCFLAGS	= -Wall -Wstrict-prototypes -g -fomit-frame-pointer
HOSTSTRIP	= strip

#########################################################################

#
# Include the make variables (CC, etc...)
#
AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
CPP	= $(CC) -E
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)RANLIB

RELFLAGS= $(PLATFORM_RELFLAGS)
DBGFLAGS= -gdwarf-2 -DDEBUG
OPTFLAGS= -Os #-fomit-frame-pointer
ifndef LDSCRIPT
#LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds.debug
LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds
endif
OBJCFLAGS += --gap-fill=0xff

gccincdir := $(shell $(CC) -print-file-name=include)


CPPFLAGS := $(DBGFLAGS) $(OPTFLAGS) $(RELFLAGS)		\
	-D__KERNEL__ -DTEXT_BASE=$(TEXT_BASE) 		\
	-I$(TOPDIR)/include				\
	-fno-builtin -ffreestanding -nostdinc -isystem	\
	$(gccincdir) -pipe $(PLATFORM_CPPFLAGS)
#	-DROUTER100					\


ifeq ($(UN_NECESSITY_U_BOOT_CMD_OPEN),ON)
CPPFLAGS += -DRT2880_U_BOOT_CMD_OPEN
endif

ifeq ($(RALINK_RUN_COMMAD_AT_ETH_RCV_FUN),ON)
CPPFLAGS += -DRALINK_RUN_COMMAD_AT_ETH_RCV_FUN
endif

ifeq ($(RALINK_PCI_HOST_TEST_FUN),ON)
CPPFLAGS += -DRALINK_PCI_HOST_TEST_FUN
endif

ifeq ($(RALINK_MDIO_ACCESS_FUN),ON)
CPPFLAGS += -DRALINK_MDIO_ACCESS_FUN
endif

ifeq ($(RALINK_SWITCH_DEBUG_FUN),ON)
CPPFLAGS += -DRALINK_SWITCH_DEBUG_FUN
endif

ifeq ($(RALINK_SWITCH_LOOPBACK_DEBUG_FUN),ON)
CPPFLAGS += -DRALINK_SWITCH_LOOPBACK_DEBUG_FUN
endif

ifeq ($(RALINK_MEMORY_TEST_FUN),ON)
CPPFLAGS += -DRALINK_MEMORY_TEST_FUN
endif

ifeq ($(RALINK_GDMA_STATUS_DISPLAY_FUN),ON)
CPPFLAGS += -DRALINK_GDMA_STATUS_DISPLAY_FUN
endif

ifeq ($(RALINK_GDMA_SCATTER_TEST_FUN),ON)
CPPFLAGS += -DRALINK_GDMA_SCATTER_TEST_FUN
endif

ifeq ($(RALINK_GDMA_DUP_TX_RING_TEST_FUN),ON)
CPPFLAGS += -DRALINK_GDMA_DUP_TX_RING_TEST_FUN
endif

ifeq ($(RALINK_GDMA_DUP_TX_RING_TEST_FUN),ON)
CPPFLAGS += -DRALINK_MUTI_TX_DESCRIPTOR_TEST_FUN
endif

ifeq ($(RALINK_CACHE_STATE_DETECT_FUNC),ON)
CPPFLAGS += -DRALINK_CACHE_STATE_DETECT_FUNC
endif

ifeq ($(RALINK_SEGMENT_SIZE_ALIGN_TEST_FUNC),ON)
CPPFLAGS += -DRALINK_SEGMENT_SIZE_ALIGN_TEST_FUNC
endif

ifeq ($(RALINK_INTERNAL_LOOPBACK_TEST_FUNC),ON)
CPPFLAGS += -DRALINK_INTERNAL_LOOPBACK_TEST_FUNC
endif

ifeq ($(RALINK_SDRAM_CONTROLLER_REFRESH_CYCLE_TEST_FUNC),ON)
CPPFLAGS += -DRALINK_SDRAM_CONTROLLER_REFRESH_CYCLE_TEST_FUNC
endif

ifeq ($(RALINK_RT3052_PHY_TEST),ON)
CPPFLAGS += -DRT3052_PHY_TEST
endif

ifeq ($(PLATFORM_TYPE),RT2880_FPGA)
CPPFLAGS += -DRT2880_FPGA_BOARD
endif

ifeq ($(PLATFORM_TYPE),RT2880_ASIC)
CPPFLAGS += -DRT2880_ASIC_BOARD
endif

ifeq ($(PLATFORM_TYPE),RT2883_FPGA)  
CPPFLAGS += -DRT2883_FPGA_BOARD
endif

ifeq ($(PLATFORM_TYPE),RT2883_ASIC)  
CPPFLAGS += -DRT2883_ASIC_BOARD
endif

ifeq ($(PLATFORM_TYPE),RT3052_FPGA)
CPPFLAGS += -DRT3052_FPGA_BOARD
endif

ifeq ($(PLATFORM_TYPE),RT3052_ASIC)
CPPFLAGS += -DRT3052_ASIC_BOARD
endif

ifeq ($(CHIP_VER),RT2880_SHUTTLE)
endif

ifeq ($(CHIP_VER),RT2880_MP)
CPPFLAGS += -DRT2880_MP
endif

ifeq ($(CHIP_VER),RT2883_MP)
CPPFLAGS += -DRT2883_MP
endif

ifeq ($(CHIP_VER),RT3052_MP1)
CPPFLAGS += -DRT3052_MP1
endif

ifeq ($(CHIP_VER),RT3052_MP2)
CPPFLAGS += -DRT3052_MP2
endif

ifeq ($(GMAC_MODE),MAC_TO_GIGAMAC_MODE)
CPPFLAGS += -DMAC_TO_GIGAMAC_MODE
endif

ifeq ($(GMAC_MODE),MAC_TO_GIGAPHY_MODE)
CPPFLAGS += -DMAC_TO_GIGAPHY_MODE
endif

ifdef MAC_TO_GIGAPHY_MODE_ADDR
CPPFLAGS += -DMAC_TO_GIGAPHY_MODE_ADDR=$(MAC_TO_GIGAPHY_MODE_ADDR)
endif 

ifeq ($(GMAC_MODE),MAC_TO_100PHY_MODE)
CPPFLAGS += -DMAC_TO_100PHY_MODE
endif

ifeq ($(SWITH_RESET_MODE),GPIO10_RESET_MODE)
CPPFLAGS += -DGPIO10_RESET_MODE
endif

ifeq ($(BOARD_RESET_MODE),GPIO14_RESET_MODE)
CPPFLAGS += -DGPIO14_RESET_MODE
endif

ifeq ($(FORCE_MODE),FORCE_TO_100F)
CPPFLAGS += -DFORCE_TO_100F
endif

ifeq ($(GIGA_SWITCH),VITESSE_7395)
CPPFLAGS += -DVTSS_SWITCH_SUPPORT
endif

ifeq ($(RT2883_ETHERNET),GE2)
CPPFLAGS += -DRT2883_USE_GE2
endif

ifeq ($(PCI_MODE),GPIO_FUNC)
CPPFLAGS += -DPCI_AT_GPIO_FUNC
endif

ifeq ($(PORT_BASED_VLAN),RALINK_DEMO_BOARD_PVLAN)
CPPFLAGS += -DRALINK_DEMO_BOARD_PVLAN
endif
ifeq ($(PORT_BASED_VLAN),RALINK_EV_BOARD_PVLAN)
CPPFLAGS += -DRALINK_EV_BOARD_PVLAN
endif

ifeq ($(DRAM_BUS),16BIT)
CPPFLAGS += -DON_BOARD_16BIT_DRAM_BUS
else
ifeq ($(DRAM_BUS),32BIT)
CPPFLAGS += -DON_BOARD_32BIT_DRAM_BUS
endif
endif

ifeq ($(DRAM_COMPONENT),64M)
CPPFLAGS += -DON_BOARD_64M_DRAM_COMPONENT
else
ifeq ($(DRAM_COMPONENT),128M)
CPPFLAGS += -DON_BOARD_128M_DRAM_COMPONENT
else
ifeq ($(DRAM_COMPONENT),256M)
CPPFLAGS += -DON_BOARD_256M_DRAM_COMPONENT
endif
endif
endif

ifeq ($(FLASH_COMPONENT),2M)
CPPFLAGS += -DON_BOARD_2M_FLASH_COMPONENT
else ifeq ($(FLASH_COMPONENT),4M)
CPPFLAGS += -DON_BOARD_4M_FLASH_COMPONENT
else ifeq ($(FLASH_COMPONENT),8M)
CPPFLAGS += -DON_BOARD_8M_FLASH_COMPONENT
else ifeq ($(FLASH_COMPONENT),16M)
CPPFLAGS += -DON_BOARD_16M_FLASH_COMPONENT
endif

	
ifdef BUILD_TAG
CFLAGS := $(CPPFLAGS) -Wall -Wstrict-prototypes \
	-DBUILD_TAG='"$(BUILD_TAG)"'
else
CFLAGS := $(CPPFLAGS) -Wall -Wstrict-prototypes
endif

# avoid trigraph warnings while parsing pci.h (produced by NIOS gcc-2.9)
# this option have to be placed behind -Wall -- that's why it is here
ifeq ($(ARCH),nios)
ifeq ($(findstring 2.9,$(shell $(CC) --version)),2.9)
CFLAGS := $(CPPFLAGS) -Wall -Wno-trigraphs
endif
endif

AFLAGS_DEBUG := -Wa,-gstabs
AFLAGS := $(AFLAGS_DEBUG) -D__ASSEMBLY__ $(CPPFLAGS)

LDFLAGS += -Bstatic -T $(LDSCRIPT) -Ttext $(TEXT_BASE) $(PLATFORM_LDFLAGS)

# Location of a usable BFD library, where we define "usable" as
# "built for ${HOST}, supports ${TARGET}".  Sensible values are
# - When cross-compiling: the root of the cross-environment
# - Linux/ppc (native): /usr
# - NetBSD/ppc (native): you lose ... (must extract these from the
#   binutils build directory, plus the native and U-Boot include
#   files don't like each other)
#
# So far, this is used only by tools/gdb/Makefile.

ifeq ($(HOSTOS)-$(HOSTARCH),darwin-ppc)
BFD_ROOT_DIR =		/usr/local/tools
else
ifeq ($(HOSTARCH),$(ARCH))
# native
BFD_ROOT_DIR =		/usr
else
#BFD_ROOT_DIR =		/LinuxPPC/CDK		# Linux/i386
#BFD_ROOT_DIR =		/usr/pkg/cross		# NetBSD/i386
BFD_ROOT_DIR =		/opt/powerpc
endif
endif

#########################################################################

export	CONFIG_SHELL HPATH HOSTCC HOSTCFLAGS CROSS_COMPILE \
	AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP \
	MAKE
export	TEXT_BASE PLATFORM_CPPFLAGS PLATFORM_RELFLAGS CPPFLAGS CFLAGS AFLAGS
#########################################################################

%.s:	%.S
	$(CPP) $(AFLAGS) -o $@ $(CURDIR)/$<
%.o:	%.S
	$(CC) $(AFLAGS) -c -o $@ $(CURDIR)/$<
%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

#########################################################################
