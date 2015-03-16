/*
 * TimerImplement.hpp
 *
 *  Created on: 29/12/2014
 *      Author: USER01
 */

#ifndef TIMERIMPLEMENT_HPP_
#define TIMERIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapTimer.hpp"
#include "../include/Timer.hpp"

#include "../include/Clock.hpp"

namespace GpTimer
{
	
	GpTimer::Timer::Timer()
	{
		this->objID = gObject::ObjectIDs::OBJ_ID_TIMER;
		this->m_timerMod = GpTimer::timerModule::TIMER0_SIMPLE;
		this->m_subTimer = GpTimer::subtimer::SUBTIMER_A;
	}

	GpTimer::Timer::Timer( GpTimer::timerModule::_timerModule tTimerMod,
			   			   GpTimer::subtimer::_subtimer tSubtimer )
	{
		this->objID = gObject::ObjectIDs::OBJ_ID_TIMER;
		this->m_timerMod = tTimerMod;
		this->m_subTimer = tSubtimer;
	}

	void GpTimer::Timer::init()
	{
		// TODO: Add extra code here
	}

	GpTimer::config::timerConfig::statusCode::_statusCode GpTimer::Timer::config( u32 period_us,
												 			  			  float tick_resolution_us,
												 			  			  GpTimer::config::timerConfig::joiningMode::_joiningMode tJoiningMode,
												 			  			  GpTimer::config::timerConfig::countDirection::_countDirection tCountDirection,
												 			  			  GpTimer::config::timerConfig::timerMode::_timerMode tTimerMode,
												 			  			  GpTimer::config::timerConfig::timerInterrupts::_timerInterrupts tInterrupt )
	{
		volatile GpTimer::config::timerConfig::statusCode::_statusCode stCode = GpTimer::config::timerConfig::statusCode::NONE;

		// Disable the corresponding subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCTL &= 0xffffffff - ( 1 << ( this->m_subTimer * 8 ) );

		// Configure the joining mode, weather or not the subtimers are joint
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCFG = tJoiningMode;

		// Configure the corresponding subtimer ( see that x4 inside the cast?-> it's ...
		// ...just an offset depending of the subtimer )
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAMR = tTimerMode | tCountDirection;

		// Calculate the prescaler and the number of timer ticks according to the desired tick resolution
		volatile u32 preescaler = ( u32 )( clock::Clock::CLOCK_RATE_MHZ * tick_resolution_us );
		volatile u32 numTimerTicks = ( u32 )( clock::Clock::CLOCK_RATE_MHZ * period_us / preescaler );

		// Load the calculated prescaler value in the prescaler register
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAPR = preescaler;

		// Load the calculated number of ticks in the periodLoadRegister
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAILR = numTimerTicks;

		// Enable interrupts if needed
		if ( this->m_subTimer == GpTimer::subtimer::SUBTIMER_A )
		{
			// Clear previous configuration for subtimer A
			reinterpret_cast<MapTimer::GPTimerRegs*>
				( this->m_timerMod )->GPTMIMR &= 0xffffffe0;
			if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::timeout )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( this->m_timerMod )->GPTMIMR |= 0x0001;
			}
			else if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::match )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( this->m_timerMod )->GPTMIMR |= 0x0010;
			}
		}
		else {
			// Clear previous configuration for subtimer B
			reinterpret_cast<MapTimer::GPTimerRegs*>
				( this->m_timerMod )->GPTMIMR &= 0xfffff0ff;
			if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::timeout )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( this->m_timerMod )->GPTMIMR |= 0x0100;
			}
			else if ( tInterrupt == GpTimer::config::timerConfig::timerInterrupts::match )
			{
				reinterpret_cast<MapTimer::GPTimerRegs*>
					( this->m_timerMod )->GPTMIMR |= 0x0800;
			}
		}

		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCTL |= ( 1 << 8 * this->m_subTimer );

		#ifdef DEBUG
		// Check if the current configuration is posible, if not, set a status code.
		if ( this->m_timerMod < GpTimer::timerModule::TIMER0_WIDE &&
			 numTimerTicks > 0x0000ffff &&
			 tJoiningMode == GpTimer::config::timerConfig::joiningMode::disjoint )
		{			
			// For this configuration... you would get a max. period of 209 ms
			stCode = GpTimer::config::timerConfig::statusCode::MAX_PERIOD_REACHED;
		}
		if ( tJoiningMode == GpTimer::config::timerConfig::joiningMode::joint &&
			 this->m_subTimer == GpTimer::subtimer::SUBTIMER_B )
		{	
			// For this configuration... the subtimerB should be in use
			stCode = GpTimer::config::timerConfig::statusCode::CONFIG_WRONG_SUBTIMER;
		}
		#endif
		
		return stCode;
	}

	void GpTimer::Timer::enableTimer()
	{
		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCTL |= ( 1 << 8 * this->m_subTimer );
	}

	void GpTimer::Timer::disableTimer()
	{
		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCTL &= 0xffffffff - ( 1 << 8 * this->m_subTimer );
	}

	void GpTimer::Timer::clearInterrupt( GpTimer::config::timerConfig::interruptFlag::_interruptFlag tInterruptFlag )
	{
		// Clear the given flag
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMICR |= tInterruptFlag;
	}
	
	/**
	 * PWM library implementation
	 *
	 */

	GpTimer::Pwm::Pwm()
		: GpTimer::Timer()
	{
		GpTimer::Timer();
		this->objID = gObject::ObjectIDs::OBJ_ID_PWM;
		this->m_period_us = 50;// 20 Khz
		this->m_duty = 0.2;
	}

	GpTimer::Pwm::Pwm( GpTimer::timerModule::_timerModule tTimerMod,
			   		   GpTimer::subtimer::_subtimer tSubtimer )
		: GpTimer::Timer( tTimerMod, tSubtimer )
	{
		GpTimer::Timer( tTimerMod, tSubtimer );
		this->objID = gObject::ObjectIDs::OBJ_ID_PWM;
		this->m_period_us = 50;// 20 Khz
		this->m_duty = 0.2;
	}

	void GpTimer::Pwm::init()
	{
		// TODO: Add extra code here
	}

	void GpTimer::Pwm::configPWM( u32 period_us,
		 					   	  float duty,
		 					   	  GpTimer::config::pwmConfig::outputLevel::_outputLevel pwmOutputLevel )
	{
		this->m_period_us = period_us;
		this->m_duty = duty;

		// Disable the corresponding subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCTL &= 0xffffffff - ( 1 << ( this->m_subTimer * 8 ) );

		// Configure the joining mode to disjoint
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCFG = GpTimer::config::timerConfig::joiningMode::disjoint;

		// Configure the corresponding subtimer ( see that x4 inside the cast?-> it's ...
		// ...just an offset depending of the subtimer )
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAMR = GpTimer::config::timerConfig::timerMode::periodic |
																	GpTimer::config::timerConfig::countDirection::down |
																	GpTimer::config::timerConfig::timerAlternateModeSelect::pwmEnabled;

		// The tick resolution in us is the tick resolution of the clock itself in pwm mode ...
		// ... because there is no preescaler :D, just a extended timer
		volatile u64 totalTimer = clock::Clock::CLOCK_RATE_MHZ * period_us;
		volatile u64 dutyTimer = ( u64 )( clock::Clock::CLOCK_RATE_MHZ * period_us * duty );
		volatile u32 preescaler = 0;
		volatile u32 intervalLoad = 0;
		volatile u32 dutyPreescaler = 0;
		volatile u32 dutyIntervalLoad = 0;
		if ( this->m_timerMod < GpTimer::timerModule::TIMER0_WIDE )
		{
			// If working with a 16 bit simple timer
			intervalLoad = totalTimer & 0x000000000000ffff;
			preescaler = ( totalTimer & 0x0000000000ff0000 ) >> 16;

			dutyIntervalLoad = dutyTimer & 0x000000000000ffff;
			dutyPreescaler = ( dutyTimer & 0x0000000000ff0000 ) >> 16;

		}
		else {
			// If working with a 32 bit wide timer
			intervalLoad = totalTimer & 0x00000000ffffffff;
			preescaler = ( totalTimer & 0x0000ffff00000000 ) >> 32;

			dutyIntervalLoad = dutyTimer & 0x00000000ffffffff;
			dutyPreescaler = ( dutyTimer & 0x0000ffff00000000 ) >> 32;
		}


		// Load the calculated prescaler value in the prescaler register
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAPR = preescaler;

		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAPMR = dutyPreescaler;

		// Load the calculated number of ticks in the periodLoadRegister
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAILR = intervalLoad;

		// Load the value of the period * duty in the match register
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAMATCHR = dutyIntervalLoad;

		// Set the output mode
		reinterpret_cast<MapTimer::GPTimerRegs *>
			( this->m_timerMod )->GPTMCTL |= pwmOutputLevel;

		// Enable the subtimer
		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod )->GPTMCTL |= ( 1 << 8 * this->m_subTimer );
	}


	void GpTimer::Pwm::setDuty( float duty )
	{
		this->m_duty = duty;
		duty = ( duty > 0.99 ) ? 0.99 : duty;
		duty = ( duty < 0.01 ) ? 0.01 : duty;
		volatile u64 dutyTimer = ( u64 )( clock::Clock::CLOCK_RATE_MHZ * this->m_period_us * duty );
		volatile u32 dutyPreescaler = 0;
		volatile u32 dutyIntervalLoad = 0;
		if ( this->m_timerMod < GpTimer::timerModule::TIMER0_WIDE )
		{
			dutyIntervalLoad = dutyTimer & 0x000000000000ffff;
			dutyPreescaler = ( dutyTimer & 0x0000000000ff0000 ) >> 16;
		}
		else {
			dutyIntervalLoad = dutyTimer & 0x00000000ffffffff;
			dutyPreescaler = ( dutyTimer & 0x0000ffff00000000 ) >> 32;
		}

		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAPMR = dutyPreescaler;

		reinterpret_cast<MapTimer::GPTimerRegs*>
			( this->m_timerMod + 4 * this->m_subTimer )->GPTMTAMATCHR = dutyIntervalLoad;
	}

}



#endif /* TIMERIMPLEMENT_HPP_ */
