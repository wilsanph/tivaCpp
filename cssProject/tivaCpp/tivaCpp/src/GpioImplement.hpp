/*
 * GpioImplement.hpp
 *
 *  Created on: 27/12/2014
 *      Author: USER01
 */

#ifndef GPIOIMPLEMENT_HPP_
#define GPIOIMPLEMENT_HPP_

#pragma once

#include "../memorymap/MapGpio.hpp"
#include "../include/Gpio.hpp"
#include "../memorymap/GMapClock.hpp"

namespace Gpio
{
	
	template<Gpio::port::_port pPort>
	void Gpio::Port<pPort>::enableClock( Gpio::peripheral::_peripheral pPeripheral )
	{
		reinterpret_cast<MapClock::ClockRegs*>
			( MapClock::moduleAddresses::clockAddress )->RCGCGPIO = ( 1 << pPeripheral );
	}

	template<Gpio::port::_port pPort>
	void Gpio::Port<pPort>::unlock()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( pPort )->GPIOLOCK = 0x4c4f434b;
	}


	Gpio::Pin::Pin()
	{
		this->m_port = Gpio::port::GPIOPortF_APB;
		this->m_pin = Gpio::pin::pin1;
	}

	Gpio::Pin::Pin( Gpio::port::_port pPort, Gpio::pin::_pin pPin )
	{
		this->m_port = pPort;
		this->m_pin = pPin;
	}

	void Gpio::Pin::enableDigitalFunc()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIODEN |= 1 << this->m_pin;
	}

	void Gpio::Pin::disableDigitalFunc()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIODEN &= 0xffffffff - ( 1 << this->m_pin );
	}

	void Gpio::Pin::setMode( Gpio::config::mode::_mode pinMode )
	{
		volatile u32 unchangedPart = reinterpret_cast<MapGpio::GpioRegs*>( this->m_port )->GPIOAFSEL;
		unchangedPart &= 0xffffffff - ( 1 << this->m_pin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOAFSEL = unchangedPart + ( pinMode << this->m_pin );
	}

	void Gpio::Pin::setIOMode( Gpio::config::ioMode::_ioMode pinIOMode )
	{
		volatile u32 unchangedPart = reinterpret_cast<MapGpio::GpioRegs*>( this->m_port )->GPIODIR;
		unchangedPart &= 0xffffffff - ( 1 << this->m_pin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIODIR = unchangedPart + ( pinIOMode << this->m_pin );
	}

	void Gpio::Pin::setLow()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port + ( 0x00000004 << this->m_pin ) )->GPIODATA = 0 << this->m_pin;
	}

	void Gpio::Pin::setHigh()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port + ( 0x00000004 << this->m_pin ) )->GPIODATA = 1 << this->m_pin;
	}

	void Gpio::Pin::setValue( Gpio::state::_state pinState )
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port + ( 0x00000004 << this->m_pin ) )->GPIODATA = pinState << this->m_pin;
	}

	void Gpio::Pin::toggle()
	{
		volatile u32 prevValue = reinterpret_cast<MapGpio::GpioRegs*>
									( this->m_port + ( 0x00000004 << this->m_pin ) )->GPIODATA;
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port + ( 0x00000004 << this->m_pin ) )->GPIODATA = 0xffffffff - prevValue;
	}

	bool Gpio::Pin::isHigh()
	{
		return ( ( reinterpret_cast<MapGpio::GpioRegs *>
					( this->m_port + ( 0x00000004 << this->m_pin ) )->GPIODATA & ( 1 << this->m_pin ) ) == ( 1 << this->m_pin ) );
	}

	bool Gpio::Pin::isLow()
	{
		return !this->isHigh();
	}

	void Gpio::Pin::enableInterrupt()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIM |= 1 << this->m_pin;

	}

	void Gpio::Pin::disableInterrupt()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIM &= 0xffffffff - ( 1 << this->m_pin );
	}

	void Gpio::Pin::clearFlag()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOICR |= ( 1 << this->m_pin );
	}

	void Gpio::Pin::configInterrupt( Gpio::config::interrupts::intSenseType::_intSenseType pinSenseType,
							  		 Gpio::config::interrupts::intSenseBothEdges::_intSenseBothEdges pinSenseBothEdges,
							  		 Gpio::config::interrupts::intEventType::_intEventType pinEventType )
	{
		this->disableInterrupt();

		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIS &= 0xffffffff - ( 1 << this->m_pin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIS |= pinSenseType << this->m_pin;

		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIBE &= 0xffffffff - ( 1 << this->m_pin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIBE |= pinSenseBothEdges << this->m_pin;

		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIEV &= 0xffffffff - ( 1 << this->m_pin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOIEV |= pinEventType << this->m_pin;						

		this->clearFlag();
		this->enableInterrupt();
	}

	void Gpio::Pin::setAnalogMode()
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOAMSEL |= ( 1 << this->m_pin );
	}

	void Gpio::Pin::setAlternateMode( Gpio::config::altModes::_altModes pAltMode )
	{
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOPCTL &= 0xffffffff - ( 0xf << this->m_pin );
		reinterpret_cast<MapGpio::GpioRegs*>
			( this->m_port )->GPIOPCTL |= pAltMode << this->m_pin;
	}

	void Gpio::Pin::setCurrentDrive( Gpio::config::currentDrive::_currentDrive pCurrentDrive )
	{
		switch (pCurrentDrive)
		{
			case Gpio::config::currentDrive::mA_2:
				reinterpret_cast<MapGpio::GpioRegs *>
					( this->m_port )->GPIODR2R = 1 << this->m_pin;
				break;
			case Gpio::config::currentDrive::mA_4:
				reinterpret_cast<MapGpio::GpioRegs *>
					( this->m_port )->GPIODR4R = 1 << this->m_pin;
				break;
			case Gpio::config::currentDrive::mA_8:
				reinterpret_cast<MapGpio::GpioRegs *>
					( this->m_port )->GPIODR8R = 1 << this->m_pin;
				break;
		}
	}

	void Gpio::Pin::setPullUp()
	{
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->m_port )->GPIOPUR |= 1 << this->m_pin;
	}

	void Gpio::Pin::setPullDown()
	{
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->m_port )->GPIOPDR |= 1 << this->m_pin;		
	}

	void Gpio::Pin::setOpenDrain()
	{
		reinterpret_cast<MapGpio::GpioRegs *>
			( this->m_port )->GPIOODR |= 1 << this->m_pin;		
	}	
}



#endif /* GPIOIMPLEMENT_HPP_ */
