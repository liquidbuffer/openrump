// ----------------------------------------------------------------------------
// ListenerDispatcher.hxx
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/ListenerDispatcher.hpp>
#include <openrump/RendererListener.hpp>

#ifdef _DEBUG
#   include <iostream>
#endif // _DEBUG

namespace OpenRump {

// ----------------------------------------------------------------------------
template <class T>
ListenerDispatcher<T>::ListenerDispatcher()
{
}

// ----------------------------------------------------------------------------
template <class T>
ListenerDispatcher<T>::~ListenerDispatcher()
{
}

// ----------------------------------------------------------------------------
template <class T>
void ListenerDispatcher<T>::addListener(const T listener, std::string listenerName)
{
#ifdef _DEBUG
    if(m_Listeners.find(listenerName) != m_Listeners.end())
    {
        std::cout << "[ListenerDispatcher::addListener] Warning: listenerName \""
                   << listenerName << "\" already registered" << std::endl;
        return;
    }
    for(iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
    {
        if(it->second == listener)
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
template <class T>
void ListenerDispatcher<T>::removeListener(const T listener)
{
    for(iterator it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
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
template <class T>
void ListenerDispatcher<T>::removeListener(std::string listenerName)
{
    iterator it = m_Listeners.find(listenerName);
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
template <class T>
typename ListenerDispatcher<T>::iterator ListenerDispatcher<T>::begin()
{
    return m_Listeners.begin();
}

// ----------------------------------------------------------------------------
template <class T>
typename ListenerDispatcher<T>::iterator ListenerDispatcher<T>::end()
{
    return m_Listeners.end();
}

} // namespace OpenRump
