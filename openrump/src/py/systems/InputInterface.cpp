// ----------------------------------------------------------------------------
// InputInterfaceInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/py/systems/InputInterface.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

using namespace OpenRump;
using namespace boost::python;

void exportPyInputInterface()
{
    class_<InputInterfaceWrapper, boost::noncopyable, bases<SystemWrapper> >("Input")
        .def("attach_to_window", pure_virtual(&InputInterface::attachToWindow))
        .def("detach_from_window", pure_virtual(&InputInterface::detachFromWindow))
        .def("set_window_extents", pure_virtual(&InputInterface::setWindowExtents))
        .def("capture", pure_virtual(&InputInterface::capture))
        .def_readonly("on_exit", &InputInterface::on_exit)
        .def_readonly("on_direction_change", &InputInterface::on_direction_change)
        .def_readonly("on_camera_angle_change", &InputInterface::on_camera_angle_change)
        .def_readonly("on_camera_distance_change", &InputInterface::on_camera_distance_change)
        ;
}

void InputInterfaceWrapper::initialise() {}
void InputInterfaceWrapper::processEntity(Entity&) {}
void InputInterfaceWrapper::configureEntity(Entity&, std::string) {}
void InputInterfaceWrapper::attachToWindow(std::size_t) {}
void InputInterfaceWrapper::detachFromWindow() {}
void InputInterfaceWrapper::setWindowExtents(unsigned int, unsigned int) {}
void InputInterfaceWrapper::capture() {}
