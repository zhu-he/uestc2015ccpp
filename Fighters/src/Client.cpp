#include "Client.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "ClientStage.hpp"

Client::Client(sf::RenderWindow& window, Background& background) : m_window(window), m_background(background)
{
	m_loading.setFont(Font::getFont());
	m_loading.setCharacterSize(30);
	m_loading.setString("Connecting server");
	m_loading.setOrigin(m_loading.getLocalBounds().width / 2, m_loading.getLocalBounds().height / 2);
	m_loading.setPosition(screenWidth / 2, screenHeight / 2);
}

Client::~Client()
{

}

void Client::setIp(std::string ip)
{
	m_ip = ip;
}

void Client::start()
{
	m_loading.setColor(Font::getColor());
	m_isRunning = true;
	sf::TcpSocket socket;
	int port = 54000;
	socket.setBlocking(false);
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
		if (socket.connect(m_ip.c_str(), port) == sf::Socket::Done)
		{
			break;
		}
		port++;
		if (port == 54005)
		{
			port = 54000;
		}
		m_window.clear();
		m_background.animate();
		m_window.draw(m_background);
		m_window.draw(m_loading);
		m_window.display();
	}
	if (m_isRunning)
	{
		ClientStage stage(m_window, m_background, socket);
		stage.play();
	}
}
