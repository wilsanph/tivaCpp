/*
 * Gpio.hpp
 *
 *  Created on: 27/12/2014
 *      Author: USER01
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#pragma once


namespace Gpio
{
	
	namespace port
	{
		enum _port 
		{  
			GPIOPortA_APB= 0x40004000,
			GPIOPortA_AHB= 0x40058000,
			GPIOPortB_APB= 0x40005000,
			GPIOPortB_AHB= 0x40059000,
			GPIOPortC_APB= 0x40006000,
			GPIOPortC_AHB= 0x4005A000,
			GPIOPortD_APB= 0x40007000,
			GPIOPortD_AHB= 0x4005B000,
			GPIOPortE_APB= 0x40024000,
			GPIOPortE_AHB= 0x4005C000,
			GPIOPortF_APB= 0x40025000,
			GPIOPortF_AHB= 0x4005D000			
		};
	}

	namespace pin
	{
		enum _pin 
		{  
			pin0 = 0,
			pin1 = 1,
			pin2 = 2,
			pin3 = 3,
			pin4 = 4,
			pin5 = 5,
			pin6 = 6,
			pin7 = 7			
		};
	}

	namespace peripheral
	{
		enum _peripheral 
		{  
			GPIOA = 0,
			GPIOB = 1,
			GPIOC = 2,
			GPIOD = 3,
			GPIOE = 4,
			GPIOF = 5			
		};
	}

	namespace config
	{
		namespace mode
		{
			enum _mode 
			{  
				gpio = 0,
				alternate = 1				
			};
		}

		namespace ioMode
		{
			enum _ioMode 
			{  
				input = 0,
				output = 1
			};
		}

		namespace altModes
		{
			enum _altModes
			{
				alt1  = 1,
				alt2  = 2,
				alt3  = 3,
				alt4  = 4,
				alt5  = 5,
				alt6  = 6,
				alt7  = 7,
				alt8  = 8,
				alt9  = 9,
				alt10 = 10,
				alt11 = 11,
				alt12 = 12,
				alt13 = 13,
				alt14 = 14,
				alt15 = 15
			};
		}

		namespace currentDrive 
		{
			enum _currentDrive 
			{
				mA_2 = 0,
				mA_4 = 1,
				mA_8 = 2
			};
		}		

		namespace interrupts
		{
			namespace intSenseType
			{
				enum _intSenseType
				{
					edge = 0,
					level = 1
				};
			}
			namespace intEventType
			{
				enum _intEventType
				{
					down = 0,
					up = 1
				};
			}			

			namespace intSenseBothEdges
			{
				enum _intSenseBothEdges 
				{
					dontSenseBothEdges = 0,
					senseBothEdges = 1
				};
			}
		}
	}

	namespace state
	{
		enum _state
		{
			low = 0,
			high = 1
		};
	}

	template<port::_port pPort>
	class Port
	{

	public:

		inline static void enableClock( peripheral::_peripheral pPeripheral );
		inline static void unlock();

	};

	class Pin
	{
	public:
		Pin();
		Pin( port::_port pPort, pin::_pin pPin );
		
		void enableDigitalFunc();
		void disableDigitalFunc();

		void setMode( config::mode::_mode pinMode );
		void setIOMode( config::ioMode::_ioMode pinIOMode );		
		void setLow();
		void setHigh();
		void setValue( state::_state pinState );
		void toggle();
		bool isHigh();
		bool isLow();

		void enableInterrupt();
		void disableInterrupt();
		void configInterrupt( config::interrupts::intSenseType::_intSenseType pinSenseType,
							  config::interrupts::intSenseBothEdges::_intSenseBothEdges pinSenseBothEdges,
							  config::interrupts::intEventType::_intEventType pinEventType );
		void clearFlag();

		void setAnalogMode();
		void setAlternateMode( config::altModes::_altModes pAltMode );
		void setCurrentDrive( config::currentDrive::_currentDrive pCurrentDrive );
		void setPullUp();
		void setPullDown();
		void setOpenDrain();



	protected:

	private:
		port::_port m_port;
		pin::_pin m_pin;
		
	};


}

typedef Gpio::Port<Gpio::port::GPIOPortF_APB> PORTF;

#include "../src/GpioImplement.hpp"

#endif /* GPIO_HPP_ */
