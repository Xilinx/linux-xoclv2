/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2022 Advanced Micro Devices, Inc. All rights reserved.
 */

#ifndef _AMD_QDMA_H
#define _AMD_QDMA_H

#include <linux/dmaengine.h>

/**
 * struct qdma_chan_info - DMA channel information
 *	This information is used to match channel when request dma channel
 * @dir: Channel transfer direction
 */
struct qdma_chan_info {
	enum dma_transfer_direction dir;
};

#define XDMA_FILTER_PARAM(chan_info)	((void *)(chan_info))

struct dma_slave_map;

/**
 * struct qdma_platdata - platform specific data for XDMA engine
 * @max_dma_channels: Maximum dma channels in each direction
 */
struct qdma_platdata {
	u32 max_dma_channels;
	u32 slave_map_cnt;
	struct dma_slave_map *slave_map;
};

#endif /* _AMD_QDMA_H */
