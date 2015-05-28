#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/Graphics.hpp>
#include "Background.hpp"

class Game
{
	public:
		Game();
		void play();
	private:
		sf::RenderWindow m_window;
		sf::Text m_titleText;
		Background m_background;
};

#endif // __GAME_HPP__
