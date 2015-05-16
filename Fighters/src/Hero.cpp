#include "Hero.hpp"

Hero::Hero()
{
	m_spriteSheet.loadFromFile(packPath);
    for (int i = 0; i < (int)heroImage.size(); ++i)
	{
		m_heroTexture.push_back(m_spriteSheet.getTexture(heroImage[i]));
	}
    for (int i = 0; i < (int)heroBlowupImage.size(); ++i)
	{
		m_heroBlowupTexture.push_back(m_spriteSheet.getTexture(heroBlowupImage[i]));
	}
	setTexture(m_heroTexture[0]);
	m_heroImagePos = 0;
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	setPosition(screenWidth / 2, screenHeight - getTextureRect().height / 2);
}

Hero::~Hero()
{

}

void Hero::moveLeft()
{
	if (getPosition().x - getTextureRect().width / 2 > 0)
	{
		move(-heroSpeed, 0);
	}
}

void Hero::moveRight()
{
	if (getPosition().x + getTextureRect().width / 2 < screenWidth)
	{
		move(heroSpeed, 0);
	}
}

void Hero::animate()
{
	m_heroImagePos = (m_heroImagePos + 1) % heroImage.size();
	setTexture(m_heroTexture[m_heroImagePos]);
}

void Hero::fire()
{

}
