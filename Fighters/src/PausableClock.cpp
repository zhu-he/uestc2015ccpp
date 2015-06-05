#include "PausableClock.hpp"

PausableClock::PausableClock()
{
	isPaused = false;
}

void PausableClock::pause()
{
	if (isPaused)
	{
		return;
	}
	isPaused = true;
    m_pauseTime = Clock::getElapsedTime();
}

void PausableClock::resume()
{
	if (!isPaused)
	{
		return;
	}
	isPaused = false;
	m_totalTime += Clock::getElapsedTime() - m_pauseTime;
}

sf::Time PausableClock::restart()
{
	sf::Time time = getElapsedTime();
	m_totalTime = sf::Time::Zero;
	sf::Clock::restart();
	return time;
}

sf::Time PausableClock::getElapsedTime()
{
	return sf::Clock::getElapsedTime() - m_totalTime;
}
