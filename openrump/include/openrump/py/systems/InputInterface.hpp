// ----------------------------------------------------------------------------
// InputInterfaceWrapper.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/InputInterface.hpp>

struct InputInterfaceWrapper : OpenRump::InputInterface, boost::python::wrapper<OpenRump::InputInterface>
{
    void initialise() override;
    void processEntity(Ontology::Entity&) override;
    void configureEntity(Ontology::Entity&, std::string) override;
    void attachToWindow(std::size_t) override;
    void detachFromWindow() override;
    void setWindowExtents(unsigned int, unsigned int) override;
    void capture() override;
};