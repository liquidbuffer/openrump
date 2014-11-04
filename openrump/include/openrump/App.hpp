// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Game;
}

namespace OpenRump {

class OPENRUMP_API App
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
    
    /*!
     * @brief Script to execute.
     */
    void setScript(char* scriptFile);
    
    /*!
     * @brief Launc the app.
     */
    void go();

private:

    /*!
     * @brief Called when the application should load
     */
    void onLoad();

    /*!
     * @brief Called when the application should run
     */
    void onRun();

    /*!
     * @brief Called when the application is exiting
     */
    void onExit();

    const char* m_PyWorkingDirectory;
    const char* m_PySysPath;
    char* m_ScriptFile;
    std::unique_ptr<Game> m_Game;
};

} // OpenRump
