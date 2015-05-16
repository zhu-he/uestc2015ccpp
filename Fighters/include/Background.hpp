#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include "Global.hpp"

class Background : public sf::Sprite
{
	public:
		Background();
		virtual ~Background();
		void animate();
	private:
		sf::Texture m_backgroundTexture;
		float m_backgroundTextureHeight;
};

#endif // BACKGROUND_HPP
