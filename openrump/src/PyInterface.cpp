// ----------------------------------------------------------------------------
// PyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#define STRING2(x) #x
#define STRING(x) STRING2(x)
#pragma message "PY_VERSION_HEX = " STRING(PY_VERSION_HEX)

// ----------------------------------------------------------------------------
// foward declarations

//void exportEntityPlayerInterface();
void exportGameInterface();

BOOST_PYTHON_MODULE(open_rump)
{
    exportGameInterface();
    /*exportEntityPlayerInterface();*/
};
