/*
 * GObject.hpp
 *
 *  Created on: 12/03/2015
 *      Author: USER01
 */

#ifndef GOBJECT_HPP_
#define GOBJECT_HPP_

#include "../common.hpp"

namespace gObject
{
	namespace ObjectIDs
	{
		enum _ObjectIDs
		{
			OBJ_ID_NONE = 0,
			OBJ_ID_TIMER = 1,
			OBJ_ID_PWM = 2,
			OBJ_ID_UART = 3
		};
	}

	class GObject
	{

	public:
		GObject();
		virtual void init();
		u32 objID;

	protected:

	private:

	};
}



#endif /* GOBJECT_HPP_ */
