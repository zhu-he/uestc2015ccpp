#include "Bullet.hpp"

Bullet::Bullet()
{
    for (int i = 0; i < (int)bulletImage.size(); ++i)
	{
        m_bulletTexture.push_back(SpriteSheet::getTexture(bulletImage[i]));
	}
	setTexture(m_bulletTexture[1]);
	setOrigin(getTextureRect().width / 2, getTextureRect().height);
	m_isAlive = true;
}

Bullet::~Bullet()
{

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
	move(0, -bulletSpeed);
	if (getPosition().y < 0)
	{
		m_isAlive = false;
	}
}

std::string Bullet::getType()
{
	return "Bullet";
}
