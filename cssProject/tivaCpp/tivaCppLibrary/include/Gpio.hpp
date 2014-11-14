

#pragma once

#include "../memorymap/MapGpio.hpp"

namespace Gpio{

	namespace options{

		namespace mode{
			enum mode{
				gpio = 0,
				alternate = 1
			};
		}
		namespace IOmode{
			enum IOmode{
				input = 0,
				output = 1
			};
		}
		namespace altModes{
			enum altModes{
				alt1  = 1,
				alt2  = 2,
				alt3  = 3,
				alt4  = 4,
				alt5  = 5,
				alt6  = 6,
				alt7  = 7,
				alt8  = 8,
				alt9  = 9,
				alt10 = 10,
				alt11 = 11,
				alt12 = 12,
				alt13 = 13,
				alt14 = 14,
				alt15 = 15
			};
		}
		namespace currentDrive {
			enum currentDrive{
				mA_2 = 0,
				mA_4 = 1,
				mA_8 = 2
			};
		}

		namespace Interrupt{
			namespace intSense{
				enum intSense{
					edge = 0,
					level = 1
				};
			}
			namespace intEvent{
				enum intEvent{
					down = 0,
					up = 1
				};
			}
		}
	}

	namespace Pin
	{
		enum _Pin{
			pin0 = 0,
			pin1 = 1,
			pin2 = 2,
			pin3 = 3,
			pin4 = 4,
			pin5 = 5,
			pin6 = 6,
			pin7 = 7
		};
	}

	namespace Port
	{
		enum _Port{

			GPIOPortA_APB= 0x40004000,
			GPIOPortA_AHB= 0x40058000,
			GPIOPortB_APB= 0x40005000,
			GPIOPortB_AHB= 0x40059000,
			GPIOPortC_APB= 0x40006000,
			GPIOPortC_AHB= 0x4005A000,
			GPIOPortD_APB= 0x40007000,
			GPIOPortD_AHB= 0x4005B000,
			GPIOPortE_APB= 0x40024000,
			GPIOPortE_AHB= 0x4005C000,
			GPIOPortF_APB= 0x40025000,
			GPIOPortF_AHB= 0x4005D000
		};
	}

	namespace peripheral
	{
		enum _peripheral
		{
			GPIOA = 0,
			GPIOB = 1,
			GPIOC = 2,
			GPIOD = 3,
			GPIOE = 4,
			GPIOF = 5
		};
	}


	inline void enableClock(peripheral::_peripheral peripheral_);

	template<Gpio::Port::_Port Port,Gpio::Pin::_Pin pin>
	class gpio{
		public:

			inline static void unlock();
			inline static void enableCommit();
			inline static void setPullUp();
			inline static void setPullDown();
			inline static void setOpenDrain();
			inline static void enableAsDigital();
			inline static void disableDigitalFunc();
			inline static void setMode(options::mode::mode moder);
			inline static void setAnalogMode();
			inline static void setIOmode(options::IOmode::IOmode iomode);
			inline static void setAlternateMode(options::altModes::altModes altMode);
			inline static void setCurrentDrive_mA(options::currentDrive::currentDrive mA);
			//inline static void configGPIO();
			//inline static void configAlternate();
			//inline static void configAnalog();

/*
 * this functions have been successfully tested
 *
 */
			inline static void setHigh();
			inline static bool isHigh();
			inline static void setLow();
			inline static void toogle();



			inline static void setDataRegister(u8 data);
			inline static void setBit(u8 bit,u8 value);

			inline static void intSense(options::Interrupt::intSense::intSense intSense, options::Interrupt::intEvent::intEvent intEvent);
			inline static void intSenseBothEdges();
			inline static void disableInterrupt();
			inline static void enableInterrupt();
			inline static void clearInterrupt();
			inline static bool isInterrupt();


	};



}


typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin0> PA0;
typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin1> PA1;
typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin2> PA2;
typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin3> PA3;
typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin4> PA4;
typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin5> PA5;
typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin6> PA6;
typedef Gpio::gpio<Gpio::Port::GPIOPortA_APB,Gpio::Pin::pin7> PA7;

typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin0> PB0;
typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin1> PB1;
typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin2> PB2;
typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin3> PB3;
typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin4> PB4;
typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin5> PB5;
typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin6> PB6;
typedef Gpio::gpio<Gpio::Port::GPIOPortB_APB,Gpio::Pin::pin7> PB7;

typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin0> PC0;
typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin1> PC1;
typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin2> PC2;
typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin3> PC3;
typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin4> PC4;
typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin5> PC5;
typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin6> PC6;
typedef Gpio::gpio<Gpio::Port::GPIOPortC_APB,Gpio::Pin::pin7> PC7;

typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin0> PD0;
typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin1> PD1;
typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin2> PD2;
typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin3> PD3;
typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin4> PD4;
typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin5> PD5;
typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin6> PD6;
typedef Gpio::gpio<Gpio::Port::GPIOPortD_APB,Gpio::Pin::pin7> PD7;

typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin0> PE0;
typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin1> PE1;
typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin2> PE2;
typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin3> PE3;
typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin4> PE4;
typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin5> PE5;
typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin6> PE6;
typedef Gpio::gpio<Gpio::Port::GPIOPortE_APB,Gpio::Pin::pin7> PE7;

typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin0> PF0;
typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin1> PF1;
typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin2> PF2;
typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin3> PF3;
typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin4> PF4;
typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin5> PF5;
typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin6> PF6;
typedef Gpio::gpio<Gpio::Port::GPIOPortF_APB,Gpio::Pin::pin7> PF7;




#include "../src/GpioImplement.hpp"
