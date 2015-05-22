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
	m_collision.setPoint(0, sf::Vector2f(53, 5));
	m_collision.setPoint(1, sf::Vector2f(24, 85));
	m_collision.setPoint(2, sf::Vector2f(80, 85));
	m_collision.setFillColor(sf::Color(255, 0, 0, 100));
	m_level = 0;
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

void Hero::moveUp()
{
	if (getPosition().y > 0)
	{
		move(0, -heroSpeed);
	}
}

void Hero::moveDown()
{
	if (getPosition().y < screenHeight)
	{
		move(0, heroSpeed);
	}
}

void Hero::hit()
{
	if (m_invincible.getElapsedTime() < sf::seconds(invincibleTime))
	{
		return;
	}
    m_hp--;
    m_stage->setHpText(m_hp);
    if (m_hp <= 0 && m_status != Dying)
	{
		die();
	}
	else
	{
		m_invincible.restart();
		m_invincibleFlash.restart();
	}
}

void Hero::die()
{
	m_status = Dying;
	m_heroImageCounter = 0;
}

void Hero::animate()
{
	if (m_invincible.getElapsedTime() < sf::seconds(invincibleTime) && m_stage->getGameStatus() == Playing)
	{
		if (m_invincibleFlash.getElapsedTime() >= sf::seconds(invincibleFlashInterval))
		{
			m_isFlash = !m_isFlash;
			m_invincibleFlash.restart();
		}
	}
	else
	{
		m_isFlash = false;
	}
	if (m_isFlash)
	{
		setColor(sf::Color::Transparent);
	}
	else
	{
		m_stage->drawLight(getPosition(), sf::Color(5 / m_lastShootTime.getElapsedTime().asSeconds(), 0, 0), 10);
		setColor(sf::Color(255, 64, 64));
	}
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
	m_level = 0;
	m_invincible.restart();
	m_invincibleFlash.restart();
}

void Hero::fire()
{
	if (m_lastShootTime.getElapsedTime() >= sf::seconds(heroBulletInterval))
	{
		m_bulletSound.play();
		for (int i = 0; i < (int)heroBulletDirection[m_level].size(); ++i)
		{
			sf::Transform transform;
			transform.rotate(heroBulletDirection[m_level][i].y);
			Bullet* bullet = new Bullet(HeroBullet, getPosition() + sf::Vector2f(heroBulletDirection[m_level][i].x, bulletOffsetY), transform.transformPoint(sf::Vector2f(0, -1)));
			m_stage->addEntity(bullet);
		}
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

bool Hero::isFlash()
{
	return m_isFlash;
}

void Hero::levelup()
{
	if (m_level != (int)heroBulletDirection.size() - 1)
	{
		m_level++;
	}
}
