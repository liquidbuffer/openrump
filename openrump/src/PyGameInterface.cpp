// ----------------------------------------------------------------------------
// PyGameInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/Game.hpp>
#include <ontology/Entity.hpp>

using namespace OpenRump;
/*
// ----------------------------------------------------------------------------
// overloads
/*
void (Game::*attachCameraToEntity_entityName)(std::string)                          = &Game::attachCameraToEntity;
void (Game::*attachCameraToEntity_cameraName_entityName)(std::string, std::string)  = &Game::attachCameraToEntity;*/

void exportGameInterface()
{
    using namespace boost::python;
    class_<Game, boost::noncopyable>("Game")
        .def("run", &Game::run)
        .def("stop", &Game::stop)
        .def("load_player", &Game::loadPlayer,
            return_value_policy<
                reference_existing_object>())
        .def("create_camera", &Game::createCamera,
             return_value_policy<
                reference_existing_object>())
        .def("attach_camera_to_entity", &Game::attachCameraToEntity)
        .def("add_game_update_callback", &Game::addGameUpdateCallback)
        .def("remove_game_update_callback", &Game::removeGameUpdateCallback)
        .def("remove_all_callbacks", &Game::removeAllCallbacks)
    ;
};
