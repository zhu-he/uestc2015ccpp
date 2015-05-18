#include "Hero.hpp"

std::vector<sf::Texture> Hero::m_heroTexture;
std::vector<sf::Texture> Hero::m_heroBlowupTexture;

Hero::Hero()
{
	setTexture(m_heroTexture[0]);
	m_heroImageCounter = 0;
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	setPosition(screenWidth / 2, screenHeight - getTextureRect().height / 2);
	m_isAlive = true;
	m_bulletSoundBuffer.loadFromFile(bulletSoundPath);
	m_bulletSound.setBuffer(m_bulletSoundBuffer);
	m_hp = heroHp;
	m_status = Normal;
	m_collision.setPointCount(3);
	m_collision.setPoint(0, sf::Vector2f(52, 0));
	m_collision.setPoint(1, sf::Vector2f(2, 90));
	m_collision.setPoint(2, sf::Vector2f(102, 90));
	m_collision.setFillColor(sf::Color(255, 0, 0, 100));
}

Hero::~Hero()
{

}

void Hero::loadResources()
{
    for (int i = 0; i < (int)heroImage.size(); ++i)
	{
		m_heroTexture.push_back(SpriteSheet::getTexture(heroImage[i]));
	}
    for (int i = 0; i < (int)heroBlowupImage.size(); ++i)
	{
		m_heroBlowupTexture.push_back(SpriteSheet::getTexture(heroBlowupImage[i]));
	}
}

void Hero::moveLeft()
{
	if (getPosition().x > 0)
	{
		move(-heroSpeed, 0);
	}
}

void Hero::moveRight()
{
	if (getPosition().x < screenWidth)
	{
		move(heroSpeed, 0);
	}
}

void Hero::hit()
{
    m_hp--;
    m_stage->setHpText(m_hp);
    if (m_hp <= 0 && m_status != Dying)
	{
		die();
	}
}

void Hero::die()
{
	m_status = Dying;
	m_heroImageCounter = 0;
}

sf::ConvexShape Hero::getCollision()
{
	return m_collision;
}

void Hero::animate()
{
	if (m_enemyAnimateClock.getElapsedTime() < sf::seconds(animateInterval))
	{
		return;
	}
	m_enemyAnimateClock.restart();
	switch (m_status)
	{
	case Normal:
		setTexture(m_heroTexture[m_heroImageCounter]);
		m_heroImageCounter = (m_heroImageCounter + 1) % heroImage.size();
		break;
	case Dying:
		setTexture(m_heroBlowupTexture[m_heroImageCounter]);
		m_heroImageCounter++;
		if (m_heroImageCounter == (int)m_heroBlowupTexture.size())
		{
			m_isAlive = false;
		}
		break;
	default:
		break;
	}
}

void Hero::revive()
{
    m_status = Normal;
	m_hp = heroHp;
	m_isAlive = true;
	m_heroImageCounter = 0;
	setPosition(screenWidth / 2, screenHeight - getTextureRect().height / 2);
}

void Hero::fire()
{
	if (m_lastShootTime.getElapsedTime() >= sf::seconds(heroBulletInterval))
	{
		m_bulletSound.play();
		Bullet* bullet = new Bullet(HeroBullet);
		bullet->setPosition(getPosition() + sf::Vector2f(0, bulletOffsetY));
		m_stage->addEntity(bullet);
		m_lastShootTime.restart();
	}
}

std::string Hero::getType()
{
	return "Hero";
}

bool Hero::isAlive()
{
	return m_isAlive;
}
