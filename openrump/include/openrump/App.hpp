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
    App(const char* workingDirectory);

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

    const char* m_PyWorkingDirectory;
    const char* m_PySysPath;
    std::unique_ptr<Game> m_Game;
};

} // OpenRump
