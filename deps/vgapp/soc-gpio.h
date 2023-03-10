/*
 * pinctrl/ingenic/pinctrl-ingenic.c
 *
 * Copyright 2015 Ingenic Semiconductor Co.,Ltd
 *
 * Author: cli <chen.li@inegnic.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __INGENIC_GPIO_H__
#define __INGENIC_GPIO_H__

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include <soc/base.h>
#include <soc/io.h>
#include <config.h>

#define u32 uint32_t
#define u16 uint16_t
#define u8  uint8_t
enum gpio_function {
	GPIO_FUNC_0	= 0x00,  //0000, GPIO as function 0 / device 0
	GPIO_FUNC_1	= 0x01,  //0001, GPIO as function 1 / device 1
	GPIO_FUNC_2	= 0x02,  //0010, GPIO as function 2 / device 2
	GPIO_FUNC_3	= 0x03,  //0011, GPIO as function 3 / device 3
	GPIO_OUTPUT0	= 0x04,  //0100, GPIO output low  level
	GPIO_OUTPUT1	= 0x05,  //0101, GPIO output high level
	GPIO_INPUT	= 0x06,  //0110, GPIO as input
	GPIO_INT_LO 	= 0x08,  //1100, Low  Level trigger interrupt
	GPIO_INT_HI 	= 0x09,  //1101, High Level trigger interrupt
	GPIO_INT_FE 	= 0x0a,  //1110, Fall Edge trigger interrupt
	GPIO_INT_RE 	= 0x0b,  //1111, Rise Edge trigger interrupt
	GPIO_INT_RE_FE 	= 0x1a,  //Fall&Rise Edge trigger interrupt
};

#define PxPIN           0x00   /* PIN Level Register */
#define PxINT           0x10   /* Port Interrupt Register */
#define PxINTS          0x14   /* Port Interrupt Set Register */
#define PxINTC          0x18   /* Port Interrupt Clear Register */
#define PxMSK           0x20   /* Port Interrupt Mask Reg */
#define PxMSKS          0x24   /* Port Interrupt Mask Set Reg */
#define PxMSKC          0x28   /* Port Interrupt Mask Clear Reg */
#define PxPAT1          0x30   /* Port Pattern 1 Set Reg. */
#define PxPAT1S         0x34   /* Port Pattern 1 Set Reg. */
#define PxPAT1C         0x38   /* Port Pattern 1 Clear Reg. */
#define PxPAT0          0x40   /* Port Pattern 0 Register */
#define PxPAT0S         0x44   /* Port Pattern 0 Set Register */
#define PxPAT0C         0x48   /* Port Pattern 0 Clear Register */
#define PxFLG           0x50   /* Port Flag Register */
#define PxFLGC          0x58   /* Port Flag clear Register */

/* TODO: move these regs to soc special. */

#if defined(CONFIG_SOC_X1520)
	#define PxPEN	0x60
	#define PxPENS	0x64
	#define PxPENC	0x68
#elif defined(CONFIG_SOC_X1600)
	#define PxPEN	0x70
	#define PxPENS	0x74
	#define PxPENC	0x78
#else
	#define PxPEN	-1
	#define PxPENS	-1
	#define PxPENC	-1
#endif

/* Note: Not All Socs have these regs. */
#if defined(CONFIG_SOC_X2000_V12) || defined(CONFIG_SOC_X2000)	\
    || defined(CONFIG_SOC_X2100) || defined(CONFIG_SOC_M300)	\
    || defined(CONFIG_SOC_X1600)
	#define PxEDG		0x70	/* PORT Dual-Edge Interrupt Register */
	#define PxEDGS		0x74	/* PORT Dual-Edge Interrupt Register Set */
	#define PxEDGC		0x78	/* PORT Dual-Edge Interrupt Register Clear */
#else
	#define PxEDG		-1
	#define PxEDGS		-1
	#define PxEDGC		-1
#endif


/* Soc Secial. X2000 s.*/
#if defined(CONFIG_SOC_X2000_V12) || defined(CONFIG_SOC_X2000)	\
    || defined(CONFIG_SOC_X2100) || defined(CONFIG_SOC_M300)	\
    || defined(CONFIG_SOC_X1600)
	#define PxPU		0x80	/* PORT PULL-UP State Register */
	#define PxPUS		0x84	/* PORT PULL-UP State Register Set */
	#define PxPUC		0x88	/* PORT PULL-UP State Register Clear */
	#define PxPD		0x90	/* PORT PULL-DOWN State Register */
	#define PxPDS		0x94	/* PORT PULL-DOWN State Register Set */
	#define PxPDC		0x98	/* PORT PULL-DOWN State Register Clear */

#elif defined(CONFIG_SOC_X2500)
/* Soc Secial. T40/X2500 s.*/
	#define PxPU		0x110	/* PORT PULL-UP State Register */
	#define PxPUS		0x114	/* PORT PULL-UP State Register Set */
	#define PxPUC		0x118	/* PORT PULL-UP State Register Clear */
	#define PxPD		0x120	/* PORT PULL-DOWN State Register */
	#define PxPDS		0x124	/* PORT PULL-DOWN State Register Set */
	#define PxPDC		0x128	/* PORT PULL-DOWN State Register Clear */
#else
	#define PxPU		-1	/* PORT PULL-UP State Register */
	#define PxPUS		-1	/* PORT PULL-UP State Register Set */
	#define PxPUC		-1	/* PORT PULL-UP State Register Clear */
	#define PxPD		-1	/* PORT PULL-DOWN State Register */
	#define PxPDS		-1	/* PORT PULL-DOWN State Register Set */
	#define PxPDC		-1	/* PORT PULL-DOWN State Register Clear */
#endif


#if defined(CONFIG_SOC_X2000_V12) || defined(CONFIG_SOC_X2000)	\
    || defined(CONFIG_SOC_X2100) || defined(CONFIG_SOC_M300)
/* Soc Special. X2000 */
	#define PXDS0		0xA0   /* PORT Drive Strength State Register0*/
	#define PXDS0S		0xA4   /* PORT Drive Strength State set Register0*/
	#define PXDS0C		0xA8   /* PORT Drive Strength State clear Register0*/
	#define PXDS1		0xB0   /* PORT Drive Strength State Register1*/
	#define PXDS1S		0xB4   /* PORT Drive Strength State set Register1*/
	#define PXDS1C		0xB8   /* PORT Drive Strength State clear Register1*/
	#define PXDS2		0xC0   /* PORT Drive Strength State Register2*/
	#define PXDS2S		0xC4   /* PORT Drive Strength State set Register2*/
	#define PXDS2C		0xC8   /* PORT Drive Strength State clear Register2*/

#elif defined(CONFIG_SOC_X2500)
/* T40/X2500. */
	#define PXDS0		0x130   /* PORT Drive Strength State Register0*/
	#define PXDS0S		0x134   /* PORT Drive Strength State set Register0*/
	#define PXDS0C		0x138   /* PORT Drive Strength State clear Register0*/
	#define PXDS1		0x140   /* PORT Drive Strength State Register1*/
	#define PXDS1S		0x144   /* PORT Drive Strength State set Register1*/
	#define PXDS1C		0x148   /* PORT Drive Strength State clear Register1*/
	#define PXDS2		0x150   /* PORT Drive Strength State Register2*/
	#define PXDS2S		0x154   /* PORT Drive Strength State set Register2*/
	#define PXDS2C		0x158   /* PORT Drive Strength State clear Register2*/
#else
	#define PXDS0		-1   /* PORT Drive Strength State Register0*/
	#define PXDS0S		-1   /* PORT Drive Strength State set Register0*/
	#define PXDS0C		-1   /* PORT Drive Strength State clear Register0*/
	#define PXDS1		-1   /* PORT Drive Strength State Register1*/
	#define PXDS1S		-1   /* PORT Drive Strength State set Register1*/
	#define PXDS1C		-1   /* PORT Drive Strength State clear Register1*/
	#define PXDS2		-1   /* PORT Drive Strength State Register2*/
	#define PXDS2S		-1   /* PORT Drive Strength State set Register2*/
	#define PXDS2C		-1   /* PORT Drive Strength State clear Register2*/
#endif

/* Soc Special. */

#if defined(CONFIG_SOC_X2000_V12) || defined(CONFIG_SOC_X2000)	\
    || defined(CONFIG_SOC_X2100) || defined(CONFIG_SOC_M300)
	#define PxSR		0xD0    /* PORT Slew Rate Register */
	#define PxSRS		0xD4	/* PORT Slew Rate Register Set */
	#define PxSRC		0xD8	/* PORT Slew Rate Register Clear */
#elif defined(CONFIG_SOC_X2500)
	#define PxSR		0x160    /* PORT Slew Rate Register */
	#define PxSRS		0x164	/* PORT Slew Rate Register Set */
	#define PxSRC		0x168	/* PORT Slew Rate Register Clear */
#else
	#define PxSR		-1    /* PORT Slew Rate Register */
	#define PxSRS		-1	/* PORT Slew Rate Register Set */
	#define PxSRC		-1	/* PORT Slew Rate Register Clear */
#endif

#if defined(CONFIG_SOC_X2000_V12) || defined(CONFIG_SOC_X2000)	\
    || defined(CONFIG_SOC_X2100) || defined(CONFIG_SOC_M300)
	#define PxSMT		0xE0	/* PORT Schmitt Trigger Register */
	#define PxSMTS		0xE4	/* PORT Schmitt Trigger Register Set */
	#define PxSMTC		0xE8	/*  PORT Schmitt Trigger Register Clear */
#elif defined(CONFIG_SOC_X2500)
	#define PxSMT		0x170    /* PORT Slew Rate Register */
	#define PxSMTS		0x174	/* PORT Slew Rate Register Set */
	#define PxSMTC		0x178	/* PORT Slew Rate Register Clear */
// TODO: X2500 has different schmit registers for GPC.

#else
	#define PxSMT		-1    /* PORT Slew Rate Register */
	#define PxSMTS		-1	/* PORT Slew Rate Register Set */
	#define PxSMTC		-1	/* PORT Slew Rate Register Clear */
#endif


#define PSHADOW_OFF(regsoffset)		(7*(regsoffset))
#define PZGIDLD         0xF0   /* GPIOZ Group ID to load */

#define PIN_NAMES_LEN		10
#define MAX_GPIOS_ON_CHIP	32
#define MAX_FUNCTIONS_ON_GPIO	4
#define PIN_ARGS_FROM_INDEX	0
#define PIN_ARGS_TO_INDEX	1
#define PIN_ARGS_CFG_INDEX	2

static inline uint32_t pin_bitmap(uint32_t from, uint32_t to)
{
	if (to == 31)
		return ~((1<<(from))-1);
	return ((~((1<<(from))-1))&((1 << ((to)+1))-1));
}

static inline unsigned bit_count(unsigned v)
{
	unsigned int c;
	for (c = 0; v; c++)
		v &= v - 1;
	return c;
}
/*ingenic gpio chip*/
struct ingenic_gpio_chip {
	char				name[4];			/*name format "GPX"(X = 'A' + idx)*/
    uint32_t        ngpio;
	u8				idx;				    /*gpio index of this chip*/
	struct ingenic_pinctrl		*pctl;
	pthread_mutex_t			lock;				/*gpio func write lock*/
	uint32_t				*mcu_gpio_reg;			/*used for gpio irq to mcu
									            mcu's pending register*/
	uint32_t				used_pins_bitmap;			/*bitmap of pins for been had requested*/
	uint32_t				filter_bitmap;			/*bitmap of pins filter support*/
	uint32_t				pull_bitmap;			/*bitmap of pins pill support*/
};

/*soc private data*/
struct ingenic_priv {
	bool				have_shadow;		/*support shadow register or not*/
	bool				have_filter;		/*support input pin filter of nor*/
	bool				pullen_set;		/*set bit to enable pull function.*/
	bool				voltage_switchable;	/*ports support 1.8v and 3.3v switch.*/
	bool				dual_edge_interrupt ;	/*support Dual-Edge Interrupt.*/
	bool				pull_tristate;		/*support pullup/pulldown/hiz settable.*/
	bool				have_ds;		/*support drive strength settings.*/
	bool				have_slew;		/*support drive strength settings.*/
	bool				have_schmit;		/*support drive strength settings.*/
	int (*set_filter)(struct ingenic_gpio_chip *jzgc,	/*set input pin filter function*/
			unsigned pin,
			u16 filter);
	ssize_t (*dump_filter)(struct ingenic_pinctrl *pctl,
			char *buf,
			ssize_t size);
};

struct ingenic_pinctrl {
	void			            *io_base;
	pthread_mutex_t			    shadow_lock;		        /*shadow register access lock*/
	pthread_mutex_t			    lock;		        /*shadow register access lock*/
	struct ingenic_gpio_chip	*gpio_chips;		/*gpio chips of this pinctrl*/
	unsigned			        num_chips;		            /*num gpio chips*/
	unsigned			        total_pins;		            /*total pins of this pinctrl*/
	uint32_t				    group_regs_offset;		/* gpio group regs offset get from dts  */
	const struct ingenic_priv   *priv;			/*soc data*/
};

static inline uint32_t ingenic_gpio_readl(struct ingenic_gpio_chip *chip, int offset)
{
	struct ingenic_pinctrl *pctl = chip->pctl;
	return readl((volatile unsigned int)pctl->io_base + (chip->idx * pctl->group_regs_offset) + offset);
}

static inline void ingenic_gpio_writel(struct ingenic_gpio_chip *chip, int offset, int value)
{
	struct ingenic_pinctrl *pctl = chip->pctl;
	writel(value , (volatile unsigned int)pctl->io_base + (chip->idx * pctl->group_regs_offset) + offset);
}

static inline void ingenic_gpio_shadow_fill(struct ingenic_gpio_chip *chip, int offset, int value)
{
	struct ingenic_pinctrl *pctl = chip->pctl;
	writel(value, (volatile unsigned int)pctl->io_base + PSHADOW_OFF(pctl->group_regs_offset)+ offset);
}

static inline void ingenic_gpio_shadow_writel(struct ingenic_gpio_chip *chip)
{
	struct ingenic_pinctrl *pctl = chip->pctl;
	writel(chip->idx, (volatile unsigned int)pctl->io_base + PSHADOW_OFF(pctl->group_regs_offset) + PZGIDLD);
}
#endif /*__PINCTRL_INGENIC_H__*/
