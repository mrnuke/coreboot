/*
 * MMC driver for Allwinner SOCs
 *
 * Copyright (C) 2007-2011 Allwinner Technology Co., Ltd.
 * Copyright (C) 2013  Alexandru Gagniuc <mr.nuke.me@gmail.com>
 * Subject to the GNU GPL v2, or (at your option) any later version.
 */

#include "clock.h"
#include "gpio.h"
#include "mmc.h"
#include <drivers/mmc/mmc.h>

#include <arch/io.h>
#include <console/console.h>
#include <string.h>

#define ERROR(x...) printk(BIOS_ERR, "[mmc/a10] " x)
#define LOG(x...) printk(BIOS_INFO, "[mmc/a10] " x)
#if CONFIG_ALLWINNER_DEBUG_MMC
#define DEBUG(x...) printk(BIOS_DEBUG, "[mmc/a10] " x)
#define SPEW(x...) printk(BIOS_DEBUG, "[mmc/a10] " x)
#else
#define DEBUG(x...)
#define SPEW(x...)
#endif

struct sunxi_mmc_host {
	unsigned mmc_no;
	uint32_t *mclkreg;
	unsigned database;
	unsigned fatal_err;
	unsigned mod_clk;
	struct sunxi_mmc *reg;
};

/* support 4 mmc hosts */
struct mmc mmc_dev[4];
struct sunxi_mmc_host mmc_host[4];

static void dump_mmc_reg(struct sunxi_mmc *reg)
{
	/* Ugly but effective */
	SPEW("MMC controller register dump:\n");
	SPEW("gctrl   0x%08x\tclkcr   0x%08x\n", reg->gctrl, reg->clkcr);
	SPEW("timeout 0x%08x\twidth   0x%08x\n", reg->timeout, reg->width);
	SPEW("blksz   0x%08x\tbytecnt 0x%08x\n", reg->blksz, reg->bytecnt);
	SPEW("cmd     0x%08x\targ     0x%08x\n", reg->cmd, reg->arg);
	SPEW("resp0   0x%08x\tresp1   0x%08x\n", reg->resp0, reg->resp1);
	SPEW("resp2   0x%08x\tresp3   0x%08x\n", reg->resp2, reg->resp3);
	SPEW("imask   0x%08x\tmint    0x%08x\n", reg->imask, reg->mint);
	SPEW("rint    0x%08x\tstatus  0x%08x\n", reg->rint, reg->status);
	SPEW("ftrglvl 0x%08x\tfuncsel 0x%08x\n", reg->ftrglevel, reg->funcsel);
	SPEW("dmac    0x%08x\tdlba    0x%08x\n", reg->dmac, reg->dlba);
	SPEW("idst    0x%08x\tidie    0x%08x\n", reg->idst, reg->idie);
}

/*
 * These two functions are named _ugly because they should be called as part of
 * platform initialization, not MMC initialization, however, there's no harm in
 * having them here for the time being.
 */

static void mmc_ungate_clock_ugly(int sdc_no)
{
	a1x_periph_clock_enable(A1X_CLKEN_MMC0 + sdc_no);

}

static void mmc_mux_pins_ugly(int sdc_no)
{
	struct a10_gpio *const pio = (void *)A1X_PIO_BASE;
	struct a10_gpio_port *gpio_f = &pio->port[GPF];

	/* config gpio */
	switch (sdc_no) {
		case 0:
			/* D1-PF0, D0-PF1, CLK-PF2, CMD-PF3, D3-PF4, D4-PF5 */
			write32(0x555, &gpio_f->pul[0]);
			write32(0xaaa, &gpio_f->drv[0]);
			break;
		default:
			return;
	}
}

static int mmc_clk_io_on(int sdc_no)
{
	u32 reg32;
	unsigned int pll5_clk;
	unsigned int divider;


	struct sunxi_mmc_host *mmchost = &mmc_host[sdc_no];

	DEBUG("init mmc %d clock and io\n", sdc_no);

	mmc_mux_pins_ugly(sdc_no);

	mmc_ungate_clock_ugly(sdc_no);
	/* config mod clock */
	//pll5_clk = clock_get_pll5();
	pll5_clk = 24000000;	/* FIXME */
	if (pll5_clk > 400000000)
		divider = 4;
	else
		divider = 3;
	////* write32((0x1 << 31) | (0x2 << 24) | divider, mmchost->mclkreg); */
	reg32 = read32(mmchost->mclkreg);
	reg32 &= ~(SDx_RAT_M_MASK | SDx_RAT_EXP_N_MASK);
	reg32 |= SDx_RAT_M(divider);
	write32((0x1 << 31) | (0x0 << 24) | divider, mmchost->mclkreg);
	mmchost->mod_clk = pll5_clk / (divider + 1);

	dump_mmc_reg(mmchost->reg);

	return 0;
}

static int mmc_update_clk(struct mmc *mmc)
{
	struct sunxi_mmc_host *mmchost = (struct sunxi_mmc_host *)mmc->priv;
	unsigned int cmd;
	unsigned timeout = 0xfffff;

	cmd = (0x1 << 31) | (0x1 << 21) | (0x1 << 13);
	write32(cmd, &mmchost->reg->cmd);
	while ((read32(&mmchost->reg->cmd) & (0x1 << 31)) && timeout--) ;
	if (!timeout)
		return -1;

	write32(read32(&mmchost->reg->rint), &mmchost->reg->rint);

	return 0;
}

static int mmc_config_clock(struct mmc *mmc, unsigned div)
{
	struct sunxi_mmc_host *mmchost = (struct sunxi_mmc_host *)mmc->priv;
	unsigned rval = read32(&mmchost->reg->clkcr);

	/*
	 * CLKCREG[7:0]: divider
	 * CLKCREG[16]:  on/off
	 * CLKCREG[17]:  power save
	 */
	/* Disable Clock */
	rval &= ~(0x1 << 16);
	write32(rval, &mmchost->reg->clkcr);
	if (mmc_update_clk(mmc))
		return -1;

	/* Change Divider Factor */
	rval &= ~(0xff);
	rval |= div;
	write32(rval, &mmchost->reg->clkcr);
	if (mmc_update_clk(mmc))
		return -1;
	/* Re-enable Clock */
	rval |= (0x1 << 16);
	write32(rval, &mmchost->reg->clkcr);

	if (mmc_update_clk(mmc))
		return -1;

	return 0;
}

static void mmc_set_ios(struct mmc *mmc)
{
	struct sunxi_mmc_host *mmchost = (struct sunxi_mmc_host *)mmc->priv;
	unsigned int clkdiv = 0;

	DEBUG("set ios: bus_width: %x, clock: %d, mod_clk: %d\n",
	       mmc->bus_width, mmc->clock, mmchost->mod_clk);

	/* Change clock first */
	clkdiv = (mmchost->mod_clk + (mmc->clock >> 1)) / mmc->clock / 2;
	if (mmc->clock)
		if (mmc_config_clock(mmc, clkdiv)) {
			mmchost->fatal_err = 1;
			return;
		}

	/* Change bus width */
	if (mmc->bus_width == 8)
		write32(0x2, &mmchost->reg->width);
	else if (mmc->bus_width == 4)
		write32(0x1, &mmchost->reg->width);
	else
		write32(0x0, &mmchost->reg->width);
}

static int mmc_core_init(struct mmc *mmc)
{
	struct sunxi_mmc_host *mmchost = (struct sunxi_mmc_host *)mmc->priv;

	/* Reset controller */
	write32(0x7, &mmchost->reg->gctrl);

	return 0;
}

static int mmc_trans_data_by_cpu(struct mmc *mmc, struct mmc_data *data)
{
	struct sunxi_mmc_host *mmchost = (struct sunxi_mmc_host *)mmc->priv;
	unsigned i;
	unsigned byte_cnt = data->blocksize * data->blocks;
	unsigned *buff;
	int timeout = 0xfffff;

	if (data->flags & MMC_DATA_READ) {
		buff = (unsigned int *)data->dest;
		for (i = 0; i < (byte_cnt >> 2); i++) {
			while (--timeout &&
			       (read32(&mmchost->reg->status) & (0x1 << 2))) ;
			if (timeout <= 0) {
				ERROR("Read timeout\n");
				goto out;
			}
			buff[i] = read32((void *)mmchost->database);
			timeout = 0xfffff;
		}
	} else {
		buff = (unsigned int *)data->src;
		for (i = 0; i < (byte_cnt >> 2); i++) {
			while (--timeout &&
			       (read32(&mmchost->reg->status) & (0x1 << 3))) ;
			if (timeout <= 0) {
				ERROR("Write timeout\n");
				goto out;
			}
			write32(buff[i], (void *)mmchost->database);
			timeout = 0xfffff;
		}
	}

 out:
	if (timeout <= 0) {
		ERROR("OOPS! Transfer timed out: %i\n", timeout);
		return -1;
	}

	return 0;
}

static int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data)
{
	struct sunxi_mmc_host *mmchost = (struct sunxi_mmc_host *)mmc->priv;
	unsigned int cmdval = 0x80000000;
	signed int timeout = 0;
	int error = 0;
	unsigned int status = 0;
	unsigned int usedma = 0;
	unsigned int bytecnt = 0;

	SPEW("mmc_send_cmd\n");
	if (mmchost->fatal_err)
		return -1;
	if (cmd->resp_type & MMC_RSP_BUSY)
		DEBUG("mmc cmd %d check rsp busy\n", cmd->cmdidx);
	if (cmd->cmdidx == 12)
		return 0;

	/*
	 * CMDREG
	 * CMD[5:0]     : Command index
	 * CMD[6]       : Has response
	 * CMD[7]       : Long response
	 * CMD[8]       : Check response CRC
	 * CMD[9]       : Has data
	 * CMD[10]      : Write
	 * CMD[11]      : Steam mode
	 * CMD[12]      : Auto stop
	 * CMD[13]      : Wait previous over
	 * CMD[14]      : About cmd
	 * CMD[15]      : Send initialization
	 * CMD[21]      : Update clock
	 * CMD[31]      : Load cmd
	 */
	if (!cmd->cmdidx)
		cmdval |= (0x1 << 15);
	if (cmd->resp_type & MMC_RSP_PRESENT)
		cmdval |= (0x1 << 6);
	if (cmd->resp_type & MMC_RSP_136)
		cmdval |= (0x1 << 7);
	if (cmd->resp_type & MMC_RSP_CRC)
		cmdval |= (0x1 << 8);

	if (data) {
		if ((u32) data->dest & 0x3) {
			error = -1;
			goto out;
		}

		cmdval |= (0x1 << 9) | (0x1 << 13);
		if (data->flags & MMC_DATA_WRITE)
			cmdval |= (0x1 << 10);
		if (data->blocks > 1)
			cmdval |= (0x1 << 12);
		write32(data->blocksize, &mmchost->reg->blksz);
		write32(data->blocks * data->blocksize, &mmchost->reg->bytecnt);
	}

	SPEW("mmc %d, cmd %d(0x%08x), arg 0x%08x\n",
	       mmchost->mmc_no, cmd->cmdidx, cmdval | cmd->cmdidx, cmd->cmdarg);
	write32(cmd->cmdarg, &mmchost->reg->arg);

	if (!data)
		write32(cmdval | cmd->cmdidx, &mmchost->reg->cmd);

	/*
	 * transfer data and check status
	 * STATREG[2] : FIFO empty
	 * STATREG[3] : FIFO full
	 */
	if (data) {
		int ret = 0;

		bytecnt = data->blocksize * data->blocks;
		DEBUG("trans data %d bytes\n", bytecnt);


		write32(read32(&mmchost->reg->gctrl) | 0x1 << 31,
			&mmchost->reg->gctrl);
		write32(cmdval | cmd->cmdidx, &mmchost->reg->cmd);
		ret = mmc_trans_data_by_cpu(mmc, data);

		if (ret) {
			error = read32(&mmchost->reg->rint) & 0xbfc2;
			error = CB_MMC_TIMEOUT;
			goto out;
		}
	}

	timeout = 0xfffff;
	do {
		status = read32(&mmchost->reg->rint);
		if (!timeout-- || (status & 0xbfc2)) {
			error = status & 0xbfc2;
			DEBUG("cmd timeout %x\n", error);
			error = CB_MMC_TIMEOUT;
			goto out;
		}
	} while (!(status & 0x4));

	if (data) {
		unsigned done = 0;
		timeout = usedma ? 0xffff * bytecnt : 0xffff;
		////DEBUG("cacl timeout %x\n", timeout);
		do {
			status = read32(&mmchost->reg->rint);
			if (!timeout-- || (status & 0xbfc2)) {
				error = status & 0xbfc2;
				DEBUG("data timeout %x\n", error);
				error = CB_MMC_TIMEOUT;
				goto out;
			}
			if (data->blocks > 1)
				done = status & (0x1 << 14);
			else
				done = status & (0x1 << 3);
		} while (!done);
	}

	if (cmd->resp_type & MMC_RSP_BUSY) {
		timeout = 0xfffff;
		do {
			status = read32(&mmchost->reg->status);
			if (!timeout--) {
				DEBUG("busy timeout\n");
				error = CB_MMC_TIMEOUT;
				goto out;
			}
		} while (status & (1 << 9));
	}

	if (cmd->resp_type & MMC_RSP_136) {
		cmd->response[0] = read32(&mmchost->reg->resp3);
		cmd->response[1] = read32(&mmchost->reg->resp2);
		cmd->response[2] = read32(&mmchost->reg->resp1);
		cmd->response[3] = read32(&mmchost->reg->resp0);
		SPEW("mmc resp 0x%08x 0x%08x 0x%08x 0x%08x\n",
		       cmd->response[3], cmd->response[2],
		       cmd->response[1], cmd->response[0]);
	} else {
		cmd->response[0] = read32(&mmchost->reg->resp0);
		SPEW("mmc resp 0x%08x\n", cmd->response[0]);
	}
 out:
	if (data && usedma) {
		/* IDMASTAREG
		 * IDST[0] : idma tx int
		 * IDST[1] : idma rx int
		 * IDST[2] : idma fatal bus error
		 * IDST[4] : idma descriptor invalid
		 * IDST[5] : idma error summary
		 * IDST[8] : idma normal interrupt sumary
		 * IDST[9] : idma abnormal interrupt sumary
		 */
		status = read32(&mmchost->reg->idst);
		write32(status, &mmchost->reg->idst);
		write32(0, &mmchost->reg->idie);
		write32(0, &mmchost->reg->dmac);
		write32(read32(&mmchost->reg->gctrl) & ~(0x1 << 5),
			&mmchost->reg->gctrl);
	}
	if (error < 0) {
		ERROR("OOPS! MMC command failed (code %i)\n", error);
		write32(0x7, &mmchost->reg->gctrl);
		mmc_update_clk(mmc);
	}
	write32(0xffffffff, &mmchost->reg->rint);
	write32(read32(&mmchost->reg->gctrl) | (1 << 1), &mmchost->reg->gctrl);

	return error;
}

static int mmc_resource_init(int sdc_no)
{
	struct sunxi_mmc_host *mmchost = &mmc_host[sdc_no];
	struct a10_ccm *ccm = (void *)A1X_CCM_BASE;

	SPEW("Init mmc %d resource\n", sdc_no);

	switch (sdc_no) {
		case 0:
			mmchost->reg = (struct sunxi_mmc *)A1X_MMC0_BASE;
			mmchost->mclkreg = &ccm->sd0_clk_cfg;
			break;
		default:
			DEBUG("Wrong mmc number %d\n", sdc_no);
			return -1;
	}
	mmchost->database = (unsigned int)mmchost->reg + 0x100;
	mmchost->mmc_no = sdc_no;

	return 0;
}

int sunxi_mmc_init(int sdc_no, struct mmc **mmcp)
{
	struct mmc *mmc;

	if (sdc_no > ARRAY_SIZE(mmc_dev)) {
		*mmcp = NULL;
		return CB_ERR_ARG;
	}

	memset(&mmc_dev[sdc_no], 0, sizeof(struct mmc));
	memset(&mmc_host[sdc_no], 0, sizeof(struct sunxi_mmc_host));
	mmc = &mmc_dev[sdc_no];

	DEBUG("sunxi MMC init.\n");

	/* FIXME: */
	//sprintf(mmc->name, "SUNXI SD/MMC");
	mmc->priv = &mmc_host[sdc_no];
	mmc->send_cmd = mmc_send_cmd;
	mmc->set_ios = mmc_set_ios;
	mmc->init = mmc_core_init;

	mmc->voltages = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->host_caps = MMC_MODE_4BIT;
	mmc->host_caps |= MMC_MODE_HS_52MHz | MMC_MODE_HS;

	mmc->f_min = 400000;
	mmc->f_max = 52000000;

	mmc_resource_init(sdc_no);
	mmc_clk_io_on(sdc_no);

	/* FIXME: */
	mmc_register(mmc);
	*mmcp = mmc;

	return 0;
}
