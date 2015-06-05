#ifndef __PAUSABLECLOCK_HPP__
#define __PAUSABLECLOCK_HPP__

#include <SFML/System/Clock.hpp>

class PausableClock : public sf::Clock
{
	public:
		PausableClock();
		void pause();
		void resume();
		sf::Time restart();
		sf::Time getElapsedTime();
	private:
		sf::Time m_pauseTime;
		sf::Time m_totalTime;
		bool isPaused;
};

#endif // __PAUSABLECLOCK_HPP__
