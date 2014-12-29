/*
 * SPIimplement.hpp
 *
 *  Created on: Sep 10, 2013
 *      Author: wilbert
 */

#pragma once

#include "../memorymap/mapSPI.hpp"
#include "../memorymap/mapClock.hpp"
#include "../include/SPI.hpp"

namespace spi
{
	template<module::_module spiMod>
	void spi<spiMod>::enableClock()
	{
		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCGCSSI |= (1<<((spiMod-0x40008000)>>12));
	}

	template<module::_module spiMod>
	void spi<spiMod>::config(configOptions::mode::_mode mode_,
				     configOptions::clockRate::_clockRate clockRate_,
				     configOptions::clockPolarity::_clockPolarity clockPolarity_,
				     configOptions::clockPhase::_clockPhase clockPhase_,
				     configOptions::frameFormat::_frameFormat frameFormat_,
				     configOptions::dataSize::_dataSize dataSize_)
	{
		reinterpret_cast<mapSPI::SPIregs *>
		(spiMod)->SSICR1 &= 0xffffffff - (1<<1);
		reinterpret_cast<mapSPI::SPIregs *>
		(spiMod)->SSICR1 = 0x00000000 | (mode_<<2);
		reinterpret_cast<mapSPI::SPIregs *>
		(spiMod)->SSICC = 0x5;
		reinterpret_cast<mapSPI::SPIregs *>
		(spiMod)->SSICPSR = clockRate_;
		reinterpret_cast<mapSPI::SPIregs *>
		(spiMod)->SSICR0 = (0x00<<8) |
					   (clockPhase_<<7) |
					   (clockPolarity_<<6) |
					   (frameFormat_<<4) |
					   (dataSize_);
		reinterpret_cast<mapSPI::SPIregs *>
		(spiMod)->SSICR1 |= (1<<1);
	}

	template<module::_module spiMod>
	void spi<spiMod>::sendByte(unsigned char data)
	{
		while(!((reinterpret_cast<mapSPI::SPIregs *>
				(spiMod)->SSISR)&0x2 == 0x2));
		reinterpret_cast<mapSPI::SPIregs *>
			(spiMod)->SSIDR = (u32)(data);
	}

	template<module::_module spiMod>
	unsigned char spi<spiMod>::readByte()
	{
		while(!((reinterpret_cast<mapSPI::SPIregs *>
							(spiMod)->SSISR)&0x4 == 0x4));
		return reinterpret_cast<mapSPI::SPIregs *>
				(spiMod)->SSIDR;
	}

}

