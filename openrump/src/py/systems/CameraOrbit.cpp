// ----------------------------------------------------------------------------
// CameraOrbitInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/CameraOrbit.hpp>
#include <ontology/System.hpp>

void exportPyCameraOrbit()
{
    using namespace boost::python;

    class_<OpenRump::CameraOrbit/*, bases<Ontology::System>*/ >("CameraOrbit")
        .def("on_new_camera_angle", &OpenRump::CameraOrbit::onNewCameraAngle)
        .def("on_new_camera_distance", &OpenRump::CameraOrbit::onNewCameraDistance)
        ;
}
