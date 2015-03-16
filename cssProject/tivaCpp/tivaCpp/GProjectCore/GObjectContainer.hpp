/*
 * GObjectContainer.hpp
 *
 *  Created on: 12/03/2015
 *      Author: USER01
 */

#ifndef GOBJECTCONTAINER_HPP_
#define GOBJECTCONTAINER_HPP_

#include "GObject.hpp"
#include <memory>
#include <vector>

namespace gObject
{
	typedef std::auto_ptr<gObject::GObject> GObjectContainer;
	typedef std::vector<GObjectContainer> GObjectsGroup;
}

#define GCast( GType, GObjContainer ) reinterpret_cast<GType>( GObjContainer.get() )


#endif /* GOBJECTCONTAINER_HPP_ */
