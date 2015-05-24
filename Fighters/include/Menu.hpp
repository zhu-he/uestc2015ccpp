#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Global.hpp>

class Menu : public sf::Drawable
{
	public:
		Menu(MenuStatus menuStatus, float offsetY);
		virtual ~Menu();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void next();
		void previous();
		MenuStatus getMenuStatus();
		void setMenuCursor(int menuCursor);
		int getMenuCursor();
		void refresh();
		void setMenu(MenuStatus menuStatus, float offsetY);
	private:
		MenuStatus m_menuStatus;
		std::vector<sf::Text> m_menuItems;
		sf::Font m_font;
		int m_menuCursor;
		float m_offsetY;
		void highlight();
		void lowlight();
};

#endif // __MENU_HPP__