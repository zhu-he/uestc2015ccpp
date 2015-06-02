#include "Bullet.hpp"
#include <cmath>

std::vector<sf::Texture> Bullet::m_bulletTexture;

Bullet::Bullet(BulletType bulletType, const sf::Vector2f& position, const sf::Vector2f& direction)
{
	m_direction = direction;
	m_bulletType = bulletType;
	setTexture(m_bulletTexture[bulletType]);
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	m_isAlive = true;
	m_collision.setPointCount(4);
	m_collision.setPoint(0, sf::Vector2f(2, 0));
	m_collision.setPoint(1, sf::Vector2f(2, 20));
	m_collision.setPoint(2, sf::Vector2f(7, 20));
	m_collision.setPoint(3, sf::Vector2f(7, 0));
	m_collision.setFillColor(sf::Color(255, 0, 0, 100));
	setPosition(position);
	rotate(atan2(direction.y, direction.x) * 180 / PI + 90);
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	m_bulletSpeed.x = direction.x * bulletSpeed[bulletType] / distance;
	m_bulletSpeed.y = direction.y * bulletSpeed[bulletType] / distance;
	if (bulletType == 2)
	{
		setColor(sf::Color::Green);
	}
}

BulletType Bullet::getBulletType()
{
	return m_bulletType;
}

void Bullet::loadResources()
{
	for (int i = 0; i < (int)bulletImage.size(); ++i)
	{
		m_bulletTexture.push_back(SpriteSheet::getTexture(bulletImage[i]));
	}
}

void Bullet::hit()
{

}

void Bullet::die()
{
	m_isAlive = false;
}

sf::Vector2f Bullet::getDirection()
{
    return m_direction;
}

void Bullet::animate(sf::Time frameTime)
{
	move(m_bulletSpeed * frameTime.asSeconds());
	if (getPosition().x + getTextureRect().width / 2 < 0 ||
		getPosition().y + getTextureRect().height / 2 < 0 ||
		getPosition().x - getTextureRect().width / 2 > screenWidth ||
		getPosition().y - getTextureRect().height / 2 > screenHeight)
	{
		m_isAlive = false;
	}
}

std::string Bullet::getType()
{
	return "Bullet";
}
