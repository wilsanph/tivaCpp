/*
 * I2Cimplement.hpp
 *
 *  Created on: Aug 24, 2013
 *      Author: wilbert
 */

#pragma once

#include "../include/I2C.h"
#include "../memorymap/MapI2C.h"
#include "../memorymap/mapClock.hpp"

namespace i2c
{
	template<module::_module module_>
	void i2c::i2cMod<module_>::enableClock()
	{
		switch (module_)
		{
			case i2c::module::i2c0:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCI2C |= (1<<0);
			break;
			case i2c::module::i2c1:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCI2C |= (1<<1);
			break;
			case i2c::module::i2c2:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCI2C |= (1<<2);
			break;
			case i2c::module::i2c3:
				reinterpret_cast<mapClock::ClockRegs *>
					(mapClock::moduleAddresses::clockAddress)
					->RCGCI2C |= (1<<3);
			break;
		}
	}

	template<module::_module module_>
	void i2c::i2cMod<module_>::writeSlaveAddress(unsigned int address,
												 i2c::options::rw::_rw rw_)
	{
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMSA = (address<<1) | rw_;
	}
	template<module::_module module_>
	void i2c::i2cMod<module_>::configSpeed(i2c::configOptions::speed::_speed speed_)
	{
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMTPR = (80*1000000/(2*10*speed_))-1;
	}
	template<module::_module module_>
	void i2c::i2cMod<module_>::config(i2c::configOptions::mode::_mode mode_,
			  	  	  	  	  	  	  i2c::configOptions::loopback::_loopback loopback_,
			  	  	  	  	  	  	  i2c::configOptions::speed::_speed speed_)
	{
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMCR = (mode_<<4) | (loopback_);
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMTPR = (80*1000000/(2*10*speed_))-1;
	}
	template<module::_module module_>
	bool i2c::i2cMod<module_>::send(unsigned char slaveAddress,
			unsigned char *buffData,
			unsigned int nBytes)
	{
		unsigned int i = 0;
		//bool sentinel = true;
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMSA = (slaveAddress<<1)|0x00;
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMDR = *buffData;
		//while(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&(0x40))==0x40);
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMCS = 0x03;
		buffData++;
		i++;
		while(true)
		{
			while(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&(0x01))==1);
			if(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&0x02)==0x02)
			{
				while(1);
				//return false;
			}
			reinterpret_cast<mapi2c::I2CRegs *>
				(module_)->I2CMDR = *buffData;
			buffData++;
			i++;
			if(i==(nBytes))
			{
				break;
			}
			reinterpret_cast<mapi2c::I2CRegs *>
				(module_)->I2CMCS = 0x01;
		}
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMCS = 0x05;
		while(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&(0x01))==0x01);
		if(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&0x02)==0x02)
		{
			while(1);
			//return false;
		}
		return true;
	}
	template<module::_module module_>
	unsigned char i2c::i2cMod<module_>::readByteReg(unsigned char slaveAddress,
			   	   	   	   	   	   	   	   unsigned char reg)
	{
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMSA = (slaveAddress<<1)|0;
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMDR = reg;
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMCS = 0x03;//generate start and start transaction
		while(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&(0x01))==1);
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMSA = (slaveAddress<<1)|1;
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMCS = 0x07;
		while(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&(0x01))==1);
		if(((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&0x02)==0x02)
		{
			while(1);
		}
		return reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMDR;
	}
	template<module::_module module_>
	void i2c::i2cMod<module_>::loadSlaveAddress(unsigned char slaveAddress,
												i2c::options::rw::_rw rw_)
	{
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMSA = (slaveAddress<<1)| rw_;
	}
	template<module::_module module_>
	void i2c::i2cMod<module_>::loadDataRegister(unsigned char data)
	{
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMDR = data;
	}
	template<module::_module module_>
	void i2c::i2cMod<module_>::setOperation(u32 operation)
	{
		reinterpret_cast<mapi2c::I2CRegs *>
			(module_)->I2CMCS = operation;
	}
	template<module::_module module_>
	bool i2c::i2cMod<module_>::isBusBusy()
	{
		return ((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&(0x01))==1 ;
	}
	template<module::_module module_>
	bool i2c::i2cMod<module_>::isThereAnError()
	{
		return ((reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMCS)&0x02)==0x02 ;
	}
	template<module::_module module_>
	u8 i2c::i2cMod<module_>::getDataRegister()
	{
		return (u8)(reinterpret_cast<mapi2c::I2CRegs *>(module_)->I2CMDR);
	}
}
