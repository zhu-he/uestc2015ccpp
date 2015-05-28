#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Global.hpp"
#include "Shader.hpp"

class Background : public sf::Drawable
{
	public:
		Background();
		void animate();
		static void loadResources();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		static sf::Texture m_backgroundTexture;
		sf::Sprite m_background1;
		sf::Sprite m_background2;
};

#endif // __BACKGROUND_HPP__
