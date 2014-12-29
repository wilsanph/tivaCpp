/*
 * Uart.h
 *
 *  Created on: 26/07/2013
 *      Author: wilbert
 */
#pragma once

#include "../memorymap/MapUart.h"
#include "math.h"

namespace uart
{
	namespace module
	{
		enum instance
		{
			uart0 = 0x4000c000,
			uart1 = 0x4000d000,
			uart2 = 0x4000e000,
			uart3 = 0x4000f000,
			uart4 = 0x40010000,
			uart5 = 0x40011000,
			uart6 = 0x40012000,
			uart7 = 0x40013000
		};
	}
	namespace uartclock
	{
		enum _uartclock
		{
			uartclock_16Mhz = 16000000
		};
	}
	namespace clockSource
	{
		enum _clockSource
		{
			systemClock = 0x0,
			pioscClock  = 0x5
		};
	}
	namespace configOptions
	{
		namespace baudrate
		{
			enum _baudrate
			{
				baud_9600   = 9600,
				baud_19200  = 19200,
				baud_38400  = 38400,
				baud_57600  = 57600,
				baud_115200 = 115200,
				baud_100000 = 100000,
				baud_230400 = 230400,
				baud_921600 = 921600,
				baud_1000000= 1000000,
				baud_3000000= 3000000
			};
		}
		namespace nbits
		{
			enum _nbits
			{
				bits_8 = 0x03,
				bits_7 = 0x02,
				bits_6 = 0x01,
				bits_5 = 0x00
			};
		}
		namespace parity{
			enum _parity
			{
				none = 0,
				odd  = 1,
				even = 3
			};
		}
		namespace stopbits
		{
			enum _stopbits
			{
				stopBits_one = 0,
				stopBits_two = 1
			};
		}
		namespace interrupts
		{
			enum _interrupts
			{
				none				= 0,
				receiveInt 			= 16,
				receiveTimeOut 		= 64,
				transmitInt			= 32

			};
		}
		namespace fifo
		{
			enum _fifo
			{
				fifoEnabled  = 1,
				fifoDisabled = 0
			};
		}
		namespace dma
		{
			enum dmaOpts
			{
				dmaTxEnabled = 2,
				dmaRxEnabled = 1
			};
		}
	}
	namespace utils
	{
		void calcBrd(unsigned int uartClock,
					 unsigned int baudRate,
					 unsigned int& brdInt,
					 unsigned int& brdFrc);

	}

	template<uart::module::instance mod>
	class uartMod
	{
		public:

			static inline void enableClock();
			static inline void disableUart();
			static inline void enableUart();
			static inline void configUart(configOptions::baudrate::_baudrate baudrate_,
										  configOptions::nbits::_nbits nbits_ = configOptions::nbits::bits_8,
										  configOptions::parity::_parity parity_ = configOptions::parity::none,
										  configOptions::stopbits::_stopbits stopbits_ = configOptions::stopbits::stopBits_one,
										  unsigned int interrupts_  = configOptions::interrupts::receiveInt,
										  configOptions::fifo::_fifo fifo_ = configOptions::fifo::fifoDisabled,
										  clockSource::_clockSource clockSource_  = clockSource::systemClock);
			static inline void enableDMA(unsigned int dmaOptions);
			static inline void sendByte(unsigned char data);
			static inline unsigned int sendString(const char* myString);
			static inline unsigned char receiveByte();
			static inline void clearInterrupts(unsigned int interrupts_);
			static inline bool isInterruptAsserted(configOptions::interrupts::_interrupts interrupt_);
			static inline void sendUintNum(u16 num)
			{
				u8 digit = 0;u8 numOfDigits = 0;u8 i;
				u16 dummyNum = num;
				if(num>=1)
				{
					while(dummyNum>=1)
					{
						numOfDigits++;
						dummyNum = dummyNum/10;
					}
					for(i=numOfDigits;i>0;i--)
					{
						u16 dummy = num;
						u8 j;
						u16 prod = 1;
						for(j=0;j<i-1;j++)
						{
							dummy = dummy/10;
						}
						digit = (u8)(dummy);
						uartMod<mod>::sendByte((u8)(48+digit));
						for(j=0;j<i-1;j++)
						{
							prod *= 10;
						}
						num = num - digit*prod;
					}
				}
				else
				{
					uartMod<mod>::sendByte('0');
				}
			}
	};
}



#define UART0_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart0)
#define UART1_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart1)
#define UART2_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart2)
#define UART3_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart3)
#define UART4_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart4)
#define UART5_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart5)
#define UART6_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart6)
#define UART7_REGS reinterpret_cast<mapUart::UartRegs *>(uart::module::uart7)

typedef uart::uartMod<uart::module::uart0> UART0;
typedef uart::uartMod<uart::module::uart1> UART1;
typedef uart::uartMod<uart::module::uart2> UART2;
typedef uart::uartMod<uart::module::uart3> UART3;
typedef uart::uartMod<uart::module::uart4> UART4;
typedef uart::uartMod<uart::module::uart5> UART5;
typedef uart::uartMod<uart::module::uart6> UART6;
typedef uart::uartMod<uart::module::uart7> UART7;


#include "../src/UartImplement.hpp"
