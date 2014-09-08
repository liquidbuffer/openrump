// ----------------------------------------------------------------------------
// PyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings

// ----------------------------------------------------------------------------
// foward declarations

void exportEntityPlayerInterface();
void exportGameInterface();

BOOST_PYTHON_MODULE(open_rump)
{
    /*exportGameInterface();
    exportEntityPlayerInterface();*/
};
