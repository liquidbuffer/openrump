// ----------------------------------------------------------------------------
// InputInterfaceInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/py/systems/InputInterface.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

void exportPyInputInterface()
{
    using namespace boost::python;
    
    class_<InputInterfaceWrapper, boost::noncopyable/*, bases<Ontology::System>*/ >("Input")
        .def("attach_to_window", pure_virtual(&OpenRump::InputInterface::attachToWindow))
        .def("detach_from_window", pure_virtual(&OpenRump::InputInterface::detachFromWindow))
        .def("set_window_extents", pure_virtual(&OpenRump::InputInterface::setWindowExtents))
        .def("capture", pure_virtual(&OpenRump::InputInterface::capture))
        .def_readonly("on_exit", &OpenRump::InputInterface::on_exit)
        .def_readonly("on_direction_change", &OpenRump::InputInterface::on_direction_change)
        .def_readonly("on_camera_angle_change", &OpenRump::InputInterface::on_camera_angle_change)
        .def_readonly("on_camera_distance_change", &OpenRump::InputInterface::on_camera_distance_change)
        ;
}

void InputInterfaceWrapper::initialise() {}
void InputInterfaceWrapper::processEntity(Ontology::Entity&) {}
void InputInterfaceWrapper::configureEntity(Ontology::Entity&, std::string) {}
void InputInterfaceWrapper::attachToWindow(std::size_t) {}
void InputInterfaceWrapper::detachFromWindow() {}
void InputInterfaceWrapper::setWindowExtents(unsigned int, unsigned int) {}
void InputInterfaceWrapper::capture() {}
