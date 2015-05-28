#include "MenuInput.hpp"
#include "Global.hpp"
#include "Font.hpp"

MenuInput::MenuInput()
{
	m_text.setFont(Font::getFont());
	m_inputText.setFont(Font::getFont());
	m_text.setCharacterSize(40);
	m_inputText.setCharacterSize(40);
	m_line.setSize(sf::Vector2f(270, 2));
	m_text.setColor(Font::getColor());
	m_inputText.setColor(Font::getColor());
	m_line.setFillColor(Font::getColor());
}

MenuItemType MenuInput::getMenuItemType()
{
	return Input;
}

void MenuInput::focus()
{
	m_text.setScale(sf::Vector2f(1.3f, 1.3f));
}

void MenuInput::leave()
{
	m_text.setScale(sf::Vector2f(1.0f, 1.0f));
}

void MenuInput::input(int code)
{
	if (code >= 26 && code <= 35)
	{
		m_inputString += (char)(code - 26 + '0');
	}
	else if (code >= 75 && code <= 84)
	{
		m_inputString += (char)(code - 75 + '0');
	}
	else if (code == 50 || code == -1)
	{
		m_inputString += '.';
	}
	else if (code == 59)
	{
		if ((int)m_inputString.size() > 0)
		{
			m_inputString.erase(m_inputString.end() - 1);
		}
	}
	m_inputText.setString(m_inputString);
	m_inputText.setOrigin(0, m_inputText.getLocalBounds().height / 2);
}

std::string MenuInput::getInputString()
{
	return m_inputString;
}

void MenuInput::setString(std::string str)
{
	m_str = str;
	m_text.setString(str);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}

void MenuInput::setOffestY(int offsetY)
{
	m_offsetY = offsetY;
	m_text.setPosition(screenWidth / 2 - 150, offsetY);
	m_inputText.setPosition(screenWidth / 2 - 100, offsetY);
	m_line.setPosition(screenWidth / 2 - 100, offsetY + 32);
}

void MenuInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
	target.draw(m_inputText, states);
	target.draw(m_line, states);
}
