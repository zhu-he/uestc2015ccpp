#ifndef __MENUITEM_HPP__
#define __MENUITEM_HPP__

#include <SFML/Graphics/Drawable.hpp>
#include <string>
#include "Global.hpp"

class MenuItem : public sf::Drawable
{
	public:
		virtual MenuItemType getMenuItemType() = 0;
		virtual void focus() = 0;
		virtual void leave() = 0;
        virtual void input(int code) = 0;
        virtual void setString(std::string str) = 0;
        virtual void setOffestY(int offsetY) = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	protected:
		std::string m_str;
		int m_offsetY;
};

#endif // __MENUITEM_HPP__
