#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "SpriteSheet.hpp"
#include "Global.hpp"
#include "Entity.hpp"

class Bullet : public Entity
{
	public:
		Bullet();
		virtual ~Bullet();
		void animate();
		bool isAlive();
		void die();
		std::string getType();
		static void loadResources();
	private:
		static std::vector<sf::Texture> m_bulletTexture;
		bool m_isAlive;
};

#endif // BULLET_HPP
