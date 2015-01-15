/*
 * ClockImplement.hpp
 *
 *  Created on: 30/12/2014
 *      Author: Wilbert
 */

#ifndef CLOCKIMPLEMENT_HPP_
#define CLOCKIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapClock.hpp"
#include "../include/Clock.hpp"

namespace clock
{

	u32 clock::Clock::CLOCK_RATE_MHZ = 80;

	clock::Clock::Clock()
	{
		this->m_clockAddress = clock::moduleAddresses::clockAddress;
	}
	
	void clock::Clock::config( clock::config::clockSource::_clockSource cSource,
					 		   clock::config::clockRate::_clockRate cRate,
					 		   clock::config::precisionInternalOscillator::_precisionInternalOscillator cPInternalOsc,
					 		   clock::config::mainOscillator::_mainOscillator cMainOscillator )
	{
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCC2 |= (u32)( 1 << 31 );

		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCC |= 1 << 11;
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCC &= 0xffffffff - ( 1 << 22 );
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )
			->RCC = ( 1 << 11 ) | ( 0x15 << 6 ) |
					( cSource << 4 ) | ( 0x09 << 23 ) | 
					( 1 << 22 ) | ( cPInternalOsc << 1 ) | ( cMainOscillator << 0 );
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )
			->RCC2 = ( 1 << 11 ) | ( 1 << 31 ) | 
					 ( 1 << 30 ) | ( cRate << 22 ) |
					 ( cSource << 4 );
		while( (reinterpret_cast<MapClock::ClockRegs*>
					( this->m_clockAddress )->RIS ) & 0x40 != 0x40
			 );
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCC &= 0xffffffff - ( 1 << 11 );
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCC2 &= 0xffffffff - ( 1 << 11 );
	}

	void clock::Clock::enableGpioClock( clock::peripheral::gpio::_gpio cGpio, clock::config::gpioBusType::_gpioBusType busType )
	{
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCGCGPIO |= 1 << cGpio;
		if ( busType == clock::config::gpioBusType::AHBbus )
		{
			reinterpret_cast<MapClock::ClockRegs*>
				( this->m_clockAddress )->GPIOHBCTL |= 1 << cGpio;
		}
	}

	void clock::Clock::enableSimpleTimerClock( clock::peripheral::timer::simpleTimer::_simpleTimer cSimpleTimer )
	{
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCGCTIMER |= 1 << cSimpleTimer;
	}

	void clock::Clock::enableWideTimerClock( clock::peripheral::timer::wideTimer::_wideTimer cWideTimer )
	{
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCGCWTIMER |= 1 << cWideTimer;
	}

	void clock::Clock::enableUartClock( clock::peripheral::uart::_uart cUart )
	{
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCGCUART |= 1 << cUart;		
	}

	void clock::Clock::enableADCClock( clock::peripheral::adc::_adc cAdc )
	{
		reinterpret_cast<MapClock::ClockRegs*>
			( this->m_clockAddress )->RCGCADC |= 1 << cAdc;		
	}

}



#endif /* CLOCKIMPLEMENT_HPP_ */
