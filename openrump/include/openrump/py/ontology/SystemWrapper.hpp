// ----------------------------------------------------------------------------
// PyOntologySystemWrapper.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <ontology/System.hpp>
#include <ontology/Entity.hpp>

using namespace Ontology;
using namespace boost::python;

struct SystemWrapper : public System, wrapper<System>
{
    void initialise();
    void processEntity(Entity&);
    void configureEntity(Entity&, std::string);
};