// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/Export.hpp>
#include <openrump/BaseApp.hpp>
#include <openrump/InputListener.hpp>
#include <openrump/RendererFrameListener.hpp>

#include <memory>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class PyGameInterface;
}

namespace OpenRump {

class OPENRUMP_API App :
    public BaseApp,
    public InputListener,
    public RendererFrameListener
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
    virtual void onLoad();

    /*!
     * @brief Called when the application should run
     */
    virtual void onRun();

    /*!
     * @brief Called when the application is exiting
     */
    virtual void onExit();

    std::string m_WorkingDirectory;

    std::unique_ptr<PyGameInterface> m_GameInterface;
};

} // OpenRump
