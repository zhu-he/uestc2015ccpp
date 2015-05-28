#include "MenuSwitch.hpp"
#include "Global.hpp"
#include "Font.hpp"
#include "Shader.hpp"

MenuSwitch::MenuSwitch()
{
	m_text.setFont(Font::getFont());
	m_slashText.setFont(Font::getFont());
	m_onText.setFont(Font::getFont());
	m_offText.setFont(Font::getFont());
	m_text.setColor(Font::getColor());
	m_slashText.setColor(Font::getColor());
	m_onText.setColor(Font::getColor());
	m_offText.setColor(Font::getColor());
	m_text.setCharacterSize(40);
	m_slashText.setCharacterSize(40);
	m_onText.setCharacterSize(30);
	m_offText.setCharacterSize(30);
	m_slashText.setString("/");
	m_onText.setString("ON");
	m_offText.setString("OFF");
	m_slashText.setOrigin(m_slashText.getLocalBounds().width / 2, m_slashText.getLocalBounds().height / 2);
	m_onText.setOrigin(m_onText.getLocalBounds().width / 2, m_onText.getLocalBounds().height / 2);
	m_offText.setOrigin(m_offText.getLocalBounds().width / 2, m_offText.getLocalBounds().height / 2);
}

MenuItemType MenuSwitch::getMenuItemType()
{
	return Switch;
}

void MenuSwitch::focus()
{
	m_text.setScale(sf::Vector2f(1.3f, 1.3f));
}

void MenuSwitch::leave()
{
	m_text.setScale(sf::Vector2f(1.0f, 1.0f));
}

void MenuSwitch::input(int code)
{

}

void MenuSwitch::bind(bool (*getter)(), void (*switcher)())
{
	m_getter = getter;
	m_switcher = switcher;
	if (m_getter())
	{
		m_onText.setScale(sf::Vector2f(1.3f, 1.3f));
		m_offText.setScale(sf::Vector2f(1.0f, 1.0f));
	}
	else
	{
		m_onText.setScale(sf::Vector2f(1.0f, 1.0f));
		m_offText.setScale(sf::Vector2f(1.3f, 1.3f));
	}
}

void MenuSwitch::toggle()
{
	m_switcher();
	if (m_getter())
	{
		m_onText.setScale(sf::Vector2f(1.3f, 1.3f));
		m_offText.setScale(sf::Vector2f(1.0f, 1.0f));
	}
	else
	{
		m_onText.setScale(sf::Vector2f(1.0f, 1.0f));
		m_offText.setScale(sf::Vector2f(1.3f, 1.3f));
	}
}

void MenuSwitch::setString(std::string str)
{
	m_str = str;
	m_text.setString(str);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

void MenuSwitch::setOffestY(int offsetY)
{
	m_offsetY = offsetY;
	m_text.setPosition(screenWidth / 2 - 100, offsetY);
	m_slashText.setPosition(screenWidth / 2 + 70, offsetY);
	m_onText.setPosition(screenWidth / 2 + 20, offsetY);
	m_offText.setPosition(screenWidth / 2 + 120, offsetY);
}

void MenuSwitch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
	target.draw(m_slashText, states);
	target.draw(m_onText, states);
	target.draw(m_offText, states);
}
