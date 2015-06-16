#include "Hero.hpp"
#include "Sound.hpp"

std::vector<sf::Texture> Hero::m_heroTexture;
std::vector<sf::Texture> Hero::m_heroBlowupTexture;

Hero::Hero()
{
	setTexture(m_heroTexture[0]);
	m_heroImageCounter = 0;
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	setPosition(screenWidth / 2, screenHeight - getTextureRect().height / 2);
	m_isAlive = true;
	m_hp = heroHp;
	m_bomb = 0;
	m_status = Normal;
	m_collision.setPointCount(3);
	m_collision.setPoint(0, sf::Vector2f(53, 5));
	m_collision.setPoint(1, sf::Vector2f(24, 85));
	m_collision.setPoint(2, sf::Vector2f(80, 85));
	m_collision.setFillColor(sf::Color(255, 0, 0, 100));
	m_level = 0;
	m_isFlash = false;
	m_color = sf::Color(255, 64, 64);
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

void Hero::moveLeft(sf::Time frameTime)
{
	if (getPosition().x > 0 && m_status == Normal)
	{
		move(-heroSpeed * frameTime.asSeconds(), 0);
	}
}

void Hero::moveRight(sf::Time frameTime)
{
	if (getPosition().x < screenWidth && m_status == Normal)
	{
		move(heroSpeed * frameTime.asSeconds(), 0);
	}
}

void Hero::moveUp(sf::Time frameTime)
{
	if (getPosition().y > 0 && m_status == Normal)
	{
		move(0, -heroSpeed * frameTime.asSeconds());
	}
}

void Hero::moveDown(sf::Time frameTime)
{
	if (getPosition().y < screenHeight && m_status == Normal)
	{
		move(0, heroSpeed * frameTime.asSeconds());
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
	else if (m_hp > 0)
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

void Hero::resetShootTime()
{
	m_lastShootTime.restart();
}

void Hero::animate(sf::Time frameTime)
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
		if (getType() == "Hero")
		{
			m_stage->drawLight(getPosition(), sf::Color(5 / m_lastShootTime.getElapsedTime().asSeconds(), 0, 0), 10);
		}
		else
		{
			m_stage->drawLight(getPosition(), sf::Color(0, 5 / m_lastShootTime.getElapsedTime().asSeconds(), 0), 10);
		}
		setColor(m_color);
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
	m_bomb = 0;
	m_isAlive = true;
	m_heroImageCounter = 0;
	setPosition(screenWidth / 2, screenHeight - getTextureRect().height / 2);
	m_level = 0;
	m_invincible.restart();
	m_invincibleFlash.restart();
}

void Hero::fire()
{
	if (!m_isAlive)
	{
		return;
	}
	if (m_lastShootTime.getElapsedTime() >= sf::seconds(heroBulletInterval))
	{
		Sound::playBulletSound();
		for (int i = 0; i < (int)heroBulletDirection[m_level].size(); ++i)
		{
			sf::Transform transform;
			transform.rotate(heroBulletDirection[m_level][i].y);
			if (getType() == "Hero")
			{
				Bullet* bullet = new Bullet(HeroBullet, getPosition() + sf::Vector2f(heroBulletDirection[m_level][i].x, bulletOffsetY), transform.transformPoint(sf::Vector2f(0, -1)));
				m_stage->addEntity(bullet);
			}
			else
			{
				Bullet* bullet = new Bullet(Hero2Bullet, getPosition() + sf::Vector2f(heroBulletDirection[m_level][i].x, bulletOffsetY), transform.transformPoint(sf::Vector2f(0, -1)));
				m_stage->addEntity(bullet);
			}
		}
		m_lastShootTime.restart();
	}
}

std::string Hero::getType()
{
	return "Hero";
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

void Hero::bombup()
{
	m_bomb++;
}

int Hero::getBomb()
{
	return m_bomb;
}

void Hero::useBomb()
{
	m_bomb--;
}
