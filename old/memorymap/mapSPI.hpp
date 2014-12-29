/*
 * mapSPI.h
 *
 *  Created on: Aug 21, 2013
 *      Author: wilbert
 */
#pragma once

#include "../common.h"

namespace mapSPI
{


	struct SPIregs
	{
		u32 SSICR0;//0x000
		u32 SSICR1;//0x004
		u32 SSIDR;//0x008
		u32 SSISR;//0x00c
		u32 SSICPSR;//0x010
		u32 SSIIM;//0x014
		u32 SSIRIS;//0x018
		u32 SSIMIS;//0x01c
		u32 SSIICR;//0x020
		u32 SSIDMACTL;//0x024
		u32 reserved1[1000];//[0x028 - 0xfc4]
		u32 SSICC;//0xfc8
		u32 reserved2[1];//[0xfcc]
		u32 SSIPeriphlD4;//0xfd0
		u32 SSIPeriphlD5;//0xfd4
		u32 SSIPeriphlD6;//0xfd8
		u32 SSIPeriphlD7;//0xfdc
		u32 SSIPeriphlD0;//0xfe0
		u32 SSIPeriphlD1;//0xfe4
		u32 SSIPeriphlD2;//0xfe8
		u32 SSIPeriphlD3;//0xfec
		u32 SSIPCellID0;//0xff0
		u32 SSIPCellID1;//0xff4
		u32 SSIPCellID2;//0xff8
		u32 SSIPCellID3;//0xffc
	};

}
