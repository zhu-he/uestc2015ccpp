#ifndef __MENUTEXT_HPP__
#define __MENUTEXT_HPP__

#include <SFML/Graphics/Text.hpp>
#include <MenuItem.hpp>

class MenuText : public MenuItem
{
	public:
		MenuText();
		virtual ~MenuText();
		MenuItemType getMenuItemType();
		void focus();
		void leave();
        void input(int code);
		void setString(std::string str);
		void setOffestY(int offsetY);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::Text m_text;
};

#endif // __MENUTEXT_HPP__
