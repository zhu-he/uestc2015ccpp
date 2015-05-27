#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Global.hpp"
#include "Shader.hpp"

class Background : public sf::Drawable
{
	public:
		Background();
		virtual ~Background();
		void animate();
		static void loadResources();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		static sf::Texture m_backgroundTexture;
		sf::Sprite m_background1;
		sf::Sprite m_background2;
};

#endif // BACKGROUND_HPP
