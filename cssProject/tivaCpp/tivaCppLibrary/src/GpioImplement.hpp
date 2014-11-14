

#pragma once

#include "../memorymap/MapGpio.hpp"
#include "../include/Gpio.hpp"
#include "../memorymap/mapClock.hpp"

namespace Gpio
{
	void enableClock(Gpio::peripheral::_peripheral peripheral_)
	{
		reinterpret_cast<mapClock::ClockRegs *>
			(mapClock::moduleAddresses::clockAddress)
			->RCGCGPIO |= (1<<peripheral_);
	}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::unlock()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOLOCK = 0x4c4f434b;
	}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::enableCommit()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOCR = 1<<pin;
	}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setPullUp()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOPUR |= 1<<pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setPullDown()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOPDR |= 1<<pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setOpenDrain()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOODR |= 1<<pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::enableAsDigital()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIODEN |= 1<<pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::disableDigitalFunc()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIODEN &= 0x00ff - (1<<pin);
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setMode(Gpio::options::mode::mode moder)
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOAFSEL |= moder<<pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setAnalogMode()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOAMSEL |= 1<<pin;//
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setIOmode(Gpio::options::IOmode::IOmode iomode)
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIODIR |= iomode<<pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setAlternateMode(Gpio::options::altModes::altModes altMode)
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port)->GPIOPCTL |= altMode<<4*pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setCurrentDrive_mA(Gpio::options::currentDrive::currentDrive mA){
		switch (mA)
		{
			case Gpio::options::currentDrive::mA_2:
				reinterpret_cast<mapGpio::GpioRegs *>
					(port)->GPIODR2R = 1<<pin;
				break;
			case Gpio::options::currentDrive::mA_4:
				reinterpret_cast<mapGpio::GpioRegs *>
					(port)->GPIODR4R = 1<<pin;
				break;
			case Gpio::options::currentDrive::mA_8:
				reinterpret_cast<mapGpio::GpioRegs *>
					(port)->GPIODR8R = 1<<pin;
				break;
		}
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setHigh()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port + 0x000003FC)->GPIODATA |= 1<<pin;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	bool Gpio::gpio<port,pin>::isHigh()
	{
		return ((reinterpret_cast<mapGpio::GpioRegs *>
				(port + 0x000003FC)->GPIODATA & (1<<pin)) == (1<<pin));
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setLow()
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port + 0x000003FC)->GPIODATA &= 0x00ff - (1<<pin);
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::toogle()
	{
		if(gpio<port,pin>::isHigh()){
			gpio<port,pin>::setLow();
		}
		else{
			gpio<port,pin>::setHigh();
		}
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setDataRegister(u8 data)
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port + 0x000003FC)->GPIODATA = data;
	}
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
	void Gpio::gpio<port,pin>::setBit(u8 bit,u8 value)
	{
		reinterpret_cast<mapGpio::GpioRegs *>
			(port + ( 0x00000004 << bit ))->GPIODATA = value << pin;
	}

	// Interrupt functionality ( thnks to Martin Carrasco :D )
	// TODO: Check for a bug with setting a whole register instead of using "or" in a bit ("|")
	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
		void Gpio::gpio<port,pin>::intSense(Gpio::options::Interrupt::intSense::intSense intSense, Gpio::options::Interrupt::intEvent::intEvent intEvent)
		{
			// Put a "0" in the "pin" bit
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOIS &= ((0xffffffff - (1<<pin)));
			// Put whatever the intSense value is in the "pin" bit
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOIS |= intSense<<pin;
			// Same here
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOIEV &= ((0xffffffff - (1<<pin)));
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOIEV |= intEvent<<pin;
		}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
		void Gpio::gpio<port,pin>::intSenseBothEdges()
		{
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOIBE |= 1<<pin;
		}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
		void Gpio::gpio<port,pin>::disableInterrupt()
		{
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOIM &= (0xffffffff) - (1<<pin);
		}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
		void Gpio::gpio<port,pin>::enableInterrupt()
		{
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOIM |= 1<<pin;
		}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
		void Gpio::gpio<port,pin>::clearInterrupt()
		{
			reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOICR |= 1<<pin;
		}

	template<Gpio::Port::_Port port,Gpio::Pin::_Pin pin>
		bool Gpio::gpio<port,pin>::isInterrupt()
		{
			return ((reinterpret_cast<mapGpio::GpioRegs *>
				(port)->GPIOMIS & (1<<pin)) == (1<<pin));
		}


}

