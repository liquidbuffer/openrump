// ----------------------------------------------------------------------------
// PyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/EntityBase.hpp>

using namespace OpenRump;

void exportEntityBaseInterface()
{
    using namespace boost::python;
    class_<EntityBase, boost::noncopyable>("EntityBase", no_init)
        .def("set_camera_distance", &EntityBase::setCameraDistance)
    ;
}
