// ----------------------------------------------------------------------------
// PyEntityBaseInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/EntityBase.hpp>

using namespace OpenRump;

// ----------------------------------------------------------------------------
// overloads

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(pyAttachCameraToOrbit_overloads, pyAttachCameraToOrbit, 1, 2);

void exportEntityBaseInterface()
{
    using namespace boost::python;
    class_<EntityBase, boost::noncopyable>("EntityBase", no_init)
        .def("add_controller", &EntityBase::addController)
        .def("remove_controller", &EntityBase::removeController)
    ;
}
