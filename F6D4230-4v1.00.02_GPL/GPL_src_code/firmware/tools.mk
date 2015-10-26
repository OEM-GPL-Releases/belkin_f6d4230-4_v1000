#-----------------------------------------------------------
#           Host CPU Arch Detect
#-----------------------------------------------------------

#CONFIG_CROSS_COMPILER_PATH=/opt/ralink/buildroot-gdb/bin
CONFIG_CROSS_COMPILER_PATH=$(shell pwd)/../tools/buildroot/buildroot-gdb/bin

ENDIAN        ?= little
ARCH          = mips
CROSS_COMPILE = $(CONFIG_CROSS_COMPILER_PATH)/mipsel-linux-uclibc-
KERNEL_CROSS_COMPILE = $(CROSS_COMPILE)

CC        = $(CROSS_COMPILE)gcc $(CPUFLAGS)
AS        = $(CROSS_COMPILE)as $(CPUFLAGS)
CXX       = $(CROSS_COMPILE)g++ $(CPUFLAGS)
AR        = $(CROSS_COMPILE)ar
LD        = $(CROSS_COMPILE)ld
OBJCOPY   = $(CROSS_COMPILE)objcopy
RANLIB    = $(CROSS_COMPILE)ranlib
STRIPTOOL = $(CROSS_COMPILE)strip
STRIP     = $(STRIPTOOL)

HOSTCC   = cc
SUBARCH= "mipsel-linux-uclibc-"

export CONFIG_CROSS_COMPILER_PATH CROSS_COMPILE CC AS CXX AR LD OBJCOPY  RANLIB STRIP

HOST_NCPU := 1
export HOST_NCPU

CONFIG_TOOLS_PATH=$(ROOTDIR)/tools/config_tools
export CONFIG_TOOLS_PATH