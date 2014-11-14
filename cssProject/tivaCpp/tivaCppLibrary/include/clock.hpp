/*
 * clock.h
 *
 *  Created on: Aug 14, 2013
 *      Author: wilbert
 */
#pragma once

#include "../memorymap/mapClock.hpp"

namespace clock
{

	namespace configOptions
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
			enum sources
			{
				mainOscilator = 0x0,
				precisionInternalOscillator = 0x1,
				precisionInternalOscillator_Div4 = 0x2,
				internal_30khz = 0x3,
				external_32_768khz = 0x7
			};
		}
		namespace enablePIOSC
		{
			enum _enablePIOSC
			{
				enablePinternalOsc	= 0,
				disablePinternalOsc	= 1
			};
		}
		namespace enableMOSC
		{
			enum _enableMOSC
			{
				enableMainOsc		= 0,
				disableMainOsc		= 1
			};
		}
	}


	class clock
	{
		public:

			static inline void config(configOptions::clockSource::sources clockSource,
					 				  configOptions::clockRate::_clockRate clockRate_,
					 				  configOptions::enablePIOSC::_enablePIOSC enablePIOSC_,
					 				  configOptions::enableMOSC::_enableMOSC enableMOSC_);
	};


}


#include "../src/ClockImplement.hpp"
