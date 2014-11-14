/*
 * mapQEI.hpp
 *
 *  Created on: 17/09/2013
 *      Author: wilbert
 */

#include "../common.h"

namespace mapQEI
{

	namespace QEImodules
	{
		enum module
		{
			QEI0 = 0x4002c000,
			QEI1 = 0x4002d000
		};
	}


	struct QEIregs
	{
		u32 QEICTL;
		u32 QEISTAT;
		u32 QEIPOS;
		u32 QEIMAXPOS;
		u32 QEILOAD;
		u32 QEITIME;
		u32 QEICOUNT;
		u32 QEISPEED;
		u32 QEIINTEN;
		u32 QEIRIS;
		u32 QEIISC;
	};




}


