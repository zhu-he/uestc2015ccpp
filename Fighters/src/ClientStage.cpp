#include "ClientStage.hpp"
#include "Hero.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Ufo.hpp"
#include "Sound.hpp"
#include "Hero2.hpp"

extern sf::Clock gameClock;

ClientStage::ClientStage(sf::RenderWindow& window, sf::TcpSocket& server) : Stage(window), m_server(server)
{
	m_hero = new Hero();
	m_hero->setPosition(screenWidth / 4, m_hero->getPosition().y);
	addEntity(m_hero);
	m_hero2 = new Hero2();
	m_hero2->setPosition(screenWidth / 4 * 3, m_hero->getPosition().y);
	addEntity(m_hero2);
	m_sendCounter = 0;
}

ClientStage::~ClientStage()
{

}

void ClientStage::init()
{
	m_score = 0;
	m_bombCount = 0;
	m_isRunning = true;
	m_scoreText.setString("Score: 0");
	setHpText(heroHp);
	m_gameStatus = Playing;
	((Hero*)m_hero)->revive();
	((Hero2*)m_hero2)->revive();
	gameClock.restart();
	for (int i = 0; i < 3; ++i)
	{
		m_enemyClock[i].restart();
	}
	m_ufoClock.restart();
	for (std::vector<Entity*>::iterator it = m_entitys.begin(); it != m_entitys.end(); ++it)
	{
		if ((*it) != m_hero && (*it) != m_hero2)
		{
			delete *it;
			m_entitys.erase(it);
			it--;
		}
	}
	Sound::playGameMusicSound();
}

void ClientStage::addEntity(Entity* entity)
{
	Stage::addEntity(entity);
}

void ClientStage::play()
{
	ClientStage::init();
	sf::Packet packet;
	std::string cmd;
	while (m_window.isOpen() && m_isRunning)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_gameStatus = Paused;
					m_pausedMenu.setMenuCursor(0);
				}
				else if (event.key.code == sf::Keyboard::Down && m_gameStatus == Paused)
				{
					m_pausedMenu.next();
				}
				else if (event.key.code == sf::Keyboard::Up && m_gameStatus == Paused)
				{
					m_pausedMenu.previous();
				}
				else if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return) && m_gameStatus == Paused)
				{
					if (m_pausedMenu.getMenuCursor() == 0)
					{
						m_gameStatus = Playing;
					}
					else if (m_pausedMenu.getMenuCursor() == 1)
					{
						init();
					}
					else
					{
						m_isRunning = false;
					}
				}
				break;
			default:
				break;
			}
		}
		if (getGameStatus() == Playing && m_hero2)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				((Hero2*)m_hero2)->moveLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				((Hero2*)m_hero2)->moveRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				((Hero2*)m_hero2)->moveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				((Hero2*)m_hero2)->moveDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				((Hero2*)m_hero2)->fire();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				useBomb();
			}
		}
		if (m_server.receive(packet) == sf::Socket::Disconnected)
		{
			break;
		}
		while (packet >> cmd)
		{
			if (cmd == "A")
			{
                std::string type;
                packet >> type;
                if (type == "B")
				{
					int type;
					packet >> type;
					int positionX, positionY;
					packet >> positionX >> positionY;
					int directionX, directionY;
					packet >> directionX >> directionY;
					Bullet* bullet = new Bullet((BulletType)type, sf::Vector2f(positionX, positionY), sf::Vector2f(directionX, directionY));
					addEntity(bullet);
				}
				else if (type == "E")
				{
					int type;
					packet >> type;
					int positionX, positionY;
					packet >> positionX >> positionY;
					Enemy* enemy = new Enemy(type);
					enemy->setPosition(positionX, positionY);
					addEntity(enemy);
				}
				else if (type == "U")
				{
					int type;
					packet >> type;
					int positionX, positionY;
					packet >> positionX >> positionY;
					Ufo* ufo = new Ufo((UfoType)type);
					ufo->setPosition(positionX, positionY);
					addEntity(ufo);
				}
			}
			else if (cmd == "H")
			{
				int positionX, positionY;
				packet >> positionX >> positionY;
				m_hero->setPosition(positionX, positionY);
			}
		}
		m_sendCounter++;
		if (m_sendCounter % 3)
		{
			sf::Packet packet;
			packet << "H";
			packet << (int)m_hero2->getPosition().x;
			packet << (int)m_hero2->getPosition().y;
			m_server.send(packet);
		}
		animate();
		draw();
    }
	Sound::playGameMusicSound();
}
