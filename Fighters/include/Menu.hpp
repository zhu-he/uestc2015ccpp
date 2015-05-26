#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Global.hpp"
#include "MenuItem.hpp"

class Menu : public sf::Drawable
{
	public:
		Menu(MenuStatus menuStatus, float offsetY = screenHeight / 2 + 150);
		virtual ~Menu();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void next();
		void previous();
		MenuStatus getMenuStatus();
		void setMenuCursor(int menuCursor);
		int getMenuCursor();
		void refresh();
		void bindSwitch(int index, bool (*getter)(), void (*switcher)());
		void toggleSwitch();
		void input(int code);
		std::string getInputString(int index);
		void setMenu(MenuStatus menuStatus, float offsetY = screenHeight / 2 + 150);
	private:
		MenuStatus m_menuStatus;
		std::vector<MenuItem*> m_menuItems;
		sf::Font m_font;
		int m_menuCursor;
		float m_offsetY;
};

#endif // __MENU_HPP__
