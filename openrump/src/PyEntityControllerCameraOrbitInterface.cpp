// ----------------------------------------------------------------------------
// PyEntityControllerCameraOrbitInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/EntityControllerCameraOrbit.hpp>

using namespace OpenRump;

// ----------------------------------------------------------------------------
// overloads

void exportEntityControllerCameraOrbitInterface()
{
    using namespace boost::python;
    class_<EntityControllerCameraOrbit, bases<EntityController>, boost::noncopyable>("EntityControllerCameraOrbit", no_init)
        .def("set_camera", &EntityControllerCameraOrbit::pySetCamera)
        .def("remove_camera", &EntityControllerCameraOrbit::pyRemoveCamera)
        .def("set_distance_constraints", &EntityControllerCameraOrbit::setDistanceConstraints)
        .def("set_distance", &EntityControllerCameraOrbit::setDistance)
        .def("set_rotation", &EntityControllerCameraOrbit::pySetRotation)
    ;
}
