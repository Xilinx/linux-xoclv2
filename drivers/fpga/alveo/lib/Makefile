# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2020 Xilinx, Inc. All rights reserved.
#
# Authors: Sonal.Santan@xilinx.com
#

FULL_ALVEO_PATH=$(srctree)/$(src)/..

obj-$(CONFIG_FPGA_ALVEO_LIB) := xocl-lib.o

xocl-lib-y := 				\
	xocl-main.o			\
	xocl-subdev.o			\
	xocl-cdev.o			\
	../common/xocl-metadata.o	\
	subdevs/xocl-partition.o	\
	subdevs/xocl-test.o		\
	subdevs/xocl-vsec.o		\
	subdevs/xocl-vsec-golden.o	\
	subdevs/xocl-axigate.o		\
	subdevs/xocl-qspi.o		\
	subdevs/xocl-gpio.o		\
	subdevs/xocl-mailbox.o		\
	subdevs/xocl-icap.o		\
	subdevs/xocl-cmc.o		\
	subdevs/xocl-cmc-ctrl.o		\
	subdevs/xocl-cmc-sensors.o	\
	subdevs/xocl-cmc-mailbox.o	\
	subdevs/xocl-cmc-bdinfo.o	\
	subdevs/xocl-cmc-sc.o		\
	subdevs/xocl-srsr.o		\
	subdevs/xocl-clock.o		\
	subdevs/xocl-clkfreq.o		\
	subdevs/xocl-ucs.o		\
	subdevs/xocl-calib.o


ccflags-y := -I$(FULL_ALVEO_PATH)/include \
	-I$(FULL_ALVEO_PATH)/include/uapi \
	-I$(FULL_ALVEO_PATH)/common
