
#pragma once

#include "../common.h"

namespace mapCore
{
	enum _coreAddress
	{
		coreAddress = 0xe000e000
	};

	namespace offset
	{
		enum _offset
		{
			systick = 0x0010,
			nvic	= 0x0100
		};
	}

	struct SysTickRegs
	{
		u32 STCTRL;
		u32 STRELOAD;
		u32 STCURRENT;
	};

	struct NVICRegs
	{
		u32 EN0;//0x0100
		u32 EN1;//0x0104
		u32 EN2;//0x0108
		u32 EN3;//0x010c
		u32 EN4;//0x0110
		u32 reserved1[27];//[0x0114 - 0x017c]
		u32 DIS0;//0x0180
		u32 DIS1;//0x0184
		u32 DIS2;//0x0188
		u32 DIS3;//0x018c
		u32 DIS4;//0x0190
		u32 reserved2[27];//[0x0194 - 0x01fc]
		u32 PEND0;//0x0200
		u32 PEND1;//0x0204
		u32 PEND2;//0x0208
		u32 PEND3;//0x020c
		u32 PEND4;//0x0210
		u32 reserved3[27];//[0x0214 - 0x027c]
		u32 UNPEND0;//0x0280
		u32 UNPEND1;//0x0284
		u32 UNPEND2;//0x0288
		u32 UNPEND3;//0x028c
		u32 UNPEND4;//0x0290
		u32 reserved4[27];//[0x0294 - 0x02fc]
		u32 ACTIVE0;//0x0300
		u32 ACTIVE1;//0x0304
		u32 ACTIVE2;//0x0308
		u32 ACTIVE3;//0x030c
		u32 ACTIVE4;//0x0310
		u32 reserved5[59];//[0x0314 - 0x03fc]
		u32 PRI0;
		u32 PRI1;
		u32 PRI2;
		u32 PRI3;
		u32 PRI4;
		u32 PRI5;
		u32 PRI6;
		u32 PRI7;
		u32 PRI8;
		u32 PRI9;
		u32 PRI10;
		u32 PRI11;
		u32 PRI12;
		u32 PRI13;
		u32 PRI14;
		u32 PRI15;
		u32 PRI16;
		u32 PRI17;
		u32 PRI18;
		u32 PRI19;
		u32 PRI20;
		u32 PRI21;
		u32 PRI22;
		u32 PRI23;
		u32 PRI24;
		u32 PRI25;
		u32 PRI26;
		u32 PRI27;
		u32 PRI28;
		u32 PRI29;
		u32 PRI30;
		u32 PRI31;
		u32 PRI32;
		u32 PRI33;
		u32 PRI34;
		u32 reserved6[669];
		u32 SWTRIG;
	};

}

