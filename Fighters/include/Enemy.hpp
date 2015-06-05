#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>
#include "SpriteSheet.hpp"
#include "Global.hpp"
#include "Entity.hpp"
#include "PausableClock.hpp"

class Enemy : public Entity
{
	public:
		Enemy(const int& enemyType);
		void animate(sf::Time frameTime);
		void die();
		void hit();
		void fire(const sf::Vector2f& heroPosition);
		std::string getType();
		Status getStatus();
		int getEnemyType();
		static void loadResources();
	private:
		static std::vector<sf::Texture> m_enemyTexture[3];
		static std::vector<sf::Texture> m_enemyDownTexture[3];
		static sf::Texture m_enemyHitTexture[3];
        PausableClock m_enemyAnimateClock;
        PausableClock m_lastShootTime;
		int m_enemyImageCounter;
		int m_hp;
		float m_speed;
		Status m_status;
		int m_enemyType;
};

#endif // __ENEMY_HPP__
