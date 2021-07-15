/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020-2021 Xilinx, Inc.
 *
 * Authors:
 *	Cheng Zhen <maxz@xilinx.com>
 */

#ifndef _LIB_DRV_H_
#define _LIB_DRV_H_

#include <linux/device/class.h>
#include <linux/device/bus.h>

extern struct class *xrt_class;
extern struct bus_type xrt_bus_type;

const char *xrt_drv_name(enum xrt_subdev_id id);
struct xrt_dev_endpoints *xrt_drv_get_endpoints(enum xrt_subdev_id id);
int xrt_drv_get(enum xrt_subdev_id id);
void xrt_drv_put(enum xrt_subdev_id id);

/* Module's init/fini routines for leaf driver in xrt-lib module */
#define XRT_LEAF_INIT_FINI_FUNC(name)					\
void name##_leaf_init_fini(bool init)					\
{									\
	if (init)							\
		xrt_register_driver(&xrt_##name##_driver);		\
	else								\
		xrt_unregister_driver(&xrt_##name##_driver);		\
}

/* Module's init/fini routines for leaf driver in xrt-lib module */
void group_leaf_init_fini(bool init);
void vsec_leaf_init_fini(bool init);
void axigate_leaf_init_fini(bool init);
void icap_leaf_init_fini(bool init);
void calib_leaf_init_fini(bool init);
void clkfreq_leaf_init_fini(bool init);
void clock_leaf_init_fini(bool init);
void ucs_leaf_init_fini(bool init);

#endif	/* _LIB_DRV_H_ */
