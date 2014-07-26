// ----------------------------------------------------------------------------
// PyEntityPlayerInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings
#include <openrump/EntityPlayer.hpp>

using namespace OpenRump;

// ----------------------------------------------------------------------------
// overloads

void exportEntityPlayerInterface()
{
    using namespace boost::python;
    class_<EntityPlayer, bases<EntityBase>, boost::noncopyable>("EntityPlayer", no_init)
    ;
}