#include "Server.hpp"
#include "Global.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "ServerStage.hpp"

Server::Server(sf::RenderWindow& window) : m_window(window)
{
	m_loading.setFont(Font::getFont());
	m_loading.setCharacterSize(30);
	m_loading.setString("Waiting for other player");
	m_loading.setOrigin(m_loading.getLocalBounds().width / 2, m_loading.getLocalBounds().height / 2);
	m_loading.setPosition(screenWidth / 2, screenHeight / 2);
}

Server::~Server()
{

}

void Server::setBackground(Background* background)
{
	m_background = background;
}

void Server::start()
{
	m_loading.setColor(Font::getColor());
	m_isRunning = true;
	sf::TcpListener listener;
	listener.listen(54000);
	sf::TcpSocket client;
	listener.setBlocking(false);
	client.setBlocking(false);
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
		m_background->animate();
		if (Shader::isAvailable())
		{
			m_window.draw(*m_background, Shader::getInvertShader());
		}
		else
		{
			m_window.draw(*m_background);
		}
		m_window.draw(m_loading);
		m_window.display();
	}
	if (m_isRunning)
	{
		ServerStage stage(m_window, client);
		stage.setBackground(m_background);
		stage.play();
	}
}
