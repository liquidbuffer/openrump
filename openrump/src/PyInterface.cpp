// ----------------------------------------------------------------------------
// PyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

// ----------------------------------------------------------------------------
// foward declarations

//void exportEntityPlayerInterface();
void exportGameInterface();

BOOST_PYTHON_MODULE(open_rump)
{
    exportGameInterface();
    /*exportEntityPlayerInterface();*/
};
