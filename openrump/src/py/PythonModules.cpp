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

class OntologyNamespace {};
class GameNamespace {};

BOOST_PYTHON_MODULE(_open_rump)
{
    using namespace boost::python;
    
    {
        scope Ontology = class_<OntologyNamespace>("Ontology");
        exportPyOntology();
    }
    
    {
        scope Game = class_<GameNamespace>("Game");
        exportPyGame();
        exportPyCameraOrbit();
        exportPyDefaultPhysicsWorld();
        exportPyInputInterface();
        exportPyLoopTimer();
        exportPyOgreDotSceneLoader();
        exportPyOgreRenderer();
        exportPyThirdPersonController();
    }
}
