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


	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	class tPin
	{

	public:

		inline static void enableDigitalFunc();
		inline static void disableDigitalFunc();

		inline static void setMode( config::mode::_mode pinMode );
		inline static void setIOMode( config::ioMode::_ioMode pinIOMode );		
		inline static void setLow();
		inline static void setHigh();
		inline static void setValue( state::_state pinState );
		inline static void toggle();
		inline static bool isHigh();
		inline static bool isLow();

		inline static void enableInterrupt();
		inline static void disableInterrupt();
		inline static void configInterrupt( config::interrupts::intSenseType::_intSenseType pinSenseType,
							  				config::interrupts::intSenseBothEdges::_intSenseBothEdges pinSenseBothEdges,
							  				config::interrupts::intEventType::_intEventType pinEventType );
		inline static void clearFlag();

		inline static void setAnalogMode();
		inline static void setAlternateMode( config::altModes::_altModes pAltMode );
		inline static void setCurrentDrive( config::currentDrive::_currentDrive pCurrentDrive );
		inline static void setPullUp();
		inline static void setPullDown();
		inline static void setOpenDrain();

	};

}

typedef Gpio::Port<Gpio::port::GPIOPortA_APB> PORTA_APB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin0> PA0;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin1> PA1;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin2> PA2;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin3> PA3;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin4> PA4;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin5> PA5;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin6> PA6;
typedef Gpio::tPin<Gpio::port::GPIOPortA_APB,Gpio::pin::pin7> PA7;

typedef Gpio::Port<Gpio::port::GPIOPortA_AHB> PORTA_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin0> PA0_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin1> PA1_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin2> PA2_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin3> PA3_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin4> PA4_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin5> PA5_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin6> PA6_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortA_AHB,Gpio::pin::pin7> PA7_AHB;

typedef Gpio::Port<Gpio::port::GPIOPortB_APB> PORTB_APB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin0> PB0;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin1> PB1;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin2> PB2;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin3> PB3;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin4> PB4;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin5> PB5;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin6> PB6;
typedef Gpio::tPin<Gpio::port::GPIOPortB_APB,Gpio::pin::pin7> PB7;

typedef Gpio::Port<Gpio::port::GPIOPortB_AHB> PORTB_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin0> PB0_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin1> PB1_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin2> PB2_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin3> PB3_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin4> PB4_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin5> PB5_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin6> PB6_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortB_AHB,Gpio::pin::pin7> PB7_AHB;

typedef Gpio::Port<Gpio::port::GPIOPortC_APB> PORTC_APB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin0> PC0;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin1> PC1;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin2> PC2;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin3> PC3;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin4> PC4;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin5> PC5;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin6> PC6;
typedef Gpio::tPin<Gpio::port::GPIOPortC_APB,Gpio::pin::pin7> PC7;

typedef Gpio::Port<Gpio::port::GPIOPortC_AHB> PORTC_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin0> PC0_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin1> PC1_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin2> PC2_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin3> PC3_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin4> PC4_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin5> PC5_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin6> PC6_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortC_AHB,Gpio::pin::pin7> PC7_AHB;

typedef Gpio::Port<Gpio::port::GPIOPortD_APB> PORTD_APB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin0> PD0;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin1> PD1;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin2> PD2;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin3> PD3;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin4> PD4;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin5> PD5;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin6> PD6;
typedef Gpio::tPin<Gpio::port::GPIOPortD_APB,Gpio::pin::pin7> PD7;

typedef Gpio::Port<Gpio::port::GPIOPortD_AHB> PORTD_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin0> PD0_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin1> PD1_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin2> PD2_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin3> PD3_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin4> PD4_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin5> PD5_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin6> PD6_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortD_AHB,Gpio::pin::pin7> PD7_AHB;

typedef Gpio::Port<Gpio::port::GPIOPortE_APB> PORTE_APB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin0> PE0;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin1> PE1;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin2> PE2;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin3> PE3;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin4> PE4;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin5> PE5;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin6> PE6;
typedef Gpio::tPin<Gpio::port::GPIOPortE_APB,Gpio::pin::pin7> PE7;

typedef Gpio::Port<Gpio::port::GPIOPortE_AHB> PORTE_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin0> PE0_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin1> PE1_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin2> PE2_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin3> PE3_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin4> PE4_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin5> PE5_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin6> PE6_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortE_AHB,Gpio::pin::pin7> PE7_AHB;

typedef Gpio::Port<Gpio::port::GPIOPortF_APB> PORTF_APB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin0> PF0;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin1> PF1;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin2> PF2;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin3> PF3;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin4> PF4;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin5> PF5;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin6> PF6;
typedef Gpio::tPin<Gpio::port::GPIOPortF_APB,Gpio::pin::pin7> PF7;

typedef Gpio::Port<Gpio::port::GPIOPortF_AHB> PORTF_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin0> PF0_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin1> PF1_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin2> PF2_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin3> PF3_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin4> PF4_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin5> PF5_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin6> PF6_AHB;
typedef Gpio::tPin<Gpio::port::GPIOPortF_AHB,Gpio::pin::pin7> PF7_AHB;

#include "../src/GpioImplement.hpp"
#include "../src/TGpioImplement.hpp"

#endif /* GPIO_HPP_ */
