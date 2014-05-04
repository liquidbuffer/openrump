// ----------------------------------------------------------------------------
// BaseApp.hpp
// ----------------------------------------------------------------------------

#include <openrump/Export.hpp>

namespace OpenRump {

class OPENRUMP_API BaseApp
{
public:

    /*!
     * @brief Default constructor
     */
    BaseApp();

    /*!
     * @brief Default destructor
     */
    virtual ~BaseApp();

    /*!
     * @brief Launches the application
     */
    void go();

protected:

    /*!
     * @brief Called when the application should load
     */
    virtual bool onLoad() = 0;

    /*!
     * @brief Called when the application should run
     */
    virtual void onRun() = 0;

    /*!
     * @brief Called when the application is exiting
     */
    virtual void onExit() = 0;
};

} // OpenRump
