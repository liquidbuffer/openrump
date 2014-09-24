// ----------------------------------------------------------------------------
// include files

#include <iostream>

#include <openrump/systems/LoopTimer.hpp>

namespace OpenRump {

// ----------------------------------------------------------------------------
LoopTimer::LoopTimer() :
	m_GameLoopCounter( 0 ),
	m_RenderLoopCounter( 0 ),
	m_TimeBetweenFrames( 0 )
{
}

// ----------------------------------------------------------------------------
LoopTimer::statistics_t::statistics_t() :
	renderFrameRate( 0 ),
	gameFrameRate( 0 )
{
}

// ----------------------------------------------------------------------------
LoopTimer::~LoopTimer()
{
}

// ----------------------------------------------------------------------------
void LoopTimer::reset()
{
	m_Timer = std::chrono::system_clock::now();
	m_GameLoopCounter = 0;
	m_RenderLoopCounter = 0;
}

// ----------------------------------------------------------------------------
float LoopTimer::getElapsedTime()
{
	using namespace std::chrono;
	auto duration = duration_cast<milliseconds>(system_clock::now() - m_Timer);
	return static_cast<float>(duration.count()) / 1000.0f;
}

// ----------------------------------------------------------------------------
void LoopTimer::setFPS( unsigned long fps )
{
	// calculate time between frames in seconds
	m_TimeBetweenFrames = 1.0f / fps;
}

// ----------------------------------------------------------------------------
float LoopTimer::getTimeBetweenFrames(void)
{
	return m_TimeBetweenFrames;
}

// ----------------------------------------------------------------------------
bool LoopTimer::isTimeToUpdate()
{

	// update internal statistics every second
	if(this->getElapsedTime() >= 1.0f)
	{

		// calculate render frame rate and game frame rate
		m_Statistics.renderFrameRate = m_RenderLoopCounter;
		m_Statistics.gameFrameRate = m_GameLoopCounter;
		m_RenderLoopCounter = 0;
		m_GameLoopCounter = 0;

		// reset timer
		m_Timer = std::chrono::system_clock::now();
#ifdef _DEBUG
		std::cout << "render FPS: " << m_Statistics.renderFrameRate <<
			"			update FPS: " << m_Statistics.gameFrameRate << std::endl;
#endif // _DEBUG
	}

	// calling this method means a render loop has occurred
	++m_RenderLoopCounter;

	// if time that has passed is smaller than the time that should have
	// passed, it's not time to update yet
	if( this->getElapsedTime() < m_GameLoopCounter*m_TimeBetweenFrames )
        return false;

	// game loop has been updated, increase counter
	++m_GameLoopCounter;

	// time to update
	return true;
}

// ----------------------------------------------------------------------------
unsigned long LoopTimer::getRenderFPS()
{
	return m_Statistics.renderFrameRate;
}

// ----------------------------------------------------------------------------
unsigned long LoopTimer::getUpdateFPS()
{
	return m_Statistics.gameFrameRate;
}

} // namespace OpenRump
