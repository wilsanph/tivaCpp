/*
 * UartImplement.hpp
 *
 *  Created on: Aug 24, 2013
 *      Author: wilbert
 */

#pragma once

#include "../memorymap/MapUart.h"
#include "../include/Uart.h"
#include "../memorymap/mapClock.hpp"
#include "string"


namespace uart
{

	void utils::calcBrd(unsigned int uartClock,
						unsigned int baudRate,
						unsigned int& brdInt,
						unsigned int& brdFrc)

	{
		float foo = (float)(uartClock)/(16.0*((float)(baudRate)));
		brdInt = (unsigned int)foo;
		brdFrc = (unsigned int)((foo-brdInt)*64.0 + 0.5);
	}

	template<uart::module::instance mod>
	void uart::uartMod<mod>::enableClock()
	{
		switch (mod)
		{
			case module::uart0:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<0);
			break;
			case module::uart1:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<1);
			break;
			case module::uart2:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<2);
			break;
			case module::uart3:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<3);
			break;
			case module::uart4:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<4);
			break;
			case module::uart5:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<5);
			break;
			case module::uart6:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<6);
			break;
			case module::uart7:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCUART |= (1<<7);
			break;

		}
	}

	template<uart::module::instance mod>
	void uart::uartMod<mod>::disableUart()
	{
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTCTL &= 0xfffe;
	}
	template<uart::module::instance mod>
	void uart::uartMod<mod>::enableUart()
	{
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTCTL |= 0x0001;
	}
	template<uart::module::instance mod>
	void uart::uartMod<mod>::configUart(configOptions::baudrate::_baudrate baudrate_,
			  configOptions::nbits::_nbits nbits_ ,
			  configOptions::parity::_parity parity_ ,
			  configOptions::stopbits::_stopbits stopbits_ ,
			  unsigned int interrupts_ ,
			  configOptions::fifo::_fifo fifo_ ,
			  clockSource::_clockSource clockSource_ )
	{
		unsigned int brdInt,brdFrc;
		utils::calcBrd(80000000,baudrate_,brdInt,brdFrc);
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTCTL &= 0xfffe;
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTIBRD = brdInt;
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTFBRD = brdFrc;
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTLCRH = (nbits_<<5) | (fifo_<<4) | (stopbits_<<3) | (parity_<<1);
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTCC = clockSource_;
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTIM = interrupts_;
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTIFLS = (0x1<<0) | (0x0<<3);
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTCTL |= 1;
	}
	template<uart::module::instance mod>
	void uart::uartMod<mod>::enableDMA(unsigned int dmaOptions)
	{
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTDMACTL = dmaOptions;
	}
	template<uart::module::instance mod>
	void uart::uartMod<mod>::sendByte(unsigned char data)
	{
		while(((reinterpret_cast<mapUart::UartRegs *>(mod)->UARTFR)&0x20) == 0x20);//THIS WORKS!!!
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTDR = data;
	}
	template<uart::module::instance mod>
	unsigned int uart::uartMod<mod>::sendString(const char* myString)
	{
		unsigned int i = 0;
		unsigned int size = std::strlen(myString);
		for(i=0;i<size;i++)
		{
			uartMod<mod>::sendByte(*myString);
			myString++;
		}
		return size;
	}

	template<uart::module::instance mod>
	unsigned char uart::uartMod<mod>::receiveByte()
	{
		return reinterpret_cast<mapUart::UartRegs *>(mod)->UARTDR;
	}
	template<uart::module::instance mod>
	void uart::uartMod<mod>::clearInterrupts(unsigned int interrupts_)
	{
		reinterpret_cast<mapUart::UartRegs *>
			(mod)->UARTICR |= interrupts_;
	}
	template<uart::module::instance mod>
	bool uart::uartMod<mod>::isInterruptAsserted(configOptions::interrupts::_interrupts interrupt_)
	{
		//check masked interrupt status...
		return ((reinterpret_cast<mapUart::UartRegs *>
					(mod)->UARTMIS) & interrupt_ == interrupt_);
	}

}
