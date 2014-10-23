// ----------------------------------------------------------------------------
// Exception.hpp
// ----------------------------------------------------------------------------

#ifndef __OPENRUMP_EXCEPTION_HPP__
#define __OPENRUMP_EXCEPTION_HPP__

// ----------------------------------------------------------------------------
// include files

#include <stdexcept>

namespace OpenRump {

class Exception : public std::runtime_error
{
public:
    Exception(const std::string& msg);
};

#define DECLARE_EXCEPTION(name) \
struct name : public Exception \
{ \
    name(const std::string& msg) : Exception(msg) {} \
};



#   define STRINGIFY(x) #x
#   define TO_STRING(x) STRINGIFY(x)
#   define AT __FILE__ ":" TO_STRING(__LINE__)
#   define ASSERT(should_be_true, except_type, class_method, message) \
        if(! (should_be_true)) \
            throw except_type(std::string(AT) + " [" + TO_STRING(class_method) + "] Error: " + message);

} // namespace OpenRump

#endif // __OPENRUMP_EXCEPTION_HPP__