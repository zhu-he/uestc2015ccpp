#include "Background.hpp"

sf::Texture Background::m_backgroundTexture;

Background::Background()
{
	setTexture(m_backgroundTexture);
	m_backgroundTextureHeight = getTextureRect().height;
	setPosition(0, -m_backgroundTextureHeight);
	setTextureRect(sf::IntRect(0, 0, getTextureRect().width, getTextureRect().height * 2));
	setColor(sf::Color(128, 128, 128));
}

Background::~Background()
{

}

sf::ConvexShape Background::getCollision()
{
	return m_collision;
}

void Background::loadResources()
{
	m_backgroundTexture.loadFromFile(backgroundImagePath);
	m_backgroundTexture.setRepeated(true);
}

void Background::animate()
{
    move(0, backgroundSpeed);
    if (getPosition().y >= 0)
	{
		setPosition(0, getPosition().y - m_backgroundTextureHeight);
	}
}

std::string Background::getType()
{
	return "Background";
}

bool Background::isAlive()
{
	return true;
}
