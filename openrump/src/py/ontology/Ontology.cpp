// ----------------------------------------------------------------------------
// PyOntologyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <ontology/Ontology.hpp>

#include <openrump/py/ontology/SystemWrapper.hpp>
#include <openrump/py/ontology/EntityManagerWrapper.hpp>

#include <openrump/systems/CameraOrbit.hpp>
#include <openrump/systems/DefaultPhysicsWorld.hpp>
#include <openrump/systems/InputInterface.hpp>
#include <openrump/systems/LoopTimer.hpp>
#include <openrump/systems/OgreDotSceneLoader.hpp>
#include <openrump/systems/OgreRenderer.hpp>
#include <openrump/systems/ThirdPersonController.hpp>

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(EntityManagerCreateEntityOverloads, createEntityWrapper, 0, 1)

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

// generates add, remove, and get python methods for the specified component
#define DEF_COMPONENT(pystr, component) \
    .def("get_"    TO_STRING(pystr), &Entity::getComponent<component>, \
        return_value_policy< \
            reference_existing_object>()) \
    .def("remove_" TO_STRING(pystr), &Entity::removeComponent<component>) \
    .def("add_"    TO_STRING(pystr), &Entity::addComponent<component>, \
        return_value_policy< \
            reference_existing_object>())

// generates get python methods for the specified system
#define DEF_GET_SYSTEM(pystr, system) \
    .def("get_" pystr, &Ontology::SystemManager::getSystem<system>, \
        return_value_policy< \
            reference_existing_object>())

// declares the python class for the specified component
#define CLASS_COMPONENT(component) \
    class_<component, bases<Component> >(TO_STRING(component), no_init);

void exportPyOntology()
{
    using namespace OpenRump;
    using namespace boost::python;
    
    // ----------------------------------------------------------------------------
    // ontology world
    class_<Ontology::World, boost::noncopyable>("World")
        .def("get_system_manager", &Ontology::World::getSystemManager,
             return_value_policy<
                reference_existing_object>())
        .def("get_entity_manager", &Ontology::World::getEntityManager,
             return_value_policy<
                reference_existing_object>())
        .def("get_delta_time", &Ontology::World::getDeltaTime)
        .def("set_delta_time", &Ontology::World::setDeltaTime)
        .def("update", &Ontology::World::update)
        ;
    
    // ----------------------------------------------------------------------------
    // system manager
    class_<Ontology::SystemManager, boost::noncopyable>("SystemManager", no_init)
        DEF_GET_SYSTEM("camera_orbit", CameraOrbit)
        DEF_GET_SYSTEM("default_physics_world", DefaultPhysicsWorld)
        DEF_GET_SYSTEM("input_interface", InputInterface)
        DEF_GET_SYSTEM("loop_timer", LoopTimer)
        DEF_GET_SYSTEM("ogre_dot_scene_loader", OgreDotSceneLoader)
        DEF_GET_SYSTEM("ogre_renderer", OgreRenderer)
        DEF_GET_SYSTEM("third_person_controller", ThirdPersonController)
        ;
    
    // ----------------------------------------------------------------------------
    // entity manager
    class_<EntityManagerWrapper, boost::noncopyable>("EntityManager", no_init)
        .def("create_entity", &EntityManagerWrapper::createEntityWrapper, EntityManagerCreateEntityOverloads())
        .def("destroy_entity", &EntityManagerWrapper::destroyEntity)
        .def("destroy_entities", &EntityManagerWrapper::destroyEntities)
        .def("destroy_all_entities", &EntityManagerWrapper::destroyAllEntities)
        ;
    
    // ----------------------------------------------------------------------------
    // system base class
    class_<SystemWrapper, boost::noncopyable>("System")
        .def("initialise", pure_virtual(&Ontology::System::initialise))
        .def("process_entity", pure_virtual(&Ontology::System::processEntity))
        .def("configure_entity", pure_virtual(&Ontology::System::configureEntity))
        ;

    /* not wrapping entities - at least not yet. They should be hidden from the end user.
     * the only thing that the user should be able to access is the entity ID.
    // ----------------------------------------------------------------------------
    // entities
    class_<Entity, boost::noncopyable>("Entity", no_init)
        DEF_COMPONENT("direction2d", Direction2D)
        DEF_COMPONENT("speed", Speed)
        ;

    // ----------------------------------------------------------------------------
    // component base class and components
    // need to wrap available components manually since there is no easy way to do it dynamically
    class_<Component>("Component", no_init);
    CLASS_COMPONENT(Direction2D);
    CLASS_COMPONENT(Speed);*/
}
