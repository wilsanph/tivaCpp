/*
 * MapUart.h
 *
 *  Created on: 26/07/2013
 *      Author: wilbert
 */
#pragma once

#include "../common.h"

namespace mapUart
{

	struct UartRegs
	{
		u32 UARTDR;//0x0000
		u32 UARTRSR_ECR;//0x0004 - 8 c 10 14
		u32 reserved1[4];//[0x0008 - 0x0014]
		u32 UARTFR;//0x0018
		u32 reserved2[1];//[0x001c]
		u32 UARTILPR;//0x0020
		u32 UARTIBRD;//0x0024
		u32 UARTFBRD;//0x0028
		u32 UARTLCRH;//0x002c
		u32 UARTCTL;//0x0030
		u32 UARTIFLS;//0x0034
		u32 UARTIM;//0x0038
		u32 UARTRIS;//0x003c
		u32 UARTMIS;//0x0040
		u32 UARTICR;//0x0044
		u32 UARTDMACTL;//0x0048
		u32 reserved3[17];//[0x004c -0x008c]
		u32 UARTLCTL;//0x0090
		u32 UARTLSS;//0x0094
		u32 UARTLTIM;//0x0098
		u32 reserved4[2];//[0x009c-0x00a0]
		u32 UART9BITADDR;//0x00a4
		u32 UART9BITAMASK;//0x00a8
		u32 reserved5[965];//[0x00ac-0xfbc]
		u32 UARTPP;//0xfc0
		u32 reserved6[1];//[0xfc4]
		u32 UARTCC;//0xfc8
		u32 reserved7[1];//[0xfcc]
		u32 UARTPeriphID4;//0xfd0
		u32 UARTPeriphID5;//0xfd4
		u32 UARTPeriphID6;//0xfd8
		u32 UARTPeriphID7;//0xfdc
		u32 UARTPeriphID0;//0xfe0
		u32 UARTPeriphID1;//0xfe4
		u32 UARTPeriphID2;//0xfe8
		u32 UARTPeriphID3;//0xfec
		u32 UARTPCellID0;//0xff0
		u32 UARTPCellID1;//0xff4
		u32 UARTPCellID2;//0xff8
		u32 UARTPCellID3;//0xffc
	};

}


