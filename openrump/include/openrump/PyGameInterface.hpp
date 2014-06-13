// ----------------------------------------------------------------------------
// PyGameInterface.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <string>
#include <memory>

namespace OpenRump {

class PyGameInterface
{
public:

    PyGameInterface(std::string workingDirectory);
    ~PyGameInterface();
private:
    std::unique_ptr<char[]> m_WorkingDirectory;
};

} // namespace OpenRump
