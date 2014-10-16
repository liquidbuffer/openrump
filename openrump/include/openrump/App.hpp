// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/BaseApp.hpp>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Game;
}

namespace OpenRump {

class OPENRUMP_API App :
    public BaseApp
{
public:

    /*!
     * @brief constructor
     */
    App(std::string workingDirectory);

    /*!
     * @brief Default destructor
     */
    ~App();

private:

    /*!
     * @brief Called when the application should load
     */
    void onLoad() override;

    /*!
     * @brief Called when the application should run
     */
    void onRun() override;

    /*!
     * @brief Called when the application is exiting
     */
    void onExit() override;

    std::string m_WorkingDirectory;
    std::unique_ptr<char[]> m_PyWorkingDirectory;
    std::unique_ptr<Game> m_Game;
};

} // OpenRump
