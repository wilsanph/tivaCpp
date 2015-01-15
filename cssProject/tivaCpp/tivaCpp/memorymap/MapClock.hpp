/*
 * MapClock.hpp
 *
 *  Created on: 27/12/2014
 *      Author: USER01
 */

#ifndef MAPCLOCK_HPP_
#define MAPCLOCK_HPP_

#pragma once

#include "../common.hpp"



namespace MapClock
{

	struct ClockRegs
	{
		u32 DID0;//0x000
		u32 DID1;//0x004
		u32 reserved1[10];//[0x008 - 0x02c]
		u32 PBORCTL;//0x030
		u32 reserved2[7];//[0x034 - 0x04c]
		u32 RIS;//0x050
		u32 IMC;//0x054
		u32 MISC;//0x058
		u32 RESC;//0x05c
		u32 RCC;//0x060
		u32 reserved3[2];//[0x064 - 0x068]
		u32 GPIOHBCTL;//0x006c
		u32 RCC2;//0x070
		u32 reserved4[2];//[0x074 - 0x078]
		u32 MOSCCTL;//0x07c
		u32 reserved5[49];//[0x080 - 0x140]
		u32 DSLPCLKCFG;//0x144
		u32 reserved6[1];//[0x148]
		u32 SYSPROP;//0x14c
		u32 PIOSCCAL;//0x150
		u32 PIOSCSTAT;//0x154
		u32 reserved7[2];//[0x158 - 0x15c]
		u32 PLLFREQ0;//0x160
		u32 PLLFREQ1;//0x164
		u32 PLLSTAT;//0x168
		u32 reserved8[101];//[0x16c - 0x29c]
		u32 PPWD;//0x300
		u32 PPTIMER;//0x304
		u32 PPGPIO;//0x308
		u32 PPDMA;//0x30c
		u32 reserved9[1];//[0x310]
		u32 PPHIB;//0x314
		u32 PPUART;//0x318
		u32 PPSSI;//0x31c
		u32 PPI2C;//0x320
		u32 reserved10[1];//[0x324]
		u32 PPUSB;//0x328
		u32 reserved11[2];//[0x32c - 0x330]
		u32 PPCAN;//0x334
		u32 PPADC;//0x338
		u32 PPACMP;//0x33c
		u32 PPPWM;//0x340
		u32 PPQEI;//0x344
		u32 reserved12[4];//[0x348 - 0x354]
		u32 PPEEPROM;//0x358
		u32 PPWTIMER;//0x35c
		u32 reserved13[104];//[0x360 - 0x4fc]
		u32 SRWD;//0x500
		u32 SRTIMER;//0x504
		u32 SRGPIO;//0x508
		u32 SRDMA;//0x50c
		u32 reserved14[1];//[0x510]
		u32 SRHIB;//0x514
		u32 SRUART;//0x518
		u32 SRSSI;//0x51c
		u32 SRI2C;//0x520
		u32 reserved15[1];//[0x524]
		u32 SRUSB;//0x528
		u32 reserved16[2];//[0x52c - 0x530]
		u32 SRCAN;//0x534
		u32 SRADC;//0x538
		u32 SRACMP;//0x53c
		u32 reserved17[6];//[0x540 - 0x554]
		u32 SREEPROM;//0x558
		u32 SRWTIMER;//0x55c
		u32 reserved18[40];//[0x560 - 0x5fc]
		u32 RCGCWD;//0x600
		u32 RCGCTIMER;//0x604
		u32 RCGCGPIO;//0x608
		u32 RCGCDMA;//0x60c
		u32 reserved19[1];//[0x610]
		u32 RCGCHIB;//0x614
		u32 RCGCUART;//0x618
		u32 RCGCSSI;//0x61c
		u32 RCGCI2C;//0x620
		u32 reserved20[1];//[0x624]
		u32 RCGCUSB;//0x628
		u32 reserved21[2];//[0x62c - 0x630]
		u32 RCGCCAN;//0x634
		u32 RCGCADC;//0x638
		u32 RCGCACMP;//0x63c
		u32 RCGCPWM;//0x640
		u32 RCGCQEI;//0x644
		u32 reserved22[4];//[0x648 - 0x654]
		u32 RCGCEEPROM;//0x658
		u32 RCGCWTIMER;//0x65c
		u32 reserved23[40];//[0x660 - 0x6fc]
		u32 SCGCWD;//0x700
		u32 SCGCTIMER;//0x704
		u32 SCGCGPIO;//0x708
		u32 SCGCDMA;//0x70c
		u32 reserved24[1];//[0x710]
		u32 SCGCHIB;//0x714
		u32 SCGCUART;//0x718
		u32 SCGCSSI;//0x71c
		u32 SCGCI2C;//0x720
		u32 reserved25[1];//[0x724]
		u32 SCGCUSB;//0x728
		u32 reserved26[2];//[0x72c - 0x730]
		u32 SCGCCAN;//0x734
		u32 SCGCADC;//0x738
		u32 SCGCACMP;//0x73c
		u32 reserved27[6];//[0x740 - 0x754]
		u32 SCGCEEPROM;//0x758
		u32 SCGCWTIMER;//0x75c
		u32 reserved28[40];//[0x760 - 0x7fc]
		u32 DCGCWD;//0x800
		u32 DCGCTIMER;//0x804
		u32 DCGCGPIO;//0x808
		u32 DCGCDMA;//0x80c
		u32 reserved29[1];//[0x810]
		u32 DCGCHIB;//0x814
		u32 DCGCUART;//0x818
		u32 DCGCSSI;//0x81c
		u32 DCGCI2C;//0x820
		u32 reserved30[1];//[0x824]
		u32 DCGCUSB;//0x828
		u32 reserved31[2];//[0x82c - 0x830]
		u32 DCGCCAN;//0x834
		u32 DCGCADC;//0x838
		u32 DCGCACMP;//0x83c
		u32 reserved32[6];//[0x840 - 0x854]
		u32 DCGCEEPROM;//0x858
		u32 DCGCWTIMER;//0x85c
		u32 reserved33[104];//[0x860 - 0x9fc]
		u32 PRWD;//0xa00
		u32 PRTIMER;//0xa04
		u32 PRGPIO;//0xa08
		u32 PRDMA;//0xa0c
		u32 reserved34[1];//[0xa10]
		u32 PRHIB;//0xa14
		u32 PRUART;//0xa18
		u32 PRSSI;//0xa1c
		u32 PRI2C;//0xa20
		u32 reserved35[1];//[0xa24]
		u32 PRUSB;//0xa28
		u32 reserved36[2];//[0xa2c - 0xa30]
		u32 PRCAN;//0xa34
		u32 PRADC;//0xa38
		u32 PRACMP;//0xa3c
		u32 reserved37[6];//[0xa40 - 0xa54]
		u32 PREEPROM;//0xa58
		u32 PRWTIMER;//0xa5c
	};


}




#endif /* MAPCLOCK_HPP_ */
