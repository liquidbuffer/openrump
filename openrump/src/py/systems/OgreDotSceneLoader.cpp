// ----------------------------------------------------------------------------
// OgreDotSceneLoaderInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/OgreDotSceneLoader.hpp>
#include <openrump/py/ontology/SystemWrapper.hpp>

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(OgreDotSceneLoaderAddSceneOverloads, addScene, 2, 3)

void exportPyOgreDotSceneLoader()
{
    using namespace boost::python;
    
    class_<OpenRump::OgreDotSceneLoader, boost::noncopyable/*, bases<Ontology::System>*/ >("OgreDotSceneLoader", no_init)
        .def("add_scene", &OpenRump::OgreDotSceneLoader::addScene, OgreDotSceneLoaderAddSceneOverloads())
        ;
    class_<OpenRump::OgreDotSceneLoader::Settings>("OgreDotSceneLoaderSettings")
        .def_readwrite("load_cameras", &OpenRump::OgreDotSceneLoader::Settings::loadCameras)
        .def_readwrite("load_lights", &OpenRump::OgreDotSceneLoader::Settings::loadLights)
        .def_readwrite("load_entities", &OpenRump::OgreDotSceneLoader::Settings::loadEntities)
        .def_readwrite("load_external_resources", &OpenRump::OgreDotSceneLoader::Settings::loadExternalResources)
        .def_readwrite("exclude_nodes", &OpenRump::OgreDotSceneLoader::Settings::excludeNodes)
        ;
}
