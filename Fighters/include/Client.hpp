#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <SFML/Window/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <string>
#include "Background.hpp"

class Client
{
	public:
		Client(sf::RenderWindow& window, Background& background);
		void setIp(std::string ip);
		void start();
	private:
		sf::RenderWindow& m_window;
		sf::Text m_loading;
		std::string m_ip;
		Background& m_background;
		bool m_isRunning;
};

#endif // __CLIENT_HPP__
