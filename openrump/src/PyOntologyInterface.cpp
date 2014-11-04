// ----------------------------------------------------------------------------
// PyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <ontology/Ontology.hpp>

#include <openrump/systems/CameraOrbit.hpp>
#include <openrump/systems/DefaultPhysicsWorld.hpp>
#include <openrump/systems/InputInterface.hpp>
#include <openrump/systems/LoopTimer.hpp>
#include <openrump/systems/OgreDotSceneLoader.hpp>
#include <openrump/systems/OgreRenderer.hpp>
#include <openrump/systems/ThirdPersonController.hpp>

#include <openrump/components/Direction2D.hpp>
#include <openrump/components/OgreCamera.hpp>
#include <openrump/components/OgreCameraOrbitNode.hpp>
#include <openrump/components/OgreEntity.hpp>
#include <openrump/components/OgreTranslateRotateNode.hpp>
#include <openrump/components/Speed.hpp>

using namespace Ontology;
using namespace OpenRump;
using namespace boost::python;

struct SystemWrapper : System, wrapper<System>
{
    void initialise()                           override {}
    void processEntity(Entity&)                 override {}
    void configureEntity(Entity&, std::string)  override {}
};

struct InputInterfaceWrapper : InputInterface, wrapper<InputInterface>
{
    void initialise()                                   override {}
    void processEntity(Entity&)                         override {}
    void configureEntity(Entity&, std::string)          override {}
    void attachToWindow(std::size_t)                    override {}
    void detachFromWindow()                             override {}
    void setWindowExtents(unsigned int, unsigned int)   override {}
    void capture()                                      override {}
};

struct EntityManagerWrapper : EntityManager, wrapper<System>
{
    // need a version of this function that returns the entity ID rather than an entity reference
    Entity::ID createEntityWrapper(const char* name="")
    {
        return this->createEntity(name).getID();
    }
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(EntityManagerCreateEntityOverloads, createEntityWrapper, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(OgreDotSceneLoaderAddSceneOverloads, addScene, 2, 3)

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
    .def("get_" pystr, &SystemManager::getSystem<system>, \
        return_value_policy< \
            reference_existing_object>())

// declares the python class for the specified component
#define CLASS_COMPONENT(component) \
    class_<component, bases<Component> >(TO_STRING(component), no_init);

void exportOntologyInterface()
{
    // ----------------------------------------------------------------------------
    // ontology world
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
    
    // ----------------------------------------------------------------------------
    // system manager
    class_<SystemManager, boost::noncopyable>("SystemManager", no_init)
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
    class_<EntityManager, boost::noncopyable>("EntityManager", no_init)
        .def("create_entity", &EntityManagerWrapper::createEntityWrapper, EntityManagerCreateEntityOverloads())
        .def("destroy_entity", &EntityManager::destroyEntity)
        .def("destroy_entities", &EntityManager::destroyEntities)
        .def("destroy_all_entities", &EntityManager::destroyAllEntities)
        ;
    
    // ----------------------------------------------------------------------------
    // system base class
    class_<SystemWrapper, boost::noncopyable>("System")
        .def("initialise", pure_virtual(&System::initialise))
        .def("process_entity", pure_virtual(&System::processEntity))
        .def("configure_entity", pure_virtual(&System::configureEntity))
        ;
    
    // ----------------------------------------------------------------------------
    // systems
    class_<CameraOrbit, bases<SystemWrapper> >("CameraOrbit")
        .def("on_new_camera_angle", &CameraOrbit::onNewCameraAngle)
        .def("on_new_camera_distance", &CameraOrbit::onNewCameraDistance)
        ;
    class_<DefaultPhysicsWorld, boost::noncopyable, bases<SystemWrapper> >("DefaultPhysicsWorld", no_init)
        ;
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
    class_<LoopTimer, boost::noncopyable, bases<SystemWrapper> >("LoopTimer", no_init)
        .def("reset", &LoopTimer::reset)
        .def("get_elapsed_time", &LoopTimer::getElapsedTime)
        .def("set_fps", &LoopTimer::setFPS)
        .def("get_time_between_frames", &LoopTimer::getTimeBetweenFrames)
        .def("get_render_fps", &LoopTimer::getRenderFPS)
        .def("get_update_fps", &LoopTimer::getUpdateFPS)
        .def_readonly("on_render_loop", &LoopTimer::on_render_loop)
        .def_readonly("on_game_loop", &LoopTimer::on_game_loop)
        ;
    class_<OgreDotSceneLoader, boost::noncopyable, bases<SystemWrapper> >("OgreDotSceneLoader", no_init)
        .def("add_scene", &OgreDotSceneLoader::addScene, OgreDotSceneLoaderAddSceneOverloads())
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
