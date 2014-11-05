// ----------------------------------------------------------------------------
// PythonModules.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

// ----------------------------------------------------------------------------
// foward declarations

void exportPyOntology();
void exportPyGame();

// systems
void exportPyCameraOrbit();
void exportPyDefaultPhysicsWorld();
void exportPyInputInterface();
void exportPyLoopTimer();
void exportPyOgreDotSceneLoader();
void exportPyOgreRenderer();
void exportPyThirdPersonController();

BOOST_PYTHON_MODULE(ontology)
{
    
}

BOOST_PYTHON_MODULE(open_rump)
{
    exportPyOntology();
    exportPyGame();
    exportPyOgreDotSceneLoader();
    /*exportPyCameraOrbit();
    exportPyDefaultPhysicsWorld();
    exportPyInputInterface();
    exportPyLoopTimer();
    //
    exportPyOgreRenderer();
    exportPyThirdPersonController();*/
}
