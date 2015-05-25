#include "Font.hpp"
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
