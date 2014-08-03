// ----------------------------------------------------------------------------
// PyInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python.hpp>  // must be included before std to avoid warnings

// ----------------------------------------------------------------------------
// foward declarations

void exportGameInterface();
void exportEntityBaseInterface();
void exportEntityPlayerInterface();
void exportEntityControllerInterface();
void exportEntityControllerCameraOrbitInterface();

BOOST_PYTHON_MODULE(open_rump)
{
    exportGameInterface();
    exportEntityBaseInterface();
    exportEntityPlayerInterface();
    exportEntityControllerInterface();
    exportEntityControllerCameraOrbitInterface();
};
