// ----------------------------------------------------------------------------
// PyCallbackDispatcher.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <boost/python/object.hpp>

#include <vector>

namespace OpenRump {

class PyCallbackDispatcher
{
public:

    PyCallbackDispatcher();
    PyCallbackDispatcher(const char* dispatcherName);
    ~PyCallbackDispatcher();

    void addCallback(boost::python::object callable);
    void removeCallback(boost::python::object callable);
    void removeAllCallbacks();

    template <class... PARAMS>
    void dispatch(PARAMS&&... params)
    {
        for(auto it : m_CallbackList)
            it(params...);
    }

    template <class... PARAMS>
    bool dispatchAndFindFalse(PARAMS&&... params)
    {
        for(auto it : m_CallbackList)
            if(!it(params...))
                return false;
        return true;
    }

private:
    inline void error(const char* method, const char* message);
    const char* m_Name;
    std::vector<boost::python::object> m_CallbackList;
};

}
