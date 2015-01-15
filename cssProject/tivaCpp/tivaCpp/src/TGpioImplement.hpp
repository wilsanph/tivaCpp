/*
 * TGpioImplement.hpp
 *
 *  Created on: 29/12/2014
 *      Author: USER01
 */

#ifndef TGPIOIMPLEMENT_HPP_
#define TGPIOIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapGpio.hpp"
#include "../include/Gpio.hpp"

namespace Gpio
{

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::enableDigitalFunc()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIODEN |= 1 << pPin;
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::disableDigitalFunc()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIODEN &= 0xffffffff - ( 1 << pPin );
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setMode( Gpio::config::mode::_mode pinMode )
	{
		volatile u32 unchangedPart = reinterpret_cast<MapGpio::GpioRegs*>( pPort )->GPIOAFSEL;
		unchangedPart &= 0xffffffff - ( 1 << pPin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOAFSEL = unchangedPart + ( pinMode << pPin );
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setIOMode( Gpio::config::ioMode::_ioMode pinIOMode )
	{
		volatile u32 unchangedPart = reinterpret_cast<MapGpio::GpioRegs*>( pPort )->GPIODIR;
		unchangedPart &= 0xffffffff - ( 1 << pPin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIODIR = unchangedPart + ( pinIOMode << pPin );
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setLow()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort + ( 0x00000004 << pPin ) )->GPIODATA = 0 << pPin;
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setHigh()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort + ( 0x00000004 << pPin ) )->GPIODATA = 1 << pPin;
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setValue( Gpio::state::_state pinState )
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort + ( 0x00000004 << pPin ) )->GPIODATA = pinState << pPin;
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::toggle()
	{
		volatile u32 prevValue = reinterpret_cast<MapGpio::GpioRegs*>
									( pPort + ( 0x00000004 << pPin ) )->GPIODATA;
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort + ( 0x00000004 << pPin ) )->GPIODATA = 0xffffffff - prevValue;
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	bool Gpio::tPin<pPort,pPin>::isHigh()
	{
		return ( ( reinterpret_cast<MapGpio::GpioRegs *>
					( pPort + ( 0x00000004 << pPin ) )->GPIODATA & ( 1 << pPin ) ) == ( 1 << pPin ) );
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	bool Gpio::tPin<pPort,pPin>::isLow()
	{
		return !Gpio::pPin<pPort,pPin>::isHigh();
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::enableInterrupt()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIM |= 1 << pPin;

	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::disableInterrupt()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIM &= 0xffffffff - ( 1 << pPin );
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::clearFlag()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOICR |= ( 1 << pPin );
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::configInterrupt( Gpio::config::interrupts::intSenseType::_intSenseType pinSenseType,
							  		 Gpio::config::interrupts::intSenseBothEdges::_intSenseBothEdges pinSenseBothEdges,
							  		 Gpio::config::interrupts::intEventType::_intEventType pinEventType )
	{
		Gpio::tPin<pPort,pPin>::disableInterrupt();

		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIS &= 0xffffffff - ( 1 << pPin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIS |= pinSenseType << pPin;

		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIBE &= 0xffffffff - ( 1 << pPin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIBE |= pinSenseBothEdges << pPin;

		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIEV &= 0xffffffff - ( 1 << pPin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOIEV |= pinEventType << pPin;						

		Gpio::tPin<pPort,pPin>::clearFlag();
		Gpio::tPin<pPort,pPin>::enableInterrupt();
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setAnalogMode()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOAMSEL |= ( 1 << pPin );
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setAlternateMode( Gpio::config::altModes::_altModes pAltMode )
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOPCTL &= 0xffffffff - ( 0xf << pPin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOPCTL |= pAltMode << pPin;
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setCurrentDrive( Gpio::config::currentDrive::_currentDrive pCurrentDrive )
	{
		switch (pCurrentDrive)
		{
			case Gpio::config::currentDrive::mA_2:
				reinterpret_cast<MapGpio::GpioRegs *>
					( pPort )->GPIODR2R = 1 << pPin;
				break;
			case Gpio::config::currentDrive::mA_4:
				reinterpret_cast<MapGpio::GpioRegs *>
					( pPort )->GPIODR4R = 1 << pPin;
				break;
			case Gpio::config::currentDrive::mA_8:
				reinterpret_cast<MapGpio::GpioRegs *>
					( pPort )->GPIODR8R = 1 << pPin;
				break;
		}
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setPullUp()
	{
		reinterpret_cast<MapGpio::GpioRegs *>
			( pPort )->GPIOPUR |= 1 << pPin;
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setPullDown()
	{
		reinterpret_cast<MapGpio::GpioRegs *>
			( pPort )->GPIOPDR |= 1 << pPin;		
	}

	template<Gpio::port::_port pPort,Gpio::pin::_pin pPin>
	void Gpio::tPin<pPort,pPin>::setOpenDrain()
	{
		reinterpret_cast<MapGpio::GpioRegs *>
			( pPort )->GPIOODR |= 1 << pPin;		
	}	

}



#endif /* TGPIOIMPLEMENT_HPP_ */
