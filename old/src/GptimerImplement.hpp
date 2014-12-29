/*
* Gptimer.cpp
*
*  Created on: 07/08/2013
*      Author: wilbert
*/

#pragma once

#include "../memorymap/MapGptimer.hpp"
#include "../include/Gptimer.hpp"
#include "../memorymap/mapClock.hpp"

namespace gpTimer{



	template<gpTimer::gpTimerModule Timer>
	void gpTimerMod<Timer>::enableClock()
	{
			switch (Timer) {
				case gpTimer::timer0_simple:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCTIMER |= (1<<0);
				break;
				case gpTimer::timer1_simple:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCTIMER |= (1<<1);
				break;
				case gpTimer::timer2_simple:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCTIMER |= (1<<2);
				break;
				case gpTimer::timer3_simple:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCTIMER |= (1<<3);
				break;
				case gpTimer::timer4_simple:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCTIMER |= (1<<4);
				break;
				case gpTimer::timer5_simple:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCTIMER |= (1<<5);
				break;
				case gpTimer::timer0_wide:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCWTIMER |= (1<<0);
				break;
				case gpTimer::timer1_wide:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCWTIMER |= (1<<1);
				break;
				case gpTimer::timer2_wide:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCWTIMER |= (1<<2);
				break;
				case gpTimer::timer3_wide:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCWTIMER |= (1<<3);
				break;
				case gpTimer::timer4_wide:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCWTIMER |= (1<<4);
				break;
				case gpTimer::timer5_wide:
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCWTIMER |= (1<<5);
				break;
			}
	}

	//start func 1--> enable subtimer
	template<gpTimer::gpTimerModule Timer>
	void gpTimer::gpTimerMod<Timer>::enableSubTimer(gpTimer::subTimers::subtimer subtimer_)
	{
        reinterpret_cast<MapGpTimer::GPTimerRegs *>
                (Timer)->GPTMCTL |=(1<<8*subtimer_);
	}
	//end func 1


//start func 2--> disable subtimer
	template<gpTimer::gpTimerModule Timer>
	void gpTimer::gpTimerMod<Timer>::disableSubTimer(gpTimer::subTimers::subtimer subtimer_)
	{
        reinterpret_cast<MapGpTimer::GPTimerRegs *>
                (Timer)->GPTMCTL &=0xffffffff - (1<<subtimer_*8);
	}
//end func 2

//start func 3--> config timer
	template<gpTimer::gpTimerModule Timer>
	unsigned int gpTimer::gpTimerMod<Timer>::config
			(gpTimer::subTimers::subtimer subtimer_,
			 unsigned long period_ms,
			 gpTimer::options::timerOptions::joiningMode::_joiningMode joiningMode_,
			 gpTimer::options::timerOptions::timerMode::tMode tMode,
			 gpTimer::options::timerOptions::countDirection::countDir cDir,
			 gpTimer::options::timerOptions::interrupts::interrupts_subtimer tInterrupt
			 )
	{
		unsigned int statusCode = 0;
		switch(subtimer_){

			case gpTimer::subTimers::subTimerA :

				//firstly, disable the sub-timer
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL &=0xffffffff - (1<<(0*8));
				//configure the joining mode, weather or not the sub-timers and joined
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCFG = joiningMode_;
				//configure the sub-timer A
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTAMR = (tMode) | (cDir<<4);
				//load the period in the period register
				if(joiningMode_ == gpTimer::options::timerOptions::joiningMode::timers_joinTimers)
				{
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMTAILR = period_ms*80000;
				}
				else if(joiningMode_ == gpTimer::options::timerOptions::joiningMode::timers_dontJoinTimers)
				{
					//only use this mode if the desired period is less than 209ms
					reinterpret_cast<MapGpTimer::GPTimerRegs *>(Timer)->GPTMTAPR = 0x000000ff;
					if(period_ms>208){
						reinterpret_cast<MapGpTimer::GPTimerRegs *>(Timer)->GPTMTAILR = 0x0000ffff;
						statusCode = 1;
					}
					else
					{
						reinterpret_cast<MapGpTimer::GPTimerRegs *>(Timer)->GPTMTAILR = 312.5*period_ms;
					}
				}
				//enable interrupts if needed
				reinterpret_cast<MapGpTimer::GPTimerRegs *>(Timer)->GPTMIMR = tInterrupt;
				//lastly, enable the sub-timer
				reinterpret_cast<MapGpTimer::GPTimerRegs *>(Timer)->GPTMCTL |=(1);

			break;

			case gpTimer::subTimers::subTimerB :

				//firstly, disable the sub-timer
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL &=0xffffffff - (1<<(1*8));
				//configure the joining mode, weather or not the sub-timers and joined
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCFG = joiningMode_;
				//configure the sub-timer B
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTBMR = (tMode) | (cDir<<4);
				//load the period in the period register
				if(joiningMode_ == gpTimer::options::timerOptions::joiningMode::timers_joinTimers)
				{
					//this sub-timer is not supposed to be working!!!
					statusCode = 2;
				}
				else if(joiningMode_ == gpTimer::options::timerOptions::joiningMode::timers_dontJoinTimers)
				{
					//only use this mode if the desired period is less than 209ms
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMTBPR = 0x000000ff;
					if(period_ms>208){
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTBILR = 0x0000ffff;
						statusCode = 1;
					}
					else
					{
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTBILR = 312.5*period_ms;
					}
				}
				//enable interrupts if needed
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMIMR = tInterrupt;
				//lastly, enable the sub-timer
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL |=(1<<8);

			break;
		}

		return statusCode;
	}
//end func 3

//start func 4
	template<gpTimer::gpTimerModule Timer>
	void gpTimer::gpTimerMod<Timer>::clearInterrupt(gpTimer::options::timerOptions::interrupts::interrupts_subtimer interrupt_)
	{
		reinterpret_cast<MapGpTimer::GPTimerRegs *>
			(Timer)->GPTMICR |= interrupt_ ;
	}

//end func 4


//start func 5

	template<gpTimer::gpTimerModule Timer,gpTimer::subTimers::subtimer subTimer>
	void gpTimer::pwm<Timer,subTimer>::config
		(unsigned int period_us,
		 float duty,
		 gpTimer::options::pwmOptions::outputLevel::_outputLevel outputLevel_
		 )
	{
		switch(subTimer)
		{
			case gpTimer::subTimers::subTimerA :

				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL &= 0xffffffff - (1);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCFG = 0x00000004;
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTAMR = (0x02)|(0<<2)|(1<<3);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL |= (outputLevel_<<6);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTAPR = 0x00000000;//250... so... it's more accurate
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTAILR = 80*period_us;//320*period_ms;
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTAPMR = 0x00000000;
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTAMATCHR = (u32)(duty*80*period_us);//(unsigned long)(duty*320*period_ms);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL |= 1;
			break;
			case gpTimer::subTimers::subTimerB :

				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL &= 0xffffffff - (1<<8);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCFG = 0x00000004;
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTBMR = (0x02)|(0<<2)|(1<<3);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL |= (outputLevel_<<14);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTBPR = 0x000000fa;//250... so... it's more accurate
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTBILR = 80*period_us;
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTBPMR = 0x000000fa;
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMTBMATCHR = (u32)(duty*80*period_us);
				reinterpret_cast<MapGpTimer::GPTimerRegs *>
					(Timer)->GPTMCTL |= 1<<8;
			break;
		}
	}
//end func 5

	template<gpTimer::gpTimerModule Timer,gpTimer::subTimers::subtimer subTimer>
	void gpTimer::pwm<Timer,subTimer>::enableClock()
	{
		switch (Timer) {
			case gpTimer::timer0_simple:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCTIMER |= (1<<0);
			break;
			case gpTimer::timer1_simple:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCTIMER |= (1<<1);
			break;
			case gpTimer::timer2_simple:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCTIMER |= (1<<2);
			break;
			case gpTimer::timer3_simple:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCTIMER |= (1<<3);
			break;
			case gpTimer::timer4_simple:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCTIMER |= (1<<4);
			break;
			case gpTimer::timer5_simple:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCTIMER |= (1<<5);
			break;
			case gpTimer::timer0_wide:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCWTIMER |= (1<<0);
			break;
			case gpTimer::timer1_wide:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCWTIMER |= (1<<1);
			break;
			case gpTimer::timer2_wide:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCWTIMER |= (1<<2);
			break;
			case gpTimer::timer3_wide:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCWTIMER |= (1<<3);
			break;
			case gpTimer::timer4_wide:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCWTIMER |= (1<<4);
			break;
			case gpTimer::timer5_wide:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCWTIMER |= (1<<5);
			break;
		}
	}

	template<gpTimer::gpTimerModule Timer,gpTimer::subTimers::subtimer subTimer>
	void gpTimer::pwm<Timer,subTimer>::setDuty(float duty)
	{
		u32 periodReg = 0;
		switch (subTimer) {
			case gpTimer::subTimers::subTimerA:
					periodReg = reinterpret_cast<MapGpTimer::GPTimerRegs *>(Timer)->GPTMTAILR;
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMTAMATCHR = (u32)(duty*periodReg);//(unsigned long)(duty*320*period_ms);
				break;
			case gpTimer::subTimers::subTimerB:
					periodReg = reinterpret_cast<MapGpTimer::GPTimerRegs *>(Timer)->GPTMTBILR;
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMTBMATCHR = (u32)(duty*periodReg);//(unsigned long)(duty*320*period_ms);
				break;
		}
	}

}
