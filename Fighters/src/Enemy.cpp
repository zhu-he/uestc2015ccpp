#include "Enemy.hpp"

std::vector<sf::Texture> Enemy::m_enemyTexture[3];
std::vector<sf::Texture> Enemy::m_enemyDownTexture[3];
sf::Texture Enemy::m_enemyHitTexture[3];
sf::SoundBuffer Enemy::m_enemyDownSoundBuffer[3];
sf::Sound Enemy::m_enemyDownSound[3];

Enemy::Enemy(const int& enemyType)
{
	m_enemyType = enemyType;
	m_hp = enemyHp[enemyType];
	setTexture(m_enemyTexture[enemyType][0]);
	m_enemyImageCounter = 0;
	setOrigin(getTextureRect().width / 2, getTextureRect().height);
	m_isAlive = true;
	m_speed = enemySpeed[enemyType];
	setPosition(rand() % (screenWidth - getTextureRect().width) + getTextureRect().width, 0);
	m_status = Normal;
}

Enemy::~Enemy()
{

}

void Enemy::loadResources()
{
	for (int enemyType = 0; enemyType < 3; ++enemyType)
	{
		for (int i = 0; i < (int)enemyImage[enemyType].size(); ++i)
		{
			m_enemyTexture[enemyType].push_back(SpriteSheet::getTexture(enemyImage[enemyType][i]));
		}
		for (int i = 0; i < (int)enemyDownImage[enemyType].size(); ++i)
		{
			m_enemyDownTexture[enemyType].push_back(SpriteSheet::getTexture(enemyDownImage[enemyType][i]));
		}
		if (enemyType != 0)
		{
			m_enemyHitTexture[enemyType] = SpriteSheet::getTexture(enemyHitImage[enemyType]);
		}
		m_enemyDownSoundBuffer[enemyType].loadFromFile(enemyDownSoundPath[enemyType]);
		m_enemyDownSound[enemyType].setBuffer(m_enemyDownSoundBuffer[enemyType]);
	}
}

void Enemy::animate()
{
    move(0, m_speed);
    if (m_enemyAnimateClock.getElapsedTime() < sf::seconds(animateInterval))
	{
		return;
	}
	m_enemyAnimateClock.restart();
    switch (m_status)
    {
	case Normal:
		setTexture(m_enemyTexture[m_enemyType][m_enemyImageCounter]);
		m_enemyImageCounter = (m_enemyImageCounter + 1) % enemyImage[m_enemyType].size();
		break;
	case Hit:
		setTexture(m_enemyHitTexture[m_enemyType]);
		m_status = Normal;
		break;
	case Dying:
		setTexture(m_enemyDownTexture[m_enemyType][m_enemyImageCounter]);
		m_enemyImageCounter++;
		if (m_enemyImageCounter >= (int)m_enemyDownTexture[m_enemyType].size())
		{
			m_isAlive = false;
			m_enemyDownSound[m_enemyType].play();
		}
		break;
    }
}

void Enemy::hit()
{
	m_hp--;
	if (m_hp <= 0)
	{
		if (m_status != Dying)
		{
			m_status = Dying;
			m_enemyImageCounter = 0;
		}
	}
	else
	{
		m_status = Hit;
	}
}

void Enemy::die()
{
	if (m_status != Dying)
	{
		m_status = Dying;
		m_enemyImageCounter = 0;
	}
}

std::string Enemy::getType()
{
	return "Enemy";
}

int Enemy::getEnemyType()
{
	return m_enemyType;
}

bool Enemy::isAlive()
{
	return m_isAlive;
}

Status Enemy::getStatus()
{
	return m_status;
}
