// ----------------------------------------------------------------------------
// LoopTimerInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/LoopTimer.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

using namespace OpenRump;
using namespace boost::python;

void exportPyLoopTimer()
{
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
}
