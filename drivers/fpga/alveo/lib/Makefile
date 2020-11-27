# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2020 Xilinx, Inc. All rights reserved.
#
# Authors: Sonal.Santan@xilinx.com
#

FULL_ALVEO_PATH=$(srctree)/$(src)/..
FULL_DTC_PATH=$(srctree)/scripts/dtc/libfdt

obj-$(CONFIG_FPGA_ALVEO_LIB) := xrt-lib.o

xrt-lib-objs := 			\
	xrt-main.o			\
	xrt-subdev.o			\
	xrt-cdev.o			\
	../common/xrt-metadata.o	\
	subdevs/xrt-partition.o	\
	subdevs/xrt-test.o		\
	subdevs/xrt-vsec.o		\
	subdevs/xrt-vsec-golden.o	\
	subdevs/xrt-axigate.o		\
	subdevs/xrt-qspi.o		\
	subdevs/xrt-gpio.o		\
	subdevs/xrt-mailbox.o		\
	subdevs/xrt-icap.o		\
	subdevs/xrt-cmc.o		\
	subdevs/xrt-cmc-ctrl.o		\
	subdevs/xrt-cmc-sensors.o	\
	subdevs/xrt-cmc-mailbox.o	\
	subdevs/xrt-cmc-bdinfo.o	\
	subdevs/xrt-cmc-sc.o		\
	subdevs/xrt-srsr.o		\
	subdevs/xrt-clock.o		\
	subdevs/xrt-clkfreq.o		\
	subdevs/xrt-ucs.o		\
	subdevs/xrt-calib.o


ccflags-y := -I$(FULL_ALVEO_PATH)/include \
	-I$(FULL_ALVEO_PATH)/common \
	-I$(FULL_DTC_PATH)
