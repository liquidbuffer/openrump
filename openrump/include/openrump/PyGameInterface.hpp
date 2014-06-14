// ----------------------------------------------------------------------------
// PyGameInterface.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <string>
#include <memory>

namespace OpenRump {

/*!
 * @brief All exposed components of the game can be controlled here.
 */
class PyGameInterface
{
public:

    /*!
     * @brief Constructor
     * @param workingDirectory Python requires the working directory of the
     * application to be specified.
     */
    PyGameInterface(std::string workingDirectory);

    /*!
     * @brief Allow destruction through base class pointer
     */
    virtual ~PyGameInterface();

    /*!
     * @brief
     */
    virtual void test() = 0;

    /*!
     * @brief Stops the game and cleans up
     */
    virtual void stop() = 0;

    /*!
     * @brief Initialises all components of the game.
     */
    virtual void initialise() = 0;

    /*!
     * @brief Run the game (enter main loop)
     */
    virtual void run() = 0;

    /*!
     * @brief Cleans up everything
     */
    virtual void cleanUp() = 0;

    // python requires a writable char* of the working directory
    std::unique_ptr<char[]> m_WorkingDirectory;
};

} // namespace OpenRump
