#include "Menu.hpp"
#include "Global.hpp"
#include "Sound.hpp"
#include "MenuText.hpp"
#include "MenuSwitch.hpp"
#include "MenuInput.hpp"

Menu::Menu(MenuStatus menuStatus, float offsetY)
{
	m_font.loadFromFile(fontPath);
	setMenu(menuStatus, offsetY);
}

Menu::~Menu()
{
	for (int i = 0; i < (int)m_menuItems.size(); ++i)
	{
		delete m_menuItems[i];
	}
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < (int)m_menuItems.size(); ++i)
	{
		target.draw(*m_menuItems[i], states);
	}
}

void Menu::next()
{
	m_menuItems[m_menuCursor]->leave();
	m_menuCursor++;
	if (m_menuCursor >= (int)menuString[m_menuStatus].size())
	{
		m_menuCursor = 0;
	}
	m_menuItems[m_menuCursor]->focus();
}

void Menu::previous()
{
	m_menuItems[m_menuCursor]->leave();
	m_menuCursor--;
	if (m_menuCursor < 0)
	{
		m_menuCursor = menuString[m_menuStatus].size() - 1;
	}
	m_menuItems[m_menuCursor]->focus();
}

void Menu::setMenuCursor(int menuCursor)
{
	m_menuCursor = menuCursor;
	refresh();
}

int Menu::getMenuCursor()
{
	return m_menuCursor;
}

MenuStatus Menu::getMenuStatus()
{
	return m_menuStatus;
}

void Menu::bindSwitch(int index, bool (*getter)(), void (*switcher)())
{
	if (m_menuItems[index]->getMenuItemType() == Switch)
	{
		((MenuSwitch*)m_menuItems[index])->bind(getter, switcher);
	}
}

void Menu::toggleSwitch()
{
	if (m_menuItems[m_menuCursor]->getMenuItemType() == Switch)
	{
		((MenuSwitch*)m_menuItems[m_menuCursor])->toggle();
	}
}

void Menu::input(int code)
{
	m_menuItems[m_menuCursor]->input(code);
}

std::string Menu::getInputString(int index)
{
	if (m_menuItems[index]->getMenuItemType() == Input)
	{
		return ((MenuInput*)m_menuItems[index])->getInputString();
	}
	return "";
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
	for (int i = 0; i < (int)m_menuItems.size(); ++i)
	{
		delete m_menuItems[i];
	}
	m_menuItems.clear();
    for (int i = 0; i < (int)menuString[m_menuStatus].size(); ++i)
	{
		if (menuString[m_menuStatus][i].first == Text)
		{
			MenuText* menuText = new MenuText();
			menuText->setString(menuString[m_menuStatus][i].second);
			menuText->setOffestY(m_offsetY + (i - menuString[m_menuStatus].size() / 2.0f) * 60);
			m_menuItems.push_back(menuText);
		}
		else if (menuString[m_menuStatus][i].first == Switch)
		{
			MenuSwitch* menuSwitch = new MenuSwitch();
			menuSwitch->setString(menuString[m_menuStatus][i].second);
			menuSwitch->setOffestY(m_offsetY + (i - menuString[m_menuStatus].size() / 2.0f) * 60);
			m_menuItems.push_back(menuSwitch);
		}
		else if (menuString[m_menuStatus][i].first == Input)
		{
			MenuInput* menuInput = new MenuInput();
			menuInput->setString(menuString[m_menuStatus][i].second);
			menuInput->setOffestY(m_offsetY + (i - menuString[m_menuStatus].size() / 2.0f) * 60);
			m_menuItems.push_back(menuInput);
		}
	}
	m_menuItems[m_menuCursor]->focus();
}
