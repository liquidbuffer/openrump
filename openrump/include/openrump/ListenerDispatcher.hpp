// ----------------------------------------------------------------------------
// ListenerDispatcher.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>

#include <map>
#include <string>

namespace OpenRump {

template <class LISTENER_CLASS>
class OPENRUMP_API ListenerDispatcher
{
public:

    /*!
     * @brief Default constructor
     */
    ListenerDispatcher();

    /*!
     * @brief Default destructor
     */
    ~ListenerDispatcher();

    /*!
     * @brief Registers a listener to be notified on events
     */
    void addListener(LISTENER_CLASS* listener, std::string listenerName);

    /*!
     * @brief Unregisters a listener by pointer
     * @param listener A pointer to a listener to unregister
     */
    void removeListener(LISTENER_CLASS* listener);

    /*!
     * @brief Unregisters a listener by name
     * @param listenerName A unique string identifying the listener.
     */
    void removeListener(std::string listenerName);

    /*!
     * @brief Removes all listeners
     */
    void removeAllListeners();

    /*!
     * @brief Dispatches a message to all listeners
     * @param func A pointer to a member function of the listener class.
     * For example:
     * @code &Listener::doThing @endcode
     * @param params Parameter list of values to be dispatched to the
     * listeners.
     */
    template <class RET_TYPE, class... PARAMS>
    void dispatch(RET_TYPE (LISTENER_CLASS::*func)(PARAMS...), PARAMS... params) const;

    /*!
     * @brief Dispatches a message to all listeners
     * If any of the listeners return false, then this method will return false.
     * If all listeners return true, then this method will return true.
     * @note As soon as a listener returns false, this method will return. All
     * listeners that would have been notified afterwards are skipped.
     * @param func A pointer to a member function of the listener class.
     * For example:
     * @code &Listener::doThing @endcode
     * @param params Parameter list of values to be dispatched to the
     * listeners.
     */
    template <class... PARAMS>
    bool dispatchAndFindFalse(bool (LISTENER_CLASS::*func)(PARAMS...), PARAMS... params) const;

private:

    std::map<std::string, LISTENER_CLASS*> m_Listeners;
};

} // namespace OpenRump
