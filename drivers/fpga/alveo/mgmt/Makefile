# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2019-2020 Xilinx, Inc. All rights reserved.
#
# Authors: Sonal.Santan@xilinx.com
#

FULL_ALVEO_PATH=$(srctree)/$(src)/..

obj-$(CONFIG_FPGA_ALVEO_XMGMT)	+= xmgmt.o

commondir := ../common

xmgmt-y := xmgmt-root.o				\
	   xmgmt-main.o				\
	   xmgmt-fmgr-drv.o      		\
	   xmgmt-impl-ulp.o			\
	   $(commondir)/xocl-root.o		\
	   $(commondir)/xocl-metadata.o		\
	   $(commondir)/xocl-xclbin.o


ccflags-y := -I$(FULL_ALVEO_PATH)/include \
	-I$(FULL_ALVEO_PATH)/include/uapi \
	-I$(FULL_ALVEO_PATH)/common
