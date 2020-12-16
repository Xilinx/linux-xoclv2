# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2019-2020 Xilinx, Inc. All rights reserved.
#
# Authors: Sonal.Santan@xilinx.com
#

FULL_XRT_PATH=$(srctree)/$(src)/..
FULL_DTC_PATH=$(srctree)/scripts/dtc/libfdt

obj-$(CONFIG_FPGA_XRT_XMGMT)	+= xmgmt.o

commondir := ../common

xmgmt-objs := xmgmt-root.o			\
	   xmgmt-main.o				\
	   xmgmt-fmgr-drv.o      		\
	   xmgmt-main-ulp.o			\
	   xmgmt-main-mailbox.o			\
	   $(commondir)/xrt-root.o		\
	   $(commondir)/xrt-metadata.o		\
	   $(commondir)/xrt-xclbin.o



ccflags-y := -I$(FULL_XRT_PATH)/include \
	-I$(FULL_XRT_PATH)/common \
	-I$(FULL_DTC_PATH)
