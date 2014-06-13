// ----------------------------------------------------------------------------
// PyGameInterface.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/PyGameInterface.hpp>

#include <python2.7/Python.h>

namespace OpenRump {

// ----------------------------------------------------------------------------
PyGameInterface::PyGameInterface(std::string workingDirectory) :
    m_WorkingDirectory(new char[workingDirectory.size()+1])
{
    // python requires a writable char* of the working directory
    std::copy(workingDirectory.begin(), workingDirectory.end(), m_WorkingDirectory.get());
    m_WorkingDirectory[workingDirectory.size()] = '\0';

    Py_SetProgramName(m_WorkingDirectory.get());
    Py_Initialize();
    PyRun_SimpleString("print 'hello world'");
}

// ----------------------------------------------------------------------------
PyGameInterface::~PyGameInterface()
{
    Py_Finalize();
}

} // namespace OpenRump
