// ----------------------------------------------------------------------------
// PyEntityPlayerInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/EntityPlayer.hpp>
#include <openrump/Input.hpp>
#include <openrump/OgreRenderSystem.hpp>

using namespace OpenRump;
class OISInput;

void exportEntityPlayerInterface()
{
    using namespace boost::python;/*
    class_<EntityPlayer, boost::noncopyable>("EntityPlayer", no_init)
        .def("set_camera_distance", &EntityPlayer::setCameraDistance)*/
    ;
}
