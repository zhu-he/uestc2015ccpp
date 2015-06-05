#include "ServerStage.hpp"
#include "Sound.hpp"
#include "Hero.hpp"
#include "Hero2.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Ufo.hpp"

ServerStage::ServerStage(Window& window, Background& background, sf::TcpSocket& client) : MultiplayerStage(window, background, client)
{
	m_idCounter = 0;
}

void ServerStage::addEntity(Entity* entity)
{
	entity->setId(m_idCounter);
	if (entity->getType() == "Bullet")
	{
		m_packet << "A";
		m_packet << m_idCounter;
		m_packet << "B";
		m_packet << ((Bullet*)entity)->getBulletType();
		m_packet << (int)entity->getPosition().x;
		m_packet << (int)entity->getPosition().y;
		m_packet << (float)((Bullet*)entity)->getDirection().x;
		m_packet << (float)((Bullet*)entity)->getDirection().y;
	}
	else if (entity->getType() == "Enemy")
	{
		m_packet << "A";
		m_packet << m_idCounter;
		m_packet << "E";
		m_packet << ((Enemy*)entity)->getEnemyType();
		m_packet << (int)entity->getPosition().x;
		m_packet << (int)entity->getPosition().y;
	}
	else if (entity->getType() == "Ufo")
	{
		m_packet << "A";
		m_packet << m_idCounter;
		m_packet << "U";
		m_packet << ((Ufo*)entity)->getUfoType();
		m_packet << (int)entity->getPosition().x;
		m_packet << (int)entity->getPosition().y;
	}
	m_idCounter++;
	Stage::addEntity(entity);
}

void ServerStage::dieEntity(Entity* entity)
{
	m_packet << "D";
	m_packet << entity->getId();
	entity->die();
}

void ServerStage::hitEntity(Entity* entity)
{
	m_packet << "H";
	m_packet << entity->getId();
	entity->hit();
}

bool ServerStage::update(sf::Time frameTime)
{
	m_sendCounter++;
	if (m_sendCounter % 10 == 0)
	{
		m_packet << "M";
		m_packet << (int)m_hero->getPosition().x;
		m_packet << (int)m_hero->getPosition().y;
	}
	sf::Packet packet;
	m_socket.receive(packet);
	std::string cmd;
	while (packet >> cmd)
	{
		if (cmd == "M")
		{
			int positionX, positionY;
			packet >> positionX >> positionY;
			m_hero2->setPosition(positionX, positionY);
		}
		else if (cmd == "F")
		{
			m_isHero2Fire = true;
		}
		else if (cmd == "f")
		{
			m_isHero2Fire = false;
		}
		else if (cmd == "L")
		{
			m_isHero2Left = true;
		}
		else if (cmd == "R")
		{
			m_isHero2Right = true;
		}
		else if (cmd == "T")
		{
			m_isHero2Up = true;
		}
		else if (cmd == "B")
		{
			m_isHero2Down = true;
		}
		else if (cmd == "l")
		{
			m_isHero2Left = false;
		}
		else if (cmd == "r")
		{
			m_isHero2Right = false;
		}
		else if (cmd == "t")
		{
			m_isHero2Up = false;
		}
		else if (cmd == "b")
		{
			m_isHero2Down = false;
		}
		else if (cmd == "U")
		{
			((Hero*)m_hero2)->useBomb();
			m_isBombing = true;
			m_bombClock.restart();
			Sound::playUseBombSound();
		}
		else if (cmd == "I")
		{
			init();
		}
		else if (cmd == "P")
		{
			Stage::pause();
		}
		else if (cmd == "C")
		{
			Stage::resume();
		}
	}
	if (m_gameStatus == Playing)
	{
		if (m_isHero2Fire)
		{
			((Hero2*)m_hero2)->fire();
		}
		if (m_isHero2Left)
		{
			((Hero2*)m_hero2)->moveLeft(frameTime);
		}
		if (m_isHero2Right)
		{
			((Hero2*)m_hero2)->moveRight(frameTime);
		}
		if (m_isHero2Up)
		{
			((Hero2*)m_hero2)->moveUp(frameTime);
		}
		if (m_isHero2Down)
		{
			((Hero2*)m_hero2)->moveDown(frameTime);
		}
	}
	Stage::update(frameTime);
	if (m_packet.getDataSize() > 0)
	{
		m_socket.send(m_packet);
		m_packet.clear();
	}
	m_packet.clear();
	return true;
}

void ServerStage::fire()
{
	if (!m_isHeroFire)
	{
		m_packet << "F";
		m_isHeroFire = true;
	}
}

void ServerStage::noFire()
{
	if (m_isHeroFire)
	{
		m_packet << "f";
		m_isHeroFire = false;
	}
}

void ServerStage::moveLeft()
{
	if (!m_isHeroLeft)
	{
		m_packet << "L";
		m_isHeroLeft = true;
	}
}

void ServerStage::moveRight()
{
	if (!m_isHeroRight)
	{
		m_packet << "R";
		m_isHeroRight = true;
	}
}

void ServerStage::moveUp()
{
	if (!m_isHeroUp)
	{
		m_packet << "T";
		m_isHeroUp = true;
	}
}

void ServerStage::moveDown()
{
	if (!m_isHeroDown)
	{
		m_packet << "B";
		m_isHeroDown = true;
	}
}

void ServerStage::moveNoLeft()
{
	if (m_isHeroLeft)
	{
		m_packet << "l";
		m_isHeroLeft = false;
	}
}

void ServerStage::moveNoRight()
{
	if (m_isHeroRight)
	{
		m_packet << "r";
		m_isHeroRight = false;
	}
}

void ServerStage::moveNoUp()
{
	if (m_isHeroUp)
	{
		m_packet << "t";
		m_isHeroUp = false;
	}
}

void ServerStage::moveNoDown()
{
	if (m_isHeroDown)
	{
		m_packet << "b";
		m_isHeroDown = false;
	}
}

void ServerStage::bombup(Entity* hero)
{
	if (((Hero*)hero)->getType() == "Hero")
	{
		m_packet << "O";
	}
	else
	{
		m_packet << "o";
	}
	Stage::bombup(hero);
}

void ServerStage::levelup(Entity* hero)
{
	if (((Hero*)hero)->getType() == "Hero")
	{
		m_packet << "V";
	}
	else
	{
		m_packet << "v";
	}
	Stage::levelup(hero);
}
