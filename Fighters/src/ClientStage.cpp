#include "ClientStage.hpp"
#include "Hero.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Ufo.hpp"
#include "Hero2.hpp"

ClientStage::ClientStage(sf::RenderWindow& window, sf::TcpSocket& server) : MultiplayerStage(window), m_server(server)
{
	m_controlHero = m_hero2;
}

ClientStage::~ClientStage()
{

}

void ClientStage::addEntity(Entity* entity)
{
	Stage::addEntity(entity);
}

bool ClientStage::update()
{
	sf::Packet packet;
	std::string cmd;
	if (m_server.receive(packet) == sf::Socket::Disconnected)
	{
		return false;
	}
	while (packet >> cmd)
	{
		if (cmd == "A")
		{
			int id;
			packet >> id;
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
				bullet->setId(id);
				if (type == HeroBullet)
				{
					((Hero*)m_hero)->resetShootTime();
				}
				else if (type == Hero2Bullet)
				{
					((Hero2*)m_hero2)->resetShootTime();
				}
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
				enemy->setId(id);
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
				ufo->setId(id);
				addEntity(ufo);
			}
		}
		else if (cmd == "M")
		{
			int positionX, positionY;
			packet >> positionX >> positionY;
			m_hero->setPosition(positionX, positionY);
		}
		else if (cmd == "D")
		{
			int id;
			packet >> id;
			dieEntity(findEntityById(id));
		}
		else if (cmd == "H")
		{
			int id;
			packet >> id;
			hitEntity(findEntityById(id));
		}
		else if (cmd == "F")
		{
			m_isHeroFire = true;
		}
		else if (cmd == "f")
		{
			m_isHeroFire = false;
		}
		else if (cmd == "L")
		{
			m_isHeroLeft = true;
		}
		else if (cmd == "R")
		{
			m_isHeroRight = true;
		}
		else if (cmd == "T")
		{
			m_isHeroUp = true;
		}
		else if (cmd == "B")
		{
			m_isHeroDown = true;
		}
		else if (cmd == "l")
		{
			m_isHeroLeft = false;
		}
		else if (cmd == "r")
		{
			m_isHeroRight = false;
		}
		else if (cmd == "t")
		{
			m_isHeroUp = false;
		}
		else if (cmd == "b")
		{
			m_isHeroDown = false;
		}
	}
	m_sendCounter++;
	if (m_sendCounter % 5 == 0)
	{
		m_packet << "M";
		m_packet << (int)m_hero2->getPosition().x;
		m_packet << (int)m_hero2->getPosition().y;
	}
	if (m_isHeroLeft)
	{
		((Hero*)m_hero)->moveLeft();
	}
	if (m_isHeroRight)
	{
		((Hero*)m_hero)->moveRight();
	}
	if (m_isHeroUp)
	{
		((Hero*)m_hero)->moveUp();
	}
	if (m_isHeroDown)
	{
		((Hero*)m_hero)->moveDown();
	}
	if (m_isHero2Left)
	{
		((Hero2*)m_hero2)->moveLeft();
	}
	if (m_isHero2Right)
	{
		((Hero2*)m_hero2)->moveRight();
	}
	if (m_isHero2Up)
	{
		((Hero2*)m_hero2)->moveUp();
	}
	if (m_isHero2Down)
	{
		((Hero2*)m_hero2)->moveDown();
	}
	animate();
	draw();
	m_server.send(m_packet);
	m_packet.clear();
	return true;
}

Entity* ClientStage::findEntityById(int id)
{
    for (Entity* entity : m_entitys)
	{
		if (entity->getId() == id)
		{
			return entity;
		}
	}
	return nullptr;
}

void ClientStage::fire()
{
	if (!m_isHero2Fire)
	{
		m_packet << "F";
		m_isHero2Fire = true;
	}
}

void ClientStage::noFire()
{
	if (m_isHero2Fire)
	{
		m_packet << "f";
		m_isHero2Fire = false;
	}
}

void ClientStage::moveLeft()
{
	if (!m_isHero2Left)
	{
		m_packet << "L";
		m_isHero2Left = true;
	}
}

void ClientStage::moveRight()
{
	if (!m_isHero2Right)
	{
		m_packet << "R";
		m_isHero2Right = true;
	}
}

void ClientStage::moveUp()
{
	if (!m_isHero2Up)
	{
		m_packet << "T";
		m_isHero2Up = true;
	}
}

void ClientStage::moveDown()
{
	if (!m_isHero2Down)
	{
		m_packet << "B";
		m_isHero2Down = true;
	}
}

void ClientStage::moveNoLeft()
{
	if (m_isHero2Left)
	{
		m_packet << "l";
		m_isHero2Left = false;
	}
}

void ClientStage::moveNoRight()
{
	if (m_isHero2Right)
	{
		m_packet << "r";
		m_isHero2Right = false;
	}
}

void ClientStage::moveNoUp()
{
	if (m_isHero2Up)
	{
		m_packet << "t";
		m_isHero2Up = false;
	}
}

void ClientStage::moveNoDown()
{
	if (m_isHero2Down)
	{
		m_packet << "b";
		m_isHero2Down = false;
	}
}

