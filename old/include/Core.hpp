/*
 * Core.h
 *
 *  Created on: 05/08/2013
 *      Author: wilbert
 */

#pragma once

#include "../memorymap/MapCore.hpp"

namespace core
{

	namespace interrupts
	{
		enum _interrupt
		{
			nmi 		  			= 2,
			hard_fault 	  			= 3,
			fault_memory  			= 4,
			fault_bus	  			= 5,
			fault_usage   			= 6,
			fault_svcall  			= 11,
			fault_debug   			= 12,
			fault_pendsv  			= 14,
			fault_systick 			= 15,

			gpio_portA	  			= 16,
			gpio_portB	  			= 17,
			gpio_portC	  			= 18,
			gpio_portD	  			= 19,
			gpio_portE    			= 20,
			uart0		  			= 21,
			uart1		  			= 22,
			ssi0		  			= 23,
			i2c0		  			= 24,
			adc0_seq0	  			= 30,
			adc0_seq1	  			= 31,
			adc0_seq2	  			= 32,
			adc0_seq3	  			= 33,
			watchDogTimers_0_1  	= 34,
			timer0a_simple			= 35,
			timer0b_simple			= 36,
			timer1a_simple			= 37,
			timer1b_simple			= 38,
			timer2a_simple			= 39,
			timer2b_simple			= 40,
			analogComparator0		= 41,
			analogComparator1		= 42,
			systemControl			= 44,
			flash_eeprom_control	= 45,
			gpio_portF				= 46,
			uart2					= 49,
			ssi1					= 50,
			timer3a_simple			= 51,
			timer3b_simple			= 52,
			i2c1					= 53,
			can0					= 55,
			hibernation_module		= 59,
			usb						= 60,
			uDMA_soft				= 62,
			uDMA_error				= 63,
			adc1_seq0				= 64,
			adc1_seq1				= 65,
			adc1_seq2				= 66,
			adc1_seq3				= 67,
			ssi2					= 73,
			ssi3					= 74,
			uart3					= 75,
			uart4					= 76,
			uart5					= 77,
			uart6					= 78,
			uart7					= 79,
			i2c2					= 84,
			i2c3					= 85,
			timer4a_simple			= 86,
			timer4b_simple			= 87,
			timer5a_simple			= 108,
			timer5b_simple			= 109,
			timer0a_wide			= 110,
			timer0b_wide			= 111,
			timer1a_wide			= 112,
			timer1b_wide			= 113,
			timer2a_wide			= 114,
			timer2b_wide			= 115,
			timer3a_wide			= 116,
			timer3b_wide			= 117,
			timer4a_wide			= 118,
			timer4b_wide			= 119,
			timer5a_wide			= 120,
			timer5b_wide			= 121,
			system_exception		= 122
		};
	}
	unsigned char IntEnableMaster();
	void enableInterrupt(core::interrupts::_interrupt interrupt_);
}

#include "../src/CoreImplement.hpp"
