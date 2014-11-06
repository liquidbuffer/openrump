// ----------------------------------------------------------------------------
// PyOntologySystemWrapper.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <ontology/System.hpp>
#include <ontology/Entity.hpp>

struct SystemWrapper : public Ontology::System, boost::python::wrapper<Ontology::System>
{
    void initialise();
    void processEntity(Ontology::Entity&);
    void configureEntity(Ontology::Entity&, std::string);
};