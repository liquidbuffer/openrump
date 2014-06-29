// ----------------------------------------------------------------------------
// PyEntityPlayerInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/EntityPlayer.hpp>

using namespace OpenRump;

void exportEntityPlayerInterface()
{
    using namespace boost::python;
    class_<EntityPlayer, boost::noncopyable>("EntityPlayer", no_init)
    ;
}
