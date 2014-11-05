// ----------------------------------------------------------------------------
// CameraOrbitInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/CameraOrbit.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

using namespace OpenRump;
using namespace boost::python;

void exportPyCameraOrbit()
{
    class_<CameraOrbit, bases<SystemWrapper> >("CameraOrbit")
        .def("on_new_camera_angle", &CameraOrbit::onNewCameraAngle)
        .def("on_new_camera_distance", &CameraOrbit::onNewCameraDistance)
        ;
}
