// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings

#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/Game.hpp>
#include <openrump/PyInterface.hpp>

#include <iostream>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App(std::string workingDirectory) :
    m_WorkingDirectory(workingDirectory),
    m_PyWorkingDirectory(new char[workingDirectory.size()+1])
{

    // python requires a writable char* of the working directory
    std::copy(workingDirectory.begin(),
              workingDirectory.end(),
              m_PyWorkingDirectory.get());
    m_PyWorkingDirectory[workingDirectory.size()] = '\0';

    // important for when python needs to load modules
    Py_SetProgramName(m_PyWorkingDirectory.get());
    Py_Initialize();
}

// ----------------------------------------------------------------------------
App::~App()
{
    Py_Finalize();
}

// ----------------------------------------------------------------------------
void App::onLoad()
{
}

// ----------------------------------------------------------------------------
void App::onRun()
{
    using namespace boost::python;
    try
    {
        initopen_rump();
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");
        object ignored = exec_file("../../py/Main.py", main_namespace);
    } catch(const error_already_set&)
    {
        PyErr_Print();
    }
}

// ----------------------------------------------------------------------------
void App::onExit()
{
}

} // namespace OpenRump
