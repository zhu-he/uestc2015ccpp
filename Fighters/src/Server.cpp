#include "Server.hpp"
#include "Global.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "ServerStage.hpp"
#include "PausableClock.hpp"

Server::Server(Window& window, Background& background) : m_window(window), m_background(background)
{
	m_loading.setFont(Font::getFont());
	m_loading.setCharacterSize(30);
	m_loading.setString("Waiting for other player");
	m_loading.setOrigin(m_loading.getLocalBounds().width / 2, m_loading.getLocalBounds().height / 2);
	m_loading.setPosition(screenWidth / 2, screenHeight / 2);
}

void Server::start()
{
	m_loading.setColor(Font::getColor());
	m_isRunning = true;
	sf::TcpListener listener;
	int port = 54000;
	while (listener.listen(port) != sf::Socket::Done && port < 54005)
	{
		port++;
	}
	if (port == 54005)
	{
		return;
	}
	sf::TcpSocket client;
	listener.setBlocking(false);
	client.setBlocking(false);
	PausableClock frameClock;
	while (m_isRunning)
	{
		sf::Event event;
        while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_isRunning = false;
				m_window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_isRunning = false;
				}
				break;
			default:
				break;
			}
		}
		if (listener.accept(client) == sf::Socket::Done)
		{
			break;
		}
		m_window.clear();
		m_background.animate(frameClock.restart());
		m_window.draw(m_background);
		m_window.draw(m_loading);
		m_window.display();
	}
	if (m_isRunning)
	{
		ServerStage stage(m_window, m_background, client);
		stage.play();
	}
}
