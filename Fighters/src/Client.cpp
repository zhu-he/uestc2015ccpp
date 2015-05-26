#include "Client.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "ClientStage.hpp"

Client::Client(sf::RenderWindow& window) : m_window(window)
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

void Client::setBackground(Background* background)
{
	m_background = background;
}

void Client::setIp(std::string ip)
{
	m_ip = ip;
}

void Client::start()
{
	m_isRunning = true;
	sf::TcpSocket socket;
	sf::Socket::Status status;
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
		status = socket.connect(m_ip.c_str(), 54000);
		if (status == sf::Socket::Done)
		{
			break;
		}
		m_window.clear();
		m_background->animate();
		m_window.draw(*m_background, Shader::getInvertShader());
		m_window.draw(m_loading);
		m_window.display();
	}
	if (m_isRunning)
	{
		ClientStage stage(m_window, socket);
		stage.setBackground(m_background);
		stage.play();
	}
}
