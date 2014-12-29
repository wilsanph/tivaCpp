/*
 * ClockImplement.hpp
 *
 *  Created on: Sep 10, 2013
 *      Author: wilbert
 */

#pragma once

#include "../memorymap/mapClock.hpp"
#include "../include/clock.hpp"

namespace clock
{
	void clock::config(configOptions::clockSource::sources clockSource,
									 configOptions::clockRate::_clockRate clockRate_,
									 configOptions::enablePIOSC::_enablePIOSC enablePIOSC_ = configOptions::enablePIOSC::enablePinternalOsc,
									 configOptions::enableMOSC::_enableMOSC enableMOSC_ = configOptions::enableMOSC::enableMainOsc)
	{

		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCC2 |= (u32)(1<<31);

		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCC |= (u32)(1<<11);
		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCC &= (u32)(0xffffffff - (1<<22));
		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCC = (u32)((1<<11)|(0x15<<6)|(clockSource<<4)|(0x09<<23)|(1<<22)|(enablePIOSC_<<1)|(enableMOSC_<<0));
		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCC2 = (u32)((1<<11)|(1<<31)|(1<<30)|(clockRate_<<22)|(clockSource<<4));
		while((reinterpret_cast<mapClock::ClockRegs *>
			  (mapClock::moduleAddresses::clockAddress)
			  ->RIS) & (0x40) != (0x40)
			 );
		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCC &= (u32)(0xffffffff - (1<<11));
		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCC2 &= (u32)(0xffffffff - (1<<11));
	}

}
