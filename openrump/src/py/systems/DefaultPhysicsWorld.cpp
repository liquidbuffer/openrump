// ----------------------------------------------------------------------------
// DefaultPhysicsWorldInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/DefaultPhysicsWorld.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

using namespace OpenRump;
using namespace boost::python;

void exportPyDefaultPhysicsWorld()
{
    class_<DefaultPhysicsWorld, boost::noncopyable, bases<SystemWrapper> >("DefaultPhysicsWorld", no_init)
        ;
}
