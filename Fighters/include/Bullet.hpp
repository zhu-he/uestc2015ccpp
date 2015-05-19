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
		Bullet(BulletType bulletType, const sf::Vector2f& from, const sf::Vector2f& to);
		virtual ~Bullet();
		void animate();
		bool isAlive();
		void die();
		BulletType getBulletType();
		sf::ConvexShape getCollision();
		std::string getType();
		static void loadResources();
	private:
		static std::vector<sf::Texture> m_bulletTexture;
		bool m_isAlive;
		BulletType m_bulletType;
		sf::Vector2f m_bulletSpeed;
};

#endif // BULLET_HPP
