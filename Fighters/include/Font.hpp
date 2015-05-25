#ifndef __FONT_HPP__
#define __FONT_HPP__

#include <SFML/Graphics/Font.hpp>

class Font
{
	public:
		static void loadResources();
		static sf::Font& getFont();
	private:
		static sf::Font m_font;
};

#endif // __FONT_HPP__
