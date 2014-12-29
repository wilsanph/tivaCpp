/*
 * I2C.h
 *
 *  Created on: 31/07/2013
 *      Author: wilbert
 */

#pragma once

#include "../memorymap/MapI2C.h"

namespace i2c
{

	namespace module
	{
		enum _module
		{
			i2c0 = 0x40020000,
			i2c1 = 0x40021000,
			i2c2 = 0x40022000,
			i2c3 = 0x40023000
		};
	}

	namespace options
	{
		namespace rw
		{
			enum _rw
			{
				read = 1,
				write = 0
			};
		}
	}


	namespace configOptions
	{
		namespace mode
		{
			enum _mode
			{
				master = 1,
				slave  = 2
			};

		}
		namespace loopback
		{
			enum _loopback
			{
				enabled  = 1,
				disabled = 0
			};
		}

		namespace speed
		{
			enum _speed
			{
				standarMode  = 100000,
				fastMode     = 400000,
				fastPlusMode = 1000000
			};
		}
		namespace operation
		{
			enum _operation
			{
				runMasterEnable = 1,
				startCondition	= 2,
				stopCondition	= 4,
				generateACK		= 8
			};
		}
	}

	template<module::_module module_>
	class i2cMod
	{
		public:
			static inline void enableClock();
			static inline void writeSlaveAddress(unsigned int address,
												 options::rw::_rw rw_);
			static inline void configSpeed(configOptions::speed::_speed speed_);
			static inline void config(configOptions::mode::_mode mode_,
									  configOptions::loopback::_loopback loopback_,
									  configOptions::speed::_speed speed_);
			static inline bool send(unsigned char slaveAddress,
									unsigned char *buffData,
									unsigned int nBytes);

			static inline unsigned char readByteReg(unsigned char slaveAddress,
										   unsigned char reg);

			static inline void loadSlaveAddress(unsigned char slaveAddress,
												i2c::options::rw::_rw rw_);
			static inline void loadDataRegister(unsigned char data);
			static inline u8 getDataRegister();
			static inline void setOperation(u32 operation);
			static inline bool isBusBusy();
			static inline bool isThereAnError();
	};


}


typedef i2c::i2cMod<i2c::module::i2c0> I2C0;
typedef i2c::i2cMod<i2c::module::i2c1> I2C1;
typedef i2c::i2cMod<i2c::module::i2c2> I2C2;
typedef i2c::i2cMod<i2c::module::i2c3> I2C3;

#include "../src/I2Cimplement.hpp"
