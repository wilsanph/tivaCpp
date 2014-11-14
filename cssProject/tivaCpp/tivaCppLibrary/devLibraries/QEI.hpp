/*
 * QEI.hpp
 *
 *  Created on: 17/09/2013
 *      Author: wilbert
 */

#include "../common.h"
#include "mapQEI.hpp"
#include "../include/clock.hpp"


namespace qei
{

	namespace options
	{
		namespace captureMode
		{
			enum captureMode_
			{
				mode1 = 0,
				mode2 = 1
			};
		}
		namespace velocityPredivider
		{
			enum velocityPredivider
			{
				div_1	= 0,
				div_2	= 1,
				div_4	= 2,
				div_8	= 3,
				div_16	= 4,
				div_32	= 5,
				div_64	= 6,
				div_128	= 7
			};
		}

		namespace stallOnDebugger
		{
			enum stallOnDebugger_{
				dontStall 	= 0,
				stall 		= 1
			};


		}
		namespace capVelocity
		{
			enum capVelocity_
			{
				captureVel 	= 1,
				dontCaptVel	= 0
			};

		}
	}


	template<mapQEI::QEImodules::module mod>
	class qeiMod
	{
		public:

		static inline void enableClock()
		{
			switch (mod) {
				case mapQEI::QEImodules::QEI0 :
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCQEI |= (1<<0);
				break;
				case mapQEI::QEImodules::QEI1 :
					reinterpret_cast<mapClock::ClockRegs *>
						(mapClock::moduleAddresses::clockAddress)
						->RCGCQEI |= (1<<1);
				break;
			}
		}

		static inline void config(options::stallOnDebugger::stallOnDebugger_ stall,
								  	  	   options::velocityPredivider::velocityPredivider veldiv,
								  	  	   options::capVelocity::capVelocity_ capVel,
								  	  	   options::captureMode::captureMode_ capmode)
		{
			reinterpret_cast<mapQEI::QEIregs *>
				(mod)->QEICTL = (stall<<12) | (veldiv<<6) | (capVel<<5) | (capmode<<3);
			reinterpret_cast<mapQEI::QEIregs *>
				(mod)->QEIMAXPOS = 0xffffffff;
		}

		static inline void setTimer(u32 timerValue)
		{
			reinterpret_cast<mapQEI::QEIregs *>
				(mod)->QEILOAD = timerValue;
		}

		static inline void enableQEI()
		{
			reinterpret_cast<mapQEI::QEIregs *>
				(mod)->QEICTL |= 1;
		}
		static inline u32 getCount()
		{
			return reinterpret_cast<mapQEI::QEIregs *>(mod)->QEIPOS;
		}
		static inline u32 getSpeedReg()
		{
			return reinterpret_cast<mapQEI::QEIregs *>(mod)->QEISPEED;
		}
	};

}



typedef qei::qeiMod<mapQEI::QEImodules::QEI0> qei0;
typedef qei::qeiMod<mapQEI::QEImodules::QEI1> qei1;



