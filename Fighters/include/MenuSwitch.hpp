#ifndef __MENUSWITCH_HPP__
#define __MENUSWITCH_HPP__

#include <SFML/Graphics/Text.hpp>
#include "MenuItem.hpp"

class MenuSwitch : public MenuItem
{
	public:
		MenuSwitch();
		MenuItemType getMenuItemType();
		void focus();
		void leave();
        void input(int code);
		void setString(std::string str);
		void setOffestY(int offsetY);
		void bind(bool (*getter)(), void (*switcher)());
		void toggle();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::Text m_text;
		sf::Text m_slashText;
		sf::Text m_onText;
		sf::Text m_offText;
		bool (*m_getter)();
		void (*m_switcher)();
};

#endif // __MENUSWITCH_HPP__
