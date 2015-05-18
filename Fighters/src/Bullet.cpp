#include "Bullet.hpp"
#include <cmath>

std::vector<sf::Texture> Bullet::m_bulletTexture;

Bullet::Bullet(BulletType bulletType)
{
	m_bulletType = bulletType;
	setTexture(m_bulletTexture[bulletType]);
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	m_isAlive = true;
	m_bulletSpeed.x = 0;
	m_bulletSpeed.y = bulletSpeed[bulletType];
	m_collision.setPointCount(4);
	m_collision.setPoint(0, sf::Vector2f(2, 0));
	m_collision.setPoint(1, sf::Vector2f(7, 0));
	m_collision.setPoint(2, sf::Vector2f(7, 20));
	m_collision.setPoint(3, sf::Vector2f(2, 20));
	m_collision.setFillColor(sf::Color(255, 0, 0, 100));
}

Bullet::Bullet(BulletType bulletType, const sf::Vector2f& from, const sf::Vector2f& to)
{
	*this = Bullet(bulletType);
	setPosition(from);
	sf::Vector2f arrow = to - from;
	rotate(atan2(arrow.y, arrow.x) * 180 / PI + 90);
	float distance = sqrt(arrow.x * arrow.x + arrow.y * arrow.y);
	arrow.x *= bulletSpeed[bulletType] / distance;
	arrow.y *= bulletSpeed[bulletType] / distance;
	m_bulletSpeed = arrow;
}

Bullet::~Bullet()
{

}

sf::ConvexShape Bullet::getCollision()
{
	return m_collision;
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

bool Bullet::isAlive()
{
	return m_isAlive;
}

void Bullet::die()
{
	m_isAlive = false;
}

void Bullet::animate()
{
	move(m_bulletSpeed);
	if (getPosition().x + getTextureRect().width / 2 < 0 ||
		getPosition().y + getTextureRect().height / 2 < 0 ||
		getPosition().x - getTextureRect().width / 2 > screenWidth ||
		getPosition().y + getTextureRect().height / 2 > screenHeight)
	{
		m_isAlive = false;
	}
}

std::string Bullet::getType()
{
	return "Bullet";
}
