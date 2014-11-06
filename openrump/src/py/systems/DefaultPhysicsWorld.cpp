// ----------------------------------------------------------------------------
// DefaultPhysicsWorldInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/DefaultPhysicsWorld.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

void exportPyDefaultPhysicsWorld()
{
    using namespace boost::python;
    
    class_<OpenRump::DefaultPhysicsWorld, boost::noncopyable/*, bases<Ontology::System>*/ >("DefaultPhysicsWorld", no_init)
        ;
}
