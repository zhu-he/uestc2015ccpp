#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Global.hpp"
#include "Entity.hpp"

class Background : public Entity
{
	public:
		Background();
		virtual ~Background();
		void animate();
		bool isAlive();
		sf::ConvexShape getCollision();
		std::string getType();
		static void loadResources();
	private:
		static sf::Texture m_backgroundTexture;
		float m_backgroundTextureHeight;
};

#endif // BACKGROUND_HPP
