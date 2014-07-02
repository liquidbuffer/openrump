// ----------------------------------------------------------------------------
// PyCallbackDispatcher.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/PyCallbackDispatcher.hpp>

#include <stdexcept>
#include <string>

namespace OpenRump {

// ----------------------------------------------------------------------------
PyCallbackDispatcher::PyCallbackDispatcher() :
    m_Name("noname")
{
}

// ----------------------------------------------------------------------------
PyCallbackDispatcher::PyCallbackDispatcher(const char* dispatcherName) :
    PyCallbackDispatcher()
{
    m_Name = dispatcherName;
}

// ----------------------------------------------------------------------------
PyCallbackDispatcher::~PyCallbackDispatcher()
{
    this->removeAllCallbacks();
}

// ----------------------------------------------------------------------------
void PyCallbackDispatcher::addCallback(boost::python::object callable)
{
    for(auto it : m_CallbackList)
        if(it == callable)
            this->error("addCallback", "callback already registered");
    m_CallbackList.push_back(callable);
}

// ----------------------------------------------------------------------------
void PyCallbackDispatcher::removeCallback(boost::python::object callable)
{
    for(auto it = m_CallbackList.begin(); it != m_CallbackList.end(); ++it)
        if(*it == callable)
        {
            m_CallbackList.erase(it);
            return;
        }
    this->error("removeCallback", "callback not registered");
}

// ----------------------------------------------------------------------------
void PyCallbackDispatcher::removeAllCallbacks()
{
    m_CallbackList.clear();
}

// ----------------------------------------------------------------------------
void PyCallbackDispatcher::error(const char* method, const char* message)
{
    throw std::runtime_error(std::string("[PyCallbackDispatcher(") + m_Name
            + ")::" + method + "] Error: " + message);
}

}
