#ifndef __BULLET_HPP__
#define __BULLET_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "SpriteSheet.hpp"
#include "Global.hpp"
#include "Entity.hpp"

class Bullet : public Entity
{
	public:
		Bullet(BulletType bulletType, const sf::Vector2f& from, const sf::Vector2f& to);
		void animate(sf::Time frameTime);
		void hit();
		void die();
		sf::Vector2f getDirection();
		sf::Color getLightColor();
		BulletType getBulletType();
		std::string getType();
		static void loadResources();
	private:
		static std::vector<sf::Texture> m_bulletTexture;
		BulletType m_bulletType;
		sf::Vector2f m_bulletSpeed;
		sf::Vector2f m_direction;
};

#endif // __BULLET_HPP__
