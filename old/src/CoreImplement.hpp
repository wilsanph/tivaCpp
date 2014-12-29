

#pragma once

#include "../memorymap/MapCore.hpp"
#include "../include/Core.hpp"

namespace core
{
	unsigned char IntEnableMaster()
	{
		//
			// Read PRIMASK and enable interrupts.
			//
			__asm("    mrs     r0, PRIMASK\n"
				  "    cpsie   i\n"
				  "    bx      lr\n");

			//
			// The following keeps the compiler happy, because it wants to see a
			// return value from this function.  It will generate code to return
			// a zero.  However, the real return is the "bx lr" above, so the
			// return(0) is never executed and the function returns with the value
			// you expect in R0.
			//
			return 0;
	}

	void enableInterrupt(core::interrupts::_interrupt interrupt_)
	{
		if(interrupt_>=16)
		{
			if((interrupt_-16)<32)
			{
				unsigned int shift = (interrupt_-16);
				reinterpret_cast<mapCore::NVICRegs *>
					(mapCore::coreAddress +
					 mapCore::offset::nvic)->EN0 |= (1<<shift);
			}
			else if((interrupt_-16)<64)
			{
				unsigned int shift = (interrupt_-16-32);
				reinterpret_cast<mapCore::NVICRegs *>
					(mapCore::coreAddress +
					 mapCore::offset::nvic)->EN1 |= (1<<shift);
			}
			else if((interrupt_-16)<96)
			{
				unsigned int shift = (interrupt_-16-64);
				reinterpret_cast<mapCore::NVICRegs *>
					(mapCore::coreAddress +
					 mapCore::offset::nvic)->EN2 |= (1<<shift);
			}
			else if((interrupt_-16)<128)
			{
				unsigned int shift = (interrupt_-16-96);
				reinterpret_cast<mapCore::NVICRegs *>
					(mapCore::coreAddress +
					 mapCore::offset::nvic)->EN3 |= (1<<shift);
			}
		}
	}


}
