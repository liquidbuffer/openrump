// ----------------------------------------------------------------------------
// PyGameInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Game.hpp>
#include <openrump/PyGameInterface.hpp>

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(open_rump)
{
    using namespace boost::python;
    class_<OpenRump::Game, boost::noncopyable>("Game")
        .def("test", &OpenRump::Game::test)
        .def("run", &OpenRump::Game::run)
    ;
}
