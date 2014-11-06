// ----------------------------------------------------------------------------
// ThirdPersonControllerInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/ThirdPersonController.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

void exportPyThirdPersonController()
{
    using namespace boost::python;
}
