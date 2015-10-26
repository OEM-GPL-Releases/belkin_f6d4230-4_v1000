#--------------------------------------------------------------
# Below items need change according to project:
#    images: kernel image geneate method
#    clean: kernel advanced clean logic
#--------------------------------------------------------------

ifndef ROOTDIR
export ROOTDIR = $(shell pwd)
endif

-include config.mk

KERNEL_IMAGE = $(IMAGEDIR)/zImage

start_time := $(shell date -R)

MAKEARCH = $(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE)
MAKEARCH_KERNEL = $(MAKE) ARCH=$(ARCH) SUBARCH=$(SUBARCH) CROSS_COMPILE=$(KERNEL_CROSS_COMPILE)

all: first kernel images

#--------------------------------------------------------------------
#
# normal targets
#--------------------------------------------------------------------

.PHONY: first
first:

.PHONY: dep
dep:
	@if [ ! -f $(LINUXDIR)/.config.old ] ; then \
		$(MAKEARCH_KERNEL) -j$(HOST_NCPU) -C $(LINUXDIR) oldconfig; \
	fi

	@if [ ! -f $(LINUXDIR)/.depend ] ; then \
		$(MAKEARCH_KERNEL) -j$(HOST_NCPU) -C $(LINUXDIR) depend; \
	fi

.PHONY: kernel
kernel: dep
	$(MAKEARCH_KERNEL) -j$(HOST_NCPU) -C $(LINUXDIR) || exit 1
	cp $(LINUXDIR)/vmlinux $(IMAGEDIR)/vmlinux_backup_$(shell date +%F_%H%M%S)

.PHONY: preimages
preimages:
	cp $(LINUXDIR)/drivers/net/raeth/raeth.ko $(IMAGEDIR)/
	$(STRIP) -S $(IMAGEDIR)/raeth.ko
	cp $(LINUXDIR)/drivers/net/wireless_3100/rt2860v2_ap/rt2860v2_ap.ko $(IMAGEDIR)/
	$(STRIP) -S $(IMAGEDIR)/rt2860v2_ap.ko
	cp $(SCDIR)/drv/sc_module.ko $(IMAGEDIR)/
	$(STRIP) -S $(IMAGEDIR)/sc_module.ko

.PHONY: images
images:
	$(OBJCOPY) -O binary -R .note -R .comment -S $(LINUXDIR)/vmlinux  $(KERNEL_IMAGE)
	rm -f $(KERNEL_IMAGE).*; $(TOOLSDIR)/lzma -9 -f -S .lzma $(KERNEL_IMAGE)
	$(TOOLSDIR)/mkimage -A mips -O linux -T kernel -C lzma -a 80000000 -e $(shell $(CROSS_COMPILE)readelf -h $(LINUXDIR)/vmlinux | grep "Entry" | awk '{print $$4}') -n "Linux Kernel Image"  -d $(KERNEL_IMAGE).lzma $(IMAGEDIR)/uImage
	$(TOOLSDIR)/lzma -9 -f -S .lzma $(IMAGEDIR)/raeth.ko
	$(TOOLSDIR)/lzma -9 -f -S .lzma $(IMAGEDIR)/rt2860v2_ap.ko
	$(TOOLSDIR)/lzma -9 -f -S .lzma $(IMAGEDIR)/sc_module.ko
	cd $(IMAGEDIR);  ./linuxbb $(CONFIG_FW_MODEL)v$(CONFIG_FW_MODEL_VERSION)
	@echo make started at $(start_time) finished on `date -R`


sos: kernel images

.PHONY: help clean sos_clean
help:
	@echo "     make                - build firmware from source"
	@echo "     make kernel         - make kernel and kernel modules"
	@echo "     make images         - build formated firmware"
	@exit 0

sos_clean:
	$(MAKE) -C $(SCDIR)/drv clean

clean:
	$(MAKE) -C $(SCDIR)/drv clean
	$(MAKEARCH) -C $(LINUXDIR) clean
	rm -f $(LINUXDIR)/arch/mips/ramdisk/*.gz $(LINUXDIR)/linux
	cd $(IMAGEDIR); rm -f uImage *.gz *.lzma
	find ./ -name .depend | xargs rm -fr {}\;

menuconfig:
#	$(MAKE) -C $(LINUXDIR) menuconfig
	$(CONFIG_TOOLS_PATH)/Menuconfig
