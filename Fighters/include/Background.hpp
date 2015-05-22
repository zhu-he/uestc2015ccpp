#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Global.hpp"

class Background : public sf::Sprite
{
	public:
		Background();
		virtual ~Background();
		void animate();
		static void loadResources();
	private:
		static sf::Texture m_backgroundTexture;
		float m_backgroundTextureHeight;
};

#endif // BACKGROUND_HPP
