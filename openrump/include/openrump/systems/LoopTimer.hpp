// ----------------------------------------------------------------------------
// include files

#include <ontology/System.hpp>

#include <chrono>
#include <boost/signals2.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {

/*! @brief Handles timings used in the main loop
 *
 * The main loop is composed of a "game loop" and a
 * "render loop". The game loop updates all of the game
 * logic, and should be called 60 times a second. The render
 * loop is detached, and needs to run as fast as possible
 *
 * This class takes care of counting and synchronizing the
 * game loop
 */
class LoopTimer :
public Ontology::System
{
public:

	/*!
	 * @brief Default constructor
	 */
	LoopTimer();

	/*!
	 * @brief Constructor with FPS setting.
	 */
    LoopTimer(unsigned long fps);

	/*!
	 * @brief Default destructor
	 */
	~LoopTimer();

	/*!
	 * @brief Resets the timer
	 * Will reset the timer and the loop counter to 0
	 */
	void reset();

	/*!
	 * @brief Gets the elapsed time in seconds since the last reset.
	 */
	float getElapsedTime();

	/*!
	 * @brief Returns true when it's time to call the update loop
	 * @return If it's time to call the update loop, true is returned
	 */
	bool isTimeToUpdate();

	/*!
	 * @brief Sets the frame rate the update loop should have
	 * @param The frame rate the update loop should aim to be
	 */
	void setFPS( unsigned long fps );

	/*!
	 * @brief Gets the time between frames in seconds
	 */
	float getTimeBetweenFrames();

	/*!
	 * @brief Gets the current rendering frame rate
	 * @return Returns the current rendering frame rate
	 */
	unsigned long getRenderFPS();

	 /*!
	 * @brief Gets the current update frame rate
	 * @return Returns the current update frame rate
	 */
	unsigned long getUpdateFPS();

	/*!
	 * @brief Should be called by the renderer every render frame.
	 */
    void onFrameRendered();

    boost::signals2::signal<void()> on_game_loop;

private:

    // implement ontology methods
    void initialise() override {};
    void processEntity(Ontology::Entity&) override {};

	/// timer implementation
	std::chrono::system_clock::time_point m_Timer;

	/// counts how many render loops have passed
	/// this is incremented every time checkUpdateLoop() is called
	unsigned long m_GameLoopCounter;

	/// counts how many update loops were authorized
	/// this is only incremented whenever it is time to update the logic loop
	unsigned long m_RenderLoopCounter;

	/// stores how much time is allowed to be between frames
	float m_TimeBetweenFrames;

	/// statistics
	struct statistics_t
	{
		statistics_t( void );
		unsigned long renderFrameRate;
		unsigned long gameFrameRate;
	}m_Statistics;

};

} // namespace OpenRump
