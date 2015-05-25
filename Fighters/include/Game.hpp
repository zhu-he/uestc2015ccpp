#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Background.hpp"

class Game
{
	public:
		Game();
		virtual ~Game();
		void play();
		void quit();
	private:
		sf::RenderWindow m_window;
		sf::Text m_titleText;
		sf::Shader m_invertShader;
		bool m_isRunning;
		Background m_background;
};

#endif // __GAME_HPP__
