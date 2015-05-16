#ifndef HERO_HPP
#define HERO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "SpriteSheet.hpp"
#include "Global.hpp"

class Hero : public sf::Sprite
{
	public:
		Hero();
		virtual ~Hero();
		void moveLeft();
		void moveRight();
		void fire();
		void animate();
		void die();
	private:
		SpriteSheet m_spriteSheet;
		std::vector<sf::Texture> m_heroTexture;
		std::vector<sf::Texture> m_heroBlowupTexture;
		int m_heroImagePos;
};

#endif // HERO_HPP
