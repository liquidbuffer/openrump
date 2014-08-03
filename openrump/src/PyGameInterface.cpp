// ----------------------------------------------------------------------------
// PyGameInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/Game.hpp>
#include <openrump/EntityBase.hpp>
#include <openrump/EntityController.hpp>

using namespace OpenRump;

// ----------------------------------------------------------------------------
// overloads

void (Game::*destroyEntity_name)(std::string) = &Game::destroyEntity;
void (Game::*destroyEntity_pointer)(EntityBase*) = &Game::destroyEntity;

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(createEntityControllerCameraOrbit_overloads, createEntityControllerCameraOrbit, 0, 1);

void exportGameInterface()
{
    using namespace boost::python;
    class_<Game, boost::noncopyable>("Game")
        .def("run", &Game::run)
        .def("stop", &Game::stop)
        .def("create_entity_player", &Game::createEntityPlayer,
            return_value_policy<
                reference_existing_object>())
        .def("destroy_entity", destroyEntity_name)
        .def("destroy_entity", destroyEntity_pointer)
        .def("create_entity_controller_camera_orbit", &Game::createEntityControllerCameraOrbit, createEntityControllerCameraOrbit_overloads())
        .def("create_camera", &Game::createCamera)
        .def("destroy_camera", &Game::destroyCamera)
        .def("add_game_update_callback", &Game::addGameUpdateCallback)
        .def("remove_game_update_callback", &Game::removeGameUpdateCallback)
        .def("remove_all_callbacks", &Game::removeAllCallbacks)
    ;
};
