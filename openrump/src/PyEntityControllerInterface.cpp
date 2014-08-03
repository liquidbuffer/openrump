// ----------------------------------------------------------------------------
// PyEntityControllerInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/EntityController.hpp>
#include <openrump/EntityBase.hpp>

using namespace OpenRump;

// ----------------------------------------------------------------------------
// overloads

void exportEntityControllerInterface()
{
    using namespace boost::python;
    class_<EntityController, boost::noncopyable, boost::shared_ptr<EntityController> >("EntityController", no_init)
        .def("set_entity", &EntityController::setEntity)
    ;
}
