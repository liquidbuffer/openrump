// ----------------------------------------------------------------------------
// ListenerDispatcher.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <map>
#include <string>

namespace OpenRump {

template <class T>
class ListenerDispatcher
{
public:

    typedef typename std::map<std::string, T>::iterator iterator;

    /*!
     * @brief Default constructor
     */
    ListenerDispatcher();

    /*!
     * @brief Default destructor
     */
    ~ListenerDispatcher();

    /*!
     * @brief Registers a listener
     */
    void addListener(const T listener, std::string listenerName);

    /*!
     * @brief Unregisters a listener by pointer
     */
    void removeListener(const T listener);

    /*!
     * @brief Unregisters a listener by name
     * @brief listenerName A unique string identifying the listener.
     */
    void removeListener(std::string listenerName);

    /*!
     * @brief Removes all listeners
     */
    void removeAllListeners();

    iterator begin();
    iterator end();

private:

    std::map<std::string, T> m_Listeners;
};

} // namespace OpenRump
