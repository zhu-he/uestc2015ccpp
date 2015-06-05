#include "Ufo.hpp"
#include "SpriteSheet.hpp"
#include "Sound.hpp"

sf::Texture Ufo::m_ufoTexture[2];

Ufo::Ufo(UfoType ufoType)
{
	m_ufoType = ufoType;
	setTexture(m_ufoTexture[ufoType]);
	setOrigin(getTextureRect().width / 2, getTextureRect().height - 20);
	setPosition(rand() % (screenWidth - getTextureRect().width) + getTextureRect().width, -getTextureRect().height);
	m_isAlive = true;
	switch (ufoType)
	{
	case Weapon:
		m_collision.setPointCount(4);
		m_collision.setPoint(0, sf::Vector2f(15, 65));
		m_collision.setPoint(1, sf::Vector2f(20, 85));
		m_collision.setPoint(2, sf::Vector2f(54, 75));
		m_collision.setPoint(3, sf::Vector2f(49, 55));
		m_collision.setFillColor(sf::Color(255, 0, 0, 100));
		break;
	case Bomb:
		m_collision.setPointCount(4);
		m_collision.setPoint(0, sf::Vector2f(10, 72));
		m_collision.setPoint(1, sf::Vector2f(2, 90));
		m_collision.setPoint(2, sf::Vector2f(45, 105));
		m_collision.setPoint(3, sf::Vector2f(53, 87));
		m_collision.setFillColor(sf::Color(255, 0, 0, 100));
		break;
	default:
		break;
	}
}

void Ufo::animate(sf::Time frameTime)
{
	move(0, ufoSpeed * frameTime.asSeconds());
	if (getPosition().y > screenHeight + getTextureRect().height)
	{
        m_isAlive = false;
	}
}

void Ufo::hit()
{

}

void Ufo::die()
{
	m_isAlive = false;
	Sound::playUfoSound(m_ufoType);
}

UfoType Ufo::getUfoType()
{
	return m_ufoType;
}

std::string Ufo::getType()
{
	return "Ufo";
}

void Ufo::loadResources()
{
	for (int i = 0; i < (int)ufoImage.size(); ++i)
	{
		m_ufoTexture[i] = SpriteSheet::getTexture(ufoImage[i]);
	}
}

sf::Color Ufo::getLightColor()
{
	switch (m_ufoType)
	{
	case Weapon:
		return sf::Color::Blue;
	case Bomb:
		return sf::Color::Red;
	default:
		return sf::Color::Transparent;
	}
}
