// ----------------------------------------------------------------------------
// PyGameInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/Game.hpp>
#include <openrump/PyGameInterface.hpp>

BOOST_PYTHON_MODULE(open_rump)
{
    using namespace boost::python;

    class_<OpenRump::Game, boost::noncopyable>("Game")
        .def("run", &OpenRump::Game::run)
        .def("stop", &OpenRump::Game::stop)
        .def("load_player", &OpenRump::Game::loadPlayer)
        .def("attach_camera_to_entity", &OpenRump::Game::attachCameraToEntity)
        .def("add_game_update_callback", &OpenRump::Game::addGameUpdateCallback)
        .def("remove_game_update_callback", &OpenRump::Game::removeGameUpdateCallback)
    ;
}
