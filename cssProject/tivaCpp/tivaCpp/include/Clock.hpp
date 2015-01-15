/*
 * Clock.hpp
 *
 *  Created on: 30/12/2014
 *      Author: Wilbert
 */

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#pragma once

#include "../common.hpp"

namespace clock
{

	namespace moduleAddresses
	{
		enum _moduleAddresses
		{
			clockAddress = 0x400FE000
		};
	}
	
	namespace config
	{
		namespace clockRate
		{
			enum _clockRate
			{
				clock_40Mhz = 0x09,
				clock_50Mhz = 0x07,
				clock_80Mhz = 0x04
			};
		}

		namespace clockSource
		{
			enum _clockSource
			{
				mainOscilator = 0x0,
				precisionInternalOscillator = 0x1,
				precisionInternalOscillator_Div4 = 0x2,
				internal_30khz = 0x3,
				external_32_768khz = 0x7
			};
		}

		namespace precisionInternalOscillator
		{
			enum _precisionInternalOscillator
			{
				enablePinternalOsc	= 0,
				disablePinternalOsc	= 1
			};
		}
		namespace mainOscillator
		{
			enum _mainOscillator
			{
				enableMainOsc	= 0,
				disableMainOsc	= 1
			};
		}

		namespace gpioBusType
		{
			enum _gpioBusType
			{
				APBbus = 0,
				AHBbus = 1
			};
		}
	}

	namespace peripheral
	{
		namespace gpio
		{			
			enum _gpio
			{
				GPIOA = 0,
				GPIOB = 1,
				GPIOC = 2,
				GPIOD = 3,
				GPIOE = 4,
				GPIOF = 5
			};
		}

		namespace timer
		{
			namespace simpleTimer
			{
				enum _simpleTimer
				{
					TIMER0 = 0,
					TIMER1 = 1,
					TIMER2 = 2,
					TIMER3 = 3,
					TIMER4 = 4,
					TIMER5 = 5,
				};	
			}

			namespace wideTimer
			{
				enum _wideTimer 
				{  
					WTIMER0 = 0,
					WTIMER1 = 1,
					WTIMER2 = 2,
					WTIMER3 = 3,
					WTIMER4 = 4,
					WTIMER5 = 5
				};
			}
		}

		namespace uart
		{
			enum _uart
			{
				UART0 = 0,
				UART1 = 1,
				UART2 = 2,
				UART3 = 3,
				UART4 = 4,
				UART5 = 5,
				UART6 = 6,
				UART7 = 7
			};
		}

		namespace adc
		{
			enum _adc
			{
				ADC0 = 0,
				ADC1 = 1
			};
		}				
	}

	class Clock
	{
	public:
		Clock();		
		
		static u32 CLOCK_RATE_MHZ;

		void config( config::clockSource::_clockSource cSource,
					 config::clockRate::_clockRate cRate,
					 config::precisionInternalOscillator::_precisionInternalOscillator cPInternalOsc  = config::precisionInternalOscillator::enablePinternalOsc,
					 config::mainOscillator::_mainOscillator cMainOscillator = config::mainOscillator::enableMainOsc );

		void enableGpioClock( peripheral::gpio::_gpio cGpio, config::gpioBusType::_gpioBusType busType );
		void enableSimpleTimerClock( peripheral::timer::simpleTimer::_simpleTimer cSimpleTimer );
		void enableWideTimerClock( peripheral::timer::wideTimer::_wideTimer cWideTimer );
		void enableUartClock( peripheral::uart::_uart cUart );
		void enableADCClock( peripheral::adc::_adc cAdc );

		//void enableI2CClock();
		//void enableSPIClock();


		// TODO : Implement these methods

		// void hibernate();
		// void wakeup();

	private:
		moduleAddresses::_moduleAddresses m_clockAddress;
	};


}

#include "../src/ClockImplement.hpp"

#endif /* CLOCK_HPP_ */
