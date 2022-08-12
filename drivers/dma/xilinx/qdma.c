// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * DMA driver for Xilinx QDMA Subsystem
 *
 * Copyright (C) 2022 Advanced Micro Devices, Inc. All rights reserved.
 */

#include <linux/mod_devicetable.h>
#include <linux/regmap.h>
#include <linux/dmaengine.h>
#include <linux/platform_device.h>
#include <linux/platform_data/amd_qdma.h>
#include <linux/dma-mapping.h>
#include "../virt-dma.h"
#include "qdma-regs.h"

/* mmio regmap config for all QDMA registers */
static struct regmap_config qdma_regmap_config = {
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
};

/**
 * struct qdma_request - DMA request structure
 * @vdesc: Virtual DMA descriptor
 * @dir: Transferring direction of the request
 * @slave_addr: Physical address on DMA slave side
 * @sgl: Scatter gather list on host side
 * @sg_off: Start offset of the first sgl segment
 * @nents: Number of sgl segments to transfer
 */
struct qdma_request {
	struct virt_dma_desc		vdesc;
	enum dma_transfer_direction	dir;
	u64				slave_addr;
	struct scatterlist		*sgl;
	u32				sg_off;
	u32				nents;
};

/**
 * struct qdma_chan - Driver specific DMA channel structure
 * @vchan: Virtual channel
 * @qdev_hdl: Pointer to DMA device structure
 * @busy: Busy flag of the channel
 * @dir: Transferring direction of the channel
 * @cfg: Transferring config of the channel
 * @tasklet: Channel tasklet
 */
struct qdma_chan {
	struct virt_dma_chan		vchan;
	void				*qdev_hdl;
	bool				busy;
	enum dma_transfer_direction	dir;
	struct dma_slave_config		cfg;
	struct tasklet_struct		tasklet;
};

/**
 * struct qdma_device - DMA device structure
 */
struct qdma_device {
	struct platform_device 	*pdev;
	struct dma_device	dma_dev;
	struct regmap		*csr_regmap;
	struct regmap		*intr_regmap;
	struct regmap		*queue_regmap;
};

static inline struct qdma_chan *to_qdma_chan(struct dma_chan *chan)
{
	return container_of(chan, struct qdma_chan, vchan.chan);
}

static struct regmap *qdma_init_regmap(struct platform_device *pdev, char *name)
{
	struct regmap *regmap;
	struct resource *res;
	void *reg_base;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, name);
	if (!res)
		return NULL;

	reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (!reg_base) {
		dev_err(&pdev->dev, "map qdma csr failed");
		return NULL;
	}

	qdma_regmap_config.max_register = (unsigned int)resource_size(res);
	regmap = devm_regmap_init_mmio(&pdev->dev, reg_base,
				       &qdma_regmap_config);
	if (!regmap) {
		dev_err(&pdev->dev, "config %s regmap failed", name);
		return NULL;
	}

	return regmap;
}

/**
 * qdma_config_channels - init qdma channels
 */
static int qdma_config_channels(struct qdma_device *qdev)
{
	// TODO: alloc and init channel structure based on driver pri data
	return 0;
}

/**
 * qdma_slave_config - Configure the DMA channel
 * @chan: DMA channel
 * @cfg: channel configuration
 */
int qdma_slave_config(struct dma_chan *chan, struct dma_slave_config *cfg)
{
	struct qdma_chan *qdma_chan = to_qdma_chan(chan);

	memcpy(&qdma_chan->cfg, cfg, sizeof(*cfg));

	return 0;
}

/**
 * qdma_free_chan_resources - Free channel resources
 * @chan: DMA channel
 */
static void qdma_free_chan_resources(struct dma_chan *chan)
{
	//TODO: free qdma queue
}

/**
 * qdma_alloc_chan_resources - Allocate channel resources
 * @chan: DMA channel
 */
static int qdma_alloc_chan_resources(struct dma_chan *chan)
{
	//TODO: alloc qdma queue
	return 0;
}

/**
 * qdma_xfer_start - Start DMA transfer
 * @qdma_chan: DMA channel pointer
 */
static int qdma_xfer_start(struct qdma_chan *qdma_chan)
{
	//TODO: read or write through queue
	return 0;
}

/**
 * qdma_issue_pending - Issue pending transactions
 * @chan: DMA channel pointer
 */
static void qdma_issue_pending(struct dma_chan *chan)
{
	struct qdma_chan *qdma_chan = to_qdma_chan(chan);
	unsigned long flags;

	spin_lock_irqsave(&qdma_chan->vchan.lock, flags);
	if (vchan_issue_pending(&qdma_chan->vchan))
		qdma_xfer_start(qdma_chan);
	spin_unlock_irqrestore(&qdma_chan->vchan.lock, flags);
}

/**
 * qdma_prep_slave_sg - prepare a descriptor for a
 *	DMA_SLAVE transaction
 * @chan: DMA channel pointer
 * @sgl: Transfer scatter gather list
 * @sg_len: Length of scatter gather list
 * @dir: Transfer direction
 * @flags: transfer ack flags
 * @context: APP words of the descriptor
 */
static struct dma_async_tx_descriptor *
qdma_prep_slave_sg(struct dma_chan *chan, struct scatterlist *sgl,
		   unsigned int sg_len, enum dma_transfer_direction dir,
		   unsigned long flags, void *context)
{
	struct qdma_chan *qdma_chan = to_qdma_chan(chan);
	struct qdma_request *req;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return NULL;

	req->sgl = sgl;
	req->dir = dir;
	req->nents = sg_len;
	if (dir == DMA_MEM_TO_DEV)
		req->slave_addr = qdma_chan->cfg.dst_addr;
	else
		req->slave_addr = qdma_chan->cfg.src_addr;

	return vchan_tx_prep(&qdma_chan->vchan, &req->vdesc, flags);
}

/**
 * qdma_irq_init - initialize IRQs
 * @qdev: DMA device pointer
 */
static int qdma_irq_init(struct qdma_device *qdev)
{
	//TODO: register and alloc irq
	return 0;
}

static bool qdma_filter_fn(struct dma_chan *chan, void *param)
{
	struct qdma_chan *qdma_chan = to_qdma_chan(chan);
	struct qdma_chan_info *chan_info = param;

	if (chan_info->dir != qdma_chan->dir)
		return false;

	return true;
}

/**
 * qdma_remove - Driver remove function
 * @pdev: Pointer to the platform_device structure
 */
static int qdma_remove(struct platform_device *pdev)
{
	return 0;
}

/**
 * qdma_probe - Driver probe function
 * @pdev: Pointer to the platform_device structure
 */
static int qdma_probe(struct platform_device *pdev)
{
	struct qdma_platdata *pdata = dev_get_platdata(&pdev->dev);
	struct qdma_device *qdev;
	int ret = -EINVAL;

	qdev = devm_kzalloc(&pdev->dev, sizeof(*qdev), GFP_KERNEL);
	if (!qdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, qdev);
	qdev->pdev = pdev;

	qdev->csr_regmap = qdma_init_regmap(pdev, "qdma_csr");
	if (!qdev->csr_regmap) {
		dev_err(&pdev->dev, "failed to init csr regmap");
		goto failed;
	}

	qdev->intr_regmap = qdma_init_regmap(pdev, "qdma_intr");
	if (!qdev->intr_regmap) {
		dev_err(&pdev->dev, "failed to init intr regmap");
		goto failed;
	}

	qdev->queue_regmap = qdma_init_regmap(pdev, "trq_sel_queue");
	if (!qdev->queue_regmap) {
		dev_err(&pdev->dev, "failed to init trq_sel_queue regmap");
		goto failed;
	}

	INIT_LIST_HEAD(&qdev->dma_dev.channels);

	ret = qdma_config_channels(qdev);
	if (ret) {
		dev_err(&pdev->dev, "config channels failed: %d", ret);
		goto failed;
	}

	dma_cap_set(DMA_SLAVE, qdev->dma_dev.cap_mask);
	dma_cap_set(DMA_PRIVATE, qdev->dma_dev.cap_mask);

	qdev->dma_dev.dev = &pdev->dev;
	qdev->dma_dev.device_free_chan_resources = qdma_free_chan_resources;
	qdev->dma_dev.device_alloc_chan_resources = qdma_alloc_chan_resources;
	qdev->dma_dev.device_tx_status = dma_cookie_status;
	qdev->dma_dev.device_prep_slave_sg = qdma_prep_slave_sg;
	qdev->dma_dev.device_config = qdma_slave_config;
	qdev->dma_dev.device_issue_pending = qdma_issue_pending;
	qdev->dma_dev.filter.map = pdata->slave_map;
	qdev->dma_dev.filter.mapcnt = pdata->slave_map_cnt;
	qdev->dma_dev.filter.fn = qdma_filter_fn;

	ret = dma_async_device_register(&qdev->dma_dev);
	if (ret) {
		dev_err(&pdev->dev, "failed to register Xilinx XDMA: %d", ret);
		goto failed;
	}

	ret = qdma_irq_init(qdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to init irq: %d", ret);
		goto failed;
	}

	return 0;

failed:
	qdma_remove(pdev);

	return ret;
}

static const struct platform_device_id qdma_id_table[] = {
	{ "qdma", },
	{ },
};

static struct platform_driver qdma_driver = {
	.driver		= {
		.name = "qdma",
	},
	.id_table	= qdma_id_table,
	.probe		= qdma_probe,
	.remove		= qdma_remove,
};

module_platform_driver(qdma_driver);

MODULE_DESCRIPTION("AMD QDMA driver");
MODULE_AUTHOR("XRT Team <runtime@xilinx.com>");
MODULE_LICENSE("GPL");
