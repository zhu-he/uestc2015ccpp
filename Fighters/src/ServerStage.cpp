#include "ServerStage.hpp"
#include "Sound.hpp"
#include "Hero.hpp"
#include "Hero2.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Ufo.hpp"

extern sf::Clock gameClock;

ServerStage::ServerStage(sf::RenderWindow& window, sf::TcpSocket& client) : Stage(window), m_client(client)
{
	m_hero = new Hero();
	m_hero->setPosition(screenWidth / 4, m_hero->getPosition().y);
	addEntity(m_hero);
	m_hero2 = new Hero2();
	m_hero2->setPosition(screenWidth / 4 * 3, m_hero->getPosition().y);
	addEntity(m_hero2);
	m_sendCounter = 0;
}

ServerStage::~ServerStage()
{

}

void ServerStage::init()
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

void ServerStage::addEntity(Entity* entity)
{
	sf::Packet packet;
	packet << "A";
	if (entity->getType() == "Bullet")
	{
		packet << "B";
		packet << ((Bullet*)entity)->getBulletType();
		packet << (int)entity->getPosition().x;
		packet << (int)entity->getPosition().y;
		packet << (int)((Bullet*)entity)->getDirection().x;
		packet << (int)((Bullet*)entity)->getDirection().y;
		//m_client.send(packet);
	}
	else if (entity->getType() == "Enemy")
	{
		packet << "E";
		packet << ((Enemy*)entity)->getEnemyType();
		packet << (int)entity->getPosition().x;
		packet << (int)entity->getPosition().y;
		m_client.send(packet);
	}
	else if (entity->getType() == "Ufo")
	{
		packet << "U";
		packet << ((Ufo*)entity)->getUfoType();
		packet << (int)entity->getPosition().x;
		packet << (int)entity->getPosition().y;
		m_client.send(packet);
	}
	Stage::addEntity(entity);
}

void ServerStage::update()
{
	m_sendCounter++;
	if (m_sendCounter % 3)
	{
		sf::Packet packet;
		packet << "H";
		packet << (int)m_hero->getPosition().x;
		packet << (int)m_hero->getPosition().y;
		m_client.send(packet);
	}
	sf::Packet packet;
	m_client.receive(packet);
	std::string cmd;
	while (packet >> cmd)
	{
		if (cmd == "H")
		{
			int positionX, positionY;
			packet >> positionX >> positionY;
			m_hero2->setPosition(positionX, positionY);
		}
	}
	Stage::update();
}
