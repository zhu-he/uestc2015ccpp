#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <SFML/Network.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <string>
#include "Background.hpp"
#include "Window.hpp"

class Client
{
	public:
		Client(Window& window, Background& background);
		void setIp(std::string ip);
		void start();
	private:
		Window& m_window;
		sf::Text m_loading;
		std::string m_ip;
		Background& m_background;
		bool m_isRunning;
};

#endif // __CLIENT_HPP__
