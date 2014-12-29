/*
 * SPI.h
 *
 *  Created on: Aug 21, 2013
 *      Author: wilbert
 */
#pragma once

#include "../memorymap/mapSPI.hpp"

namespace spi
{

	namespace module
	{
		enum _module
		{
			spi0 = 0x40008000,
			spi1 = 0x40009000,
			spi2 = 0x4000a000,
			spi3 = 0x4000b000
		};
	}
	namespace configOptions
	{
		namespace mode
		{
			enum _mode
			{
				master 				= 0,
				slave_txNotDriven	= 3,
				slave_txDriven		= 1
			};
		}

		namespace clockRate
		{
			enum _clockRate
			{
				spiclock_100khz = 160,
				spiclock_200khz = 80,
				spiclock_400khz = 40,
				spiclock_500khz = 32,
				spiclock_800khz = 20,
				spiclock_1Mhz = 16,
				spiclock_2Mhz = 8,
				spiclock_4Mhz = 4
			};
		}
		namespace clockPolarity
		{
			enum _clockPolarity
			{
				high 	= 1,
				low		= 0
			};
		}
		namespace clockPhase
		{
			enum _clockPhase
			{
				capFirstClock 	= 0,
				capSecondClock	= 1
			};
		}
		namespace frameFormat
		{
			enum _frameFormat
			{
				freescale 			= 0,
				texasInstruments	= 1,
				microwire			= 2,
				reserved			= 3
			};
		}
		namespace dataSize
		{
			enum _dataSize
			{
				bits_4	= 0x3,
				bits_5	= 0x4,
				bits_6	= 0x5,
				bits_7	= 0x6,
				bits_8	= 0x7,
				bits_9	= 0x8,
				bits_10	= 0x9,
				bits_11	= 0xa,
				bits_12	= 0xb,
				bits_13	= 0xc,
				bits_14	= 0xd,
				bits_15	= 0xe,
				bits_16	= 0xf
			};
		}
	}


	template<module::_module spiMod>
	class spi
	{
	public:
		static inline void enableClock();
		static inline void config(configOptions::mode::_mode mode_,
								  configOptions::clockRate::_clockRate clockRate_,
								  configOptions::clockPolarity::_clockPolarity clockPolarity_,
								  configOptions::clockPhase::_clockPhase clockPhase_,
								  configOptions::frameFormat::_frameFormat frameFormat_,
								  configOptions::dataSize::_dataSize dataSize_);
		static inline void sendByte(unsigned char data);
		static inline unsigned char readByte();
	};


}

#include "../src/SPIimplement.hpp"
