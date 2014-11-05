// ----------------------------------------------------------------------------
// InputInterfaceWrapper.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings
#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/systems/InputInterface.hpp>

using namespace Ontology;
using namespace OpenRump;
using namespace boost::python;

struct InputInterfaceWrapper : InputInterface, wrapper<InputInterface>
{
    void initialise() override;
    void processEntity(Entity&) override;
    void configureEntity(Entity&, std::string) override;
    void attachToWindow(std::size_t) override;
    void detachFromWindow() override;
    void setWindowExtents(unsigned int, unsigned int) override;
    void capture() override;
};