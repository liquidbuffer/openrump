// ----------------------------------------------------------------------------
// LoopTimerInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/LoopTimer.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

void exportPyLoopTimer()
{
    using namespace boost::python;
    
    class_<OpenRump::LoopTimer, boost::noncopyable/*, bases<Ontology::System>*/ >("LoopTimer", no_init)
        .def("reset", &OpenRump::LoopTimer::reset)
        .def("get_elapsed_time", &OpenRump::LoopTimer::getElapsedTime)
        .def("set_fps", &OpenRump::LoopTimer::setFPS)
        .def("get_time_between_frames", &OpenRump::LoopTimer::getTimeBetweenFrames)
        .def("get_render_fps", &OpenRump::LoopTimer::getRenderFPS)
        .def("get_update_fps", &OpenRump::LoopTimer::getUpdateFPS)
        .def_readonly("on_render_loop", &OpenRump::LoopTimer::on_render_loop)
        .def_readonly("on_game_loop", &OpenRump::LoopTimer::on_game_loop)
        ;
}
