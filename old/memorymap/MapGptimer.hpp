/*
 * GPTimer.hpp
 *
 *  Created on: 03/07/2013
 *      Author: wilbert
 */
#pragma once

#include "../common.h"


namespace MapGpTimer{

	struct GPTimerRegs{
		u32 GPTMCFG;//0x000
		u32 GPTMTAMR;//0x004
		u32 GPTMTBMR;//0x008
		u32 GPTMCTL;//0x00c
		u32 GPTMSYNC;//0x010
		u32 reserved_1;//0x014
		u32 GPTMIMR;//0x018
		u32 GPTMRIS;//0x01c
		u32 GPTMMIS;//0x020
		u32 GPTMICR;//0x024
		u32 GPTMTAILR;//0x028
		u32 GPTMTBILR;//0x02c
		u32 GPTMTAMATCHR;//0x030
		u32 GPTMTBMATCHR;//0x034
		u32 GPTMTAPR;//0x038
		u32 GPTMTBPR;//0x03c
		u32 GPTMTAPMR;//0x040
		u32 GPTMTBPMR;//0x044
		u32 GPTMTAR;//0x048
		u32 GPTMTBR;//0x04c
		u32 GPTMTAV;//0x050
		u32 GPTMTBV;//0x054
		u32 GPTMRTCPD;//0x058
		u32 GPTMTAPS;//0x05c
		u32 GPTMTBPS;//0x060
		u32 GPTMTAPV;//0x064
		u32 GPTMTBPV;//0x068
		u32 reserved_2;//[all this huge gap xD!!!]
		u32 GPTMPP;//0xfc0
	};

}

