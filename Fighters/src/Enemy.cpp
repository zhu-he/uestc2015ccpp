#include "Enemy.hpp"

Enemy::Enemy(const int& enemyType)
{
    for (int i = 0; i < (int)enemyImage[enemyType].size(); ++i)
	{
		m_enemyTexture.push_back(SpriteSheet::getTexture(enemyImage[enemyType][i]));
	}
    for (int i = 0; i < (int)enemyDownImage[enemyType].size(); ++i)
	{
		m_enemyDownTexture.push_back(SpriteSheet::getTexture(enemyDownImage[enemyType][i]));
	}
	if (enemyType != 0)
	{
		m_enemyHitTexture = SpriteSheet::getTexture(enemyHitImage[enemyType]);
	}
	m_hp = enemyHp[enemyType];
	setTexture(m_enemyTexture[0]);
	m_enemyImagePos = 0;
	setOrigin(getTextureRect().width / 2, getTextureRect().height);
	m_isAlive = true;
	m_speed = enemySpeed[enemyType];
	setPosition(rand() % (screenWidth - getTextureRect().width) + getTextureRect().width, 0);
	m_enemyDownSoundBuffer.loadFromFile(enemyDownSoundPath[enemyType]);
	m_enemyDownSound.setBuffer(m_enemyDownSoundBuffer);
}

Enemy::~Enemy()
{

}

void Enemy::animate()
{
    move(0, m_speed);
    setTexture(m_enemyTexture[0]);
}

void Enemy::hit()
{
	m_hp--;
	if (m_hp == 0)
	{
		die();
	}
	else
	{
		setTexture(m_enemyHitTexture);
	}
}

void Enemy::die()
{
	m_isAlive = false;
	m_enemyDownSound.play();
}

std::string Enemy::getType()
{
	return "Enemy";
}

bool Enemy::isAlive()
{
	return m_isAlive;
}

