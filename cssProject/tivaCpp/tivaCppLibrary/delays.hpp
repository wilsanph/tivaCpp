/*
 * delays.hpp
 *
 *  Created on: Sep 10, 2013
 *      Author: wilbert
 */

#ifndef DELAYS_HPP_
#define DELAYS_HPP_

namespace delays
{

	void delay_ms(unsigned int ms)
	{
		unsigned int i;
		for(i=0;i<5714*ms;i++);
	}

}


#endif /* DELAYS_HPP_ */
