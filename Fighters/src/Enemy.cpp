#include "Enemy.hpp"
#include "Bullet.hpp"

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
	switch (enemyType)
	{
	case 0:
		m_collision.setPointCount(3);
		m_collision.setPoint(0, sf::Vector2f(0, 10));
		m_collision.setPoint(1, sf::Vector2f(60, 10));
		m_collision.setPoint(2, sf::Vector2f(30, 45));
		m_collision.setFillColor(sf::Color(255, 0, 0, 100));
		break;
	case 1:
		m_collision.setPointCount(4);
		m_collision.setPoint(0, sf::Vector2f(35, 0));
		m_collision.setPoint(1, sf::Vector2f(0, 50));
		m_collision.setPoint(2, sf::Vector2f(35, 95));
		m_collision.setPoint(3, sf::Vector2f(70, 50));
		m_collision.setFillColor(sf::Color(255, 0, 0, 100));
		break;
	case 2:
		m_collision.setPointCount(6);
		m_collision.setPoint(0, sf::Vector2f(20, 0));
		m_collision.setPoint(1, sf::Vector2f(0, 200));
		m_collision.setPoint(2, sf::Vector2f(40, 240));
		m_collision.setPoint(3, sf::Vector2f(130, 240));
		m_collision.setPoint(4, sf::Vector2f(170, 200));
		m_collision.setPoint(5, sf::Vector2f(150, 0));
		m_collision.setFillColor(sf::Color(255, 0, 0, 100));
		break;
	default:
		break;
	}
	setColor(sf::Color(64, 64, 255));
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
	if (getPosition().y < 0)
	{
		m_isAlive = false;
		return;
	}
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
	default:
		break;
    }
}

void Enemy::hit()
{
	m_hp--;
	if (m_hp <= 0)
	{
		die();
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
		m_stage->addScore(enemyScore[m_enemyType]);
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

sf::ConvexShape Enemy::getCollision()
{
	return m_collision;
}

void Enemy::fire(const sf::Vector2f& heroPosition)
{
	if (m_lastShootTime.getElapsedTime() >= sf::seconds(enemyBulletInterval[m_enemyType]) && getPosition().y + enemyFireDistance < heroPosition.y)
	{
		for (int i = 0; i < (int)enemyBulletDirection[m_enemyType].size(); ++i)
		{
			sf::Transform transform;
			transform.rotate(enemyBulletDirection[m_enemyType][i]);
			Bullet* bullet = new Bullet(EnemyBullet, getPosition(), transform.transformPoint(heroPosition - getPosition()));
			m_stage->addEntity(bullet);
		}
		m_lastShootTime.restart();
	}
}
