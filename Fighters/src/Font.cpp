#include "Font.hpp"
#include "Shader.hpp"
#include "Global.hpp"

sf::Font Font::m_font;

void Font::loadResources()
{
	m_font.loadFromFile(fontPath);
}

sf::Font& Font::getFont()
{
	return m_font;
}

sf::Color Font::getColor()
{
	if (Shader::isAvailable())
	{
		return textColor;
	}
	else
	{
		return textColorNoShader;
	}
}
