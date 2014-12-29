/*
 * MapGpio.hpp
 *
 *  Created on: 27/12/2014
 *      Author: USER01
 */

#ifndef MAPGPIO_HPP_
#define MAPGPIO_HPP_

#pragma once

#include "../common.hpp"

namespace MapGpio {

	struct GpioRegs{
		u32 GPIODATA;//0x000
		u32 rsvd1[255];//[0x004-0x400>
		u32 GPIODIR;//0x400
		u32 GPIOIS;//0x404
		u32 GPIOIBE;//0x408
		u32 GPIOIEV;//0x40c
		u32 GPIOIM;//0x410
		u32 GPIORIS;//0x414
		u32 GPIOMIS;//0x418
		u32 GPIOICR;//0x41c
		u32 GPIOAFSEL;//0x420
		u32 rsvd2[55];//[0x424-0x500>
		u32 GPIODR2R;//0x500
		u32 GPIODR4R;//0x504
		u32 GPIODR8R;//0x508
		u32 GPIOODR;//0x50c
		u32 GPIOPUR;//0x510
		u32 GPIOPDR;//0x514
		u32 GPIOSLR;//0x518
		u32 GPIODEN;//0x51c
		u32 GPIOLOCK;//0x520
		u32 GPIOCR;//0x524
		u32 GPIOAMSEL;//0x528
		u32 GPIOPCTL;//0x52c
		u32 GPIOADCCTL;//0x530
		u32 GPIODMACTL;//0x534
		u32 rsvd3[679];//[0x538-0xfd0>
		u32 GPIOPeriphID4;//0xfd0
		u32 GPIOPeriphID5;//0xfd4
		u32 GPIOPeriphID6;//0xfd8
		u32 GPIOPeriphID7;//0xfdc
		u32 GPIOPeriphID0;//0xfe0
		u32 GPIOPeriphID1;//0xfe4
		u32 GPIOPeriphID2;//0xfe8
		u32 GPIOPeriphID3;//0xfec
		u32 GPIOPCellID0;//0xff0
		u32 GPIOPCellID1;//0xff4
		u32 GPIOPCellID2;//0xff8
		u32 GPIOPCellID3;//0xffc
	};

}


#endif /* MAPGPIO_HPP_ */
