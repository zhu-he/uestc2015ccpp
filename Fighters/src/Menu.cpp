#include "Menu.hpp"
#include "Global.hpp"

extern bool musicSwitch;
extern bool sfxSwitch;

Menu::Menu(MenuStatus menuStatus, float offsetY)
{
	m_font.loadFromFile(fontPath);
	setMenu(menuStatus, offsetY);
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < (int)m_menuItems.size(); ++i)
	{
		target.draw(m_menuItems[i], states);
	}
}

void Menu::next()
{
	lowlight();
	m_menuCursor++;
	if (m_menuCursor >= (int)menuString[m_menuStatus].size())
	{
		m_menuCursor = 0;
	}
	highlight();
}

void Menu::previous()
{
	lowlight();
	m_menuCursor--;
	if (m_menuCursor < 0)
	{
		m_menuCursor = menuString[m_menuStatus].size() - 1;
	}
	highlight();
}

void Menu::highlight()
{
	m_menuItems[m_menuCursor].setColor(sf::Color::White);
	m_menuItems[m_menuCursor].setCharacterSize(50);
	m_menuItems[m_menuCursor].setPosition(screenWidth / 2 - m_menuItems[m_menuCursor].getLocalBounds().width / 2, m_offsetY + (m_menuCursor - menuString[m_menuStatus].size() / 2.0f) * 60 - 5);
}

void Menu::lowlight()
{
	m_menuItems[m_menuCursor].setColor(textColor);
	m_menuItems[m_menuCursor].setCharacterSize(40);
	m_menuItems[m_menuCursor].setPosition(screenWidth / 2 - m_menuItems[m_menuCursor].getLocalBounds().width / 2, m_offsetY + (m_menuCursor - menuString[m_menuStatus].size() / 2.0f) * 60);
}

int Menu::getMenuCursor()
{
	return m_menuCursor;
}

MenuStatus Menu::getMenuStatus()
{
	return m_menuStatus;
}

void Menu::setMenu(MenuStatus menuStatus, float offsetY)
{
	m_menuStatus = menuStatus;
	m_offsetY = offsetY;
	m_menuCursor = 0;
	refresh();
}

void Menu::refresh()
{
	m_menuItems.clear();
    for (int i = 0; i < (int)menuString[m_menuStatus].size(); ++i)
	{
		sf::Text text;
		text.setFont(m_font);
		text.setCharacterSize(40);
		if (menuString[m_menuStatus][i] == "Music")
		{
			text.setString(menuString[m_menuStatus][i] + (musicSwitch ? ": ON" : ": OFF"));
		}
		else if (menuString[m_menuStatus][i] == "SFX")
		{
			text.setString(menuString[m_menuStatus][i] + (sfxSwitch ? ": ON" : ": OFF"));
		}
		else
		{
			text.setString(menuString[m_menuStatus][i]);
		}
		text.setColor(textColor);
		text.setPosition(screenWidth / 2 - text.getLocalBounds().width / 2, m_offsetY + (i - menuString[m_menuStatus].size() / 2.0f) * 60);
		m_menuItems.push_back(text);
	}
	highlight();
}
