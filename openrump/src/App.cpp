// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <python2.7/Python.h>  // must be included before boost.python to avoid warnings

#include <boost/python.hpp>  // must be included before std to avoid warnings

#include <openrump/App.hpp>
#include <openrump/systems/OgreRenderer.hpp>
#include <openrump/Game.hpp>
#include <openrump/PyInterface.hpp>

#include <iostream>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App(const char* workingDirectory) :
    m_PyWorkingDirectory(workingDirectory),
#ifdef _DEBUG
    m_PySysPath("../../py"),
#else
    m_PySysPath("py"),
#endif
    m_ScriptFile(nullptr)
{
}

// ----------------------------------------------------------------------------
App::~App()
{
}

// ----------------------------------------------------------------------------
void App::setScript(char* scriptFile)
{
    m_ScriptFile = scriptFile;
}

// ----------------------------------------------------------------------------
void App::go()
{
    this->onLoad();
    this->onRun();
    this->onExit();
}

// ----------------------------------------------------------------------------
void App::onLoad()
{
    std::cout << "OpenRump starting..." << std::endl;
    
    // important for when python needs to load modules
    Py_SetProgramName(const_cast<char*>(m_PyWorkingDirectory));
    Py_Initialize();
    PySys_SetPath(const_cast<char*>(m_PySysPath));
}

// ----------------------------------------------------------------------------
void App::onRun()
{
    using namespace boost::python;
    try
    {
        initopen_rump();
        initontology();
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");
        object ignored = exec_file(m_ScriptFile, main_namespace);
    } catch(const error_already_set&)
    {
        PyErr_Print();
    }
}

// ----------------------------------------------------------------------------
void App::onExit()
{
    std::cout << "OpenRump quitting..." << std::endl;
    Py_Finalize();
}

} // namespace OpenRump
