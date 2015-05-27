#include "Background.hpp"

sf::Texture Background::m_backgroundTexture;

Background::Background()
{
	m_background1.setTexture(m_backgroundTexture);
	m_background1.setPosition(0, -screenHeight);
	m_background2.setTexture(m_backgroundTexture);
	m_background2.setPosition(0, 0);
}

Background::~Background()
{

}

void Background::loadResources()
{
	m_backgroundTexture.loadFromFile(backgroundImagePath);
}

void Background::animate()
{
	if (Shader::isAvailable())
	{
		m_background1.setColor(sf::Color(128, 128, 128));
		m_background2.setColor(sf::Color(128, 128, 128));
	}
	else
	{
		m_background1.setColor(sf::Color::White);
		m_background2.setColor(sf::Color::White);
	}
	m_background1.move(0, backgroundSpeed);
	m_background2.move(0, backgroundSpeed);
    if (m_background1.getPosition().y >= 0)
	{
		m_background1.setPosition(0, m_background1.getPosition().y - screenHeight);
		m_background2.setPosition(0, m_background2.getPosition().y - screenHeight);
	}
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (Shader::isAvailable())
	{
		target.draw(m_background1, Shader::getInvertShader());
		target.draw(m_background2, Shader::getInvertShader());
	}
	else
	{
		target.draw(m_background1);
		target.draw(m_background2);
	}
}
