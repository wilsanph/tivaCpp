/*
int main()
 * GPTimer.hpp
 *
 *  Created on: 03/07/2013
 *      Author: wilbert
 */
#pragma once

#include "../memorymap/MapGptimer.hpp"

namespace gpTimer{

	enum gpTimerModule{
		timer0_simple = 0x40030000,
		timer1_simple = 0x40031000,
		timer2_simple = 0x40032000,
		timer3_simple = 0x40033000,
		timer4_simple = 0x40034000,
		timer5_simple = 0x40035000,
		timer0_wide  = 0x40036000,
		timer1_wide  = 0x40037000,
		timer2_wide  = 0x4004c000,
		timer3_wide  = 0x4004d000,
		timer4_wide  = 0x4004e000,
		timer5_wide  = 0x4004f000
	};
	namespace subTimers{
		enum subtimer{
			subTimerA = 0,
			subTimerB = 1
		};
	}
	namespace options{
		namespace timerOptions{
				namespace joiningMode
				{
					enum _joiningMode
					{
						timers_joinTimers 		= 0x00,
						timers_dontJoinTimers 	= 0x04
					};
				}
				namespace countDirection{
					enum countDir{
						down = 0,
						up = 1
					};
				}
				namespace interrupts{
					enum interrupts_subtimer{
						none		  = 0x00000000,
						timerAmatch   = 0x00000010,
						timerAtimeout = 0x00000001,
						timerBmatch   = 0x00000800,
						timerBtimeout = 0x00000100
					};
				}
				namespace alternateModeSelect{
					enum altMode{
						captureOrCompareEnabled = 0,
						pwmEnabled = 1
					};
				}
				namespace captureMode{
					enum capMode{
						edgeCount = 0,
						edgeTime = 1
					};
				}
				namespace timerMode{
					enum tMode{
						reserved = 0x00,
						oneShot  = 0x01,
						periodic = 0x02,
						capture  = 0x03
					};
				}
		}
		namespace pwmOptions
		{
			namespace outputLevel
			{
				enum _outputLevel
				{
					normal 		= 1,
					inverted	= 0
				};
			}
		}
		namespace timeCaptureOptions
		{
			namespace countDirection
			{
				enum _countDirection
				{
					positiveEdge	=	0x0,
					negativeEdge	=	0x1,
					bothEdges		=	0x3
				};
			}
		}
	}



	template<gpTimer::gpTimerModule Timer>
	class gpTimerMod
	{
	public:

		static inline void enableClock();
		static inline unsigned int config(gpTimer::subTimers::subtimer subtimer_,
								  unsigned long period_ms,
								  gpTimer::options::timerOptions::joiningMode::_joiningMode joiningMode_,
								  gpTimer::options::timerOptions::timerMode::tMode tMode,
								  gpTimer::options::timerOptions::countDirection::countDir cDir,
								  gpTimer::options::timerOptions::interrupts::interrupts_subtimer tInterrupt
								  );
		static inline void disableSubTimer(gpTimer::subTimers::subtimer subtimer_);
		static inline void enableSubTimer(gpTimer::subTimers::subtimer subtimer_);
		static inline void clearInterrupt(gpTimer::options::timerOptions::interrupts::interrupts_subtimer interrupt_);
	};

	template<gpTimer::gpTimerModule Timer,gpTimer::subTimers::subtimer subTimer>
	class pwm
	{
	public:
		static inline void enableClock();
		static inline void config
				(unsigned int period_us,
				 float duty,
				 gpTimer::options::pwmOptions::outputLevel::_outputLevel outputLevel_ = gpTimer::options::pwmOptions::outputLevel::normal
				);
		static inline void setDuty(float duty);
	};

	template<gpTimer::gpTimerModule Timer,gpTimer::subTimers::subtimer subTimer>
	class timeCap
	{
	public:
		static inline void enableClock()
		{

		}
		static inline void config(u32 us,
											options::timeCaptureOptions::countDirection::_countDirection countDirection_)
		{
			switch(subTimer)
			{
				case gpTimer::subTimers::subTimerA :

					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCFG &= (0xffffffff - 0x00000001);
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCFG = 0x00000004;
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMTAMR = (0x1<<2) | (0x3);
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL &= (0xffffffff)|(0x3<<2);
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL |= (countDirection_<<2);
					if(Timer>=gpTimer::timer0_wide)
					{
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTAPR = 0;
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTAILR = 80*us;
					}
					else
					{
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTAPR = 80;
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTAILR = us;
					}

				break;

				case	gpTimer::subTimers::subTimerB :

					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCFG = 0x00000004;
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMTBMR = (0x1<<2) | (0x3);
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL &= (0xffffffff)|(0x3<<10);
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL |= (countDirection_<<10);
					if(Timer>=gpTimer::timer0_wide)
					{
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTBPR = 0;
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTBILR = 80*us;
					}
					else
					{
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTBPR = 80;
						reinterpret_cast<MapGpTimer::GPTimerRegs *>
							(Timer)->GPTMTBILR = us;
					}

				break;
			}
			//END FUNCTION
		}
		static inline void disableSubtimer()
		{
			switch(subTimer)
			{
				case gpTimer::subTimers::subTimerA :
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL &= (0xffffffff - (1<<0));
				break;
				case gpTimer::subTimers::subTimerB :
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL &= (0xffffffff - (1<<8));
				break;
			}
		}
		static inline void enableSubtimer()
		{
			switch(subTimer)
			{
				case gpTimer::subTimers::subTimerA :
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL |= (1<<0);
				break;
				case gpTimer::subTimers::subTimerB :
					reinterpret_cast<MapGpTimer::GPTimerRegs *>
						(Timer)->GPTMCTL |= (1<<8);
				break;
			}
		}
	};
}

typedef gpTimer::gpTimerMod<gpTimer::timer0_simple> timer0;
typedef gpTimer::gpTimerMod<gpTimer::timer1_simple> timer1;
typedef gpTimer::gpTimerMod<gpTimer::timer2_simple> timer2;
typedef gpTimer::gpTimerMod<gpTimer::timer3_simple> timer3;
typedef gpTimer::gpTimerMod<gpTimer::timer4_simple> timer4;
typedef gpTimer::gpTimerMod<gpTimer::timer5_simple> timer5;

typedef gpTimer::gpTimerMod<gpTimer::timer0_wide> timerWide0;
typedef gpTimer::gpTimerMod<gpTimer::timer1_wide> timerWide1;
typedef gpTimer::gpTimerMod<gpTimer::timer2_wide> timerWide2;
typedef gpTimer::gpTimerMod<gpTimer::timer3_wide> timerWide3;
typedef gpTimer::gpTimerMod<gpTimer::timer4_wide> timerWide4;
typedef gpTimer::gpTimerMod<gpTimer::timer5_wide> timerWide5;

typedef gpTimer::pwm<gpTimer::timer0_wide,gpTimer::subTimers::subTimerA> pwmW_0A;
typedef gpTimer::pwm<gpTimer::timer0_wide,gpTimer::subTimers::subTimerB> pwmW_0B;
typedef gpTimer::pwm<gpTimer::timer1_wide,gpTimer::subTimers::subTimerA> pwmW_1A;
typedef gpTimer::pwm<gpTimer::timer1_wide,gpTimer::subTimers::subTimerB> pwmW_1B;
typedef gpTimer::pwm<gpTimer::timer2_wide,gpTimer::subTimers::subTimerA> pwmW_2A;
typedef gpTimer::pwm<gpTimer::timer2_wide,gpTimer::subTimers::subTimerB> pwmW_2B;
typedef gpTimer::pwm<gpTimer::timer3_wide,gpTimer::subTimers::subTimerA> pwmW_3A;
typedef gpTimer::pwm<gpTimer::timer3_wide,gpTimer::subTimers::subTimerB> pwmW_3B;
typedef gpTimer::pwm<gpTimer::timer4_wide,gpTimer::subTimers::subTimerA> pwmW_4A;
typedef gpTimer::pwm<gpTimer::timer4_wide,gpTimer::subTimers::subTimerB> pwmW_4B;
typedef gpTimer::pwm<gpTimer::timer5_wide,gpTimer::subTimers::subTimerA> pwmW_5A;
typedef gpTimer::pwm<gpTimer::timer5_wide,gpTimer::subTimers::subTimerB> pwmW_5B;

#include "../src/GptimerImplement.hpp"

