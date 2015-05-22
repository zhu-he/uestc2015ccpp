#include "Ufo.hpp"
#include "SpriteSheet.hpp"

sf::Texture Ufo::m_ufoTexture[2];
sf::SoundBuffer Ufo::m_ufoSoundBuffer[2];
sf::Sound Ufo::m_ufoSound[2];

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

Ufo::~Ufo()
{

}

void Ufo::animate()
{
	move(0, ufoSpeed);
	if (getPosition().y > screenHeight + getTextureRect().height)
	{
        m_isAlive = false;
	}
}

bool Ufo::isAlive()
{
	return m_isAlive;
}

void Ufo::die()
{
	m_isAlive = false;
	m_ufoSound[m_ufoType].play();
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
	for (int i = 0; i < (int)ufoSoundPath.size(); ++i)
	{
		m_ufoSoundBuffer[i].loadFromFile(ufoSoundPath[i]);
		m_ufoSound[i].setBuffer(m_ufoSoundBuffer[i]);
	}
}
