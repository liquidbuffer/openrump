// ----------------------------------------------------------------------------
// ListenerDispatcher.hxx
// ----------------------------------------------------------------------------

#ifndef __OPENRUMP_LISTENER_DISPATCHER__
#define __OPENRUMP_LISTENER_DISPATCHER__

// ----------------------------------------------------------------------------
// include files

#include <openrump/ListenerDispatcher.hpp>
#include <openrump/RendererListener.hpp>

#ifdef _DEBUG
#   include <iostream>
#endif // _DEBUG

namespace OpenRump {

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
ListenerDispatcher<LISTENER_CLASS>::ListenerDispatcher()
{
}

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
ListenerDispatcher<LISTENER_CLASS>::~ListenerDispatcher()
{
}

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
void ListenerDispatcher<LISTENER_CLASS>::addListener(LISTENER_CLASS* listener, std::string listenerName)
{
#ifdef _DEBUG
    if(m_Listeners.find(listenerName) != m_Listeners.end())
    {
        std::cout << "[ListenerDispatcher::addListener] Warning: listenerName \""
                   << listenerName << "\" already registered" << std::endl;
        return;
    }
    for(auto it : m_Listeners)
    {
        if(it.second == listener)
        {
            std::cout << "[ListenerDispatcher::addListener] Warning: listener pointer already registered"
                       << std::endl;
            return;
        }
    }
#endif // _DEBUG

    m_Listeners[listenerName] = listener;
}

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
void ListenerDispatcher<LISTENER_CLASS>::removeListener(LISTENER_CLASS* listener)
{
    for(auto it = std::begin(m_Listeners); it != std::end(m_Listeners); ++it)
    {
        if(it->second == listener)
        {
            m_Listeners.erase(it);
            return;
        }
    }
#ifdef _DEBUG
    std::cout << "[ListenerDispatcher::removeListener] Warning: listener pointer not registered" << std::endl;
#endif // _DEBUG
}

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
void ListenerDispatcher<LISTENER_CLASS>::removeListener(std::string listenerName)
{
    auto it = m_Listeners.find(listenerName);
    if(it == m_Listeners.end())
    {
#ifdef _DEBUG
        std::cout << "[ListenerDispatcher::removeListener] Warning: listener \"" << listenerName
                   << "\" not registered" << std::endl;
#endif // _DEBUG
        return;
    }
    m_Listeners.erase(it);
}

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
void ListenerDispatcher<LISTENER_CLASS>::removeAllListeners()
{
    m_Listeners.clear();
}

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
template <class RET_TYPE, class... ARGS, class... PARAMS>
void ListenerDispatcher<LISTENER_CLASS>::
    dispatch(RET_TYPE (LISTENER_CLASS::*func)(ARGS...), PARAMS&&... params) const
{
    for(auto it : m_Listeners)
        (it.second->*func)(params...);
}

// ----------------------------------------------------------------------------
template <class LISTENER_CLASS>
template <class... ARGS, class... PARAMS>
bool ListenerDispatcher<LISTENER_CLASS>::
    dispatchAndFindFalse(bool (LISTENER_CLASS::*func)(ARGS...), PARAMS&&... params) const
{
    for(auto it : m_Listeners)
        if(!(it.second->*func)(params...))
            return false;
    return true;
}

} // namespace OpenRump

#endif // __OPENRUMP_LISTENER_DISPATCHER__
