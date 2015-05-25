#include "MenuText.hpp"
#include "Font.hpp"

MenuText::MenuText()
{
	m_text.setCharacterSize(40);
	m_text.setFont(Font::getFont());
}

MenuText::~MenuText()
{

}

MenuItemType MenuText::getMenuItemType()
{
	return Text;
}

void MenuText::focus()
{
	m_text.setScale(sf::Vector2f(1.3f, 1.3f));
}

void MenuText::leave()
{
	m_text.setScale(sf::Vector2f(1.0f, 1.0f));
}

void MenuText::input(int code)
{

}

void MenuText::setString(std::string str)
{
	m_str = str;
	m_text.setString(str);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

void MenuText::setOffestY(int offsetY)
{
	m_offsetY = offsetY;
	m_text.setPosition(screenWidth / 2, offsetY);
}

void MenuText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}
