// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/App.hpp>
#include <openrump/OgreRenderer.hpp>
#include <openrump/Game.hpp>
#include <openrump/PyGameInterface.hpp>

#include <iostream>

#include <python2.7/Python.h>
#include <boost/python.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
App::App(std::string workingDirectory) :
    m_WorkingDirectory(workingDirectory),
    m_PyWorkingDirectory(new char[workingDirectory.size()+1])
{

    // python requires a writable char* of the working directory
    std::copy(workingDirectory.begin(),
              workingDirectory.end(),
              m_PyWorkingDirectory.get()
    );
    m_PyWorkingDirectory[workingDirectory.size()] = '\0';

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
    //m_Game = std::unique_ptr<Game>(new Game);
}

// ----------------------------------------------------------------------------
void App::onRun()
{
    //m_Game->run();
    using namespace boost::python;
    try
    {
        initopen_rump();
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");
        object ignored = exec("import open_rump\ngame = open_rump.Game()\ngame.run()\n", main_namespace);
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
