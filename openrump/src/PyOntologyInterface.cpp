// ----------------------------------------------------------------------------
// PyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <ontology/Ontology.hpp>
#include <ontology/Entity.hpp>

#include <openrump/components/OgreCamera.hpp>

using namespace Ontology;
using namespace boost::python;

struct SystemWrapper : System, wrapper<System>
{
    void initialise()               {}
    void processEntity(Entity&)     {}
};

void exportOntologyInterface()
{
    class_<World, boost::noncopyable>("World")
        .def("get_system_manager", &World::getSystemManager,
             return_value_policy<
                reference_existing_object>())
        .def("get_entity_manager", &World::getEntityManager,
             return_value_policy<
                reference_existing_object>())
        .def("get_delta_time", &World::getDeltaTime)
        .def("set_delta_time", &World::setDeltaTime)
        .def("update", &World::update)
        ;
    class_<SystemManager, boost::noncopyable>("SystemManager", no_init)
        ;
    class_<EntityManager, boost::noncopyable>("EntityManager", no_init)
        ;
    class_<SystemWrapper, boost::noncopyable>("System")
        .def("initialise", pure_virtual(&System::initialise))
        .def("process_entity", pure_virtual(&System::processEntity))
        ;
    class_<Entity, boost::noncopyable>("Entity", no_init)
        /*.def("add_component_camera", &Entity::addComponent<OpenRump::OgreCamera>,
             return_value_policy<
                reference_existing_object>())*/
        .def("remove_component_camera", &Entity::removeComponent<OpenRump::OgreCamera>)
        /*.def("get_component_camera", &Entity::getComponent<OpenRump::OgreCamera>,
             return_value_policy<
                reference_existing_object>())*/
        ;
}
