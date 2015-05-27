#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <SFML/Window/Window.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Background.hpp"

class Server
{
	public:
		Server(sf::RenderWindow& window, Background& background);
		virtual ~Server();
		void start();
	private:
		sf::RenderWindow& m_window;
		sf::Text m_loading;
		Background& m_background;
		bool m_isRunning;
};

#endif // __SERVER_HPP__
