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
    ;
}
