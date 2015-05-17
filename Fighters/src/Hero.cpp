#include "Hero.hpp"

std::vector<sf::Texture> Hero::m_heroTexture;
std::vector<sf::Texture> Hero::m_heroBlowupTexture;

Hero::Hero()
{
	setTexture(m_heroTexture[0]);
	m_heroImageCounter = 0;
	setOrigin(getTextureRect().width / 2, 0);
	setPosition(screenWidth / 2, screenHeight - getTextureRect().height);
	m_isAlive = true;
	m_bulletSoundBuffer.loadFromFile(bulletSoundPath);
	m_bulletSound.setBuffer(m_bulletSoundBuffer);
	m_hp = heroHp;
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

void Hero::fire()
{
	if (m_lastShootTime.getElapsedTime() >= sf::seconds(bulletInterval))
	{
		m_bulletSound.play();
		Bullet* bullet = new Bullet();
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
