#ifndef __MENUINPUT_HPP__
#define __MENUINPUT_HPP__

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <string>
#include "MenuItem.hpp"

class MenuInput : public MenuItem
{
	public:
		MenuInput();
		MenuItemType getMenuItemType();
		void focus();
		void leave();
        void input(int code);
        std::string getInputString();
		void setString(std::string str);
		void setOffestY(int offsetY);
		void bind(bool (*getter)(), void (*switcher)());
		void toggle();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::Text m_text;
		sf::Text m_inputText;
		sf::RectangleShape m_line;
		std::string m_inputString;
};

#endif // __MENUINPUT_HPP__
