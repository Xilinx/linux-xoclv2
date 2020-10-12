# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2019-2020 Xilinx, Inc. All rights reserved.
#
# Authors: Sonal.Santan@xilinx.com
#

FULL_ALVEO_PATH=$(srctree)/$(src)/..
FULL_DTC_PATH=$(srctree)/scripts/dtc/libfdt

fdt-o := ../common/libfdt/fdt_addresses.o  \
	../common/libfdt/fdt_empty_tree.o \
	../common/libfdt/fdt.o  \
	../common/libfdt/fdt_ro.o  \
	../common/libfdt/fdt_rw.o \
	../common/libfdt/fdt_strerror.o \
	../common/libfdt/fdt_sw.o  \
	../common/libfdt/fdt_wip.o

obj-$(CONFIG_FPGA_ALVEO_XMGMT)	+= xmgmt.o

commondir := ../common

xmgmt-objs := xmgmt-root.o			\
	   xmgmt-main.o				\
	   xmgmt-fmgr-drv.o      		\
	   xmgmt-impl-ulp.o			\
	   $(commondir)/xocl-root.o		\
	   $(commondir)/xocl-metadata.o		\
	   $(commondir)/xocl-xclbin.o           \
	   $(fdt-o)


ccflags-y := -I$(FULL_ALVEO_PATH)/include \
	-I$(FULL_ALVEO_PATH)/include/uapi \
	-I$(FULL_ALVEO_PATH)/common \
	-I$(FULL_DTC_PATH)
