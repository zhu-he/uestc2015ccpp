#ifndef HERO_HPP
#define HERO_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "SpriteSheet.hpp"
#include "Global.hpp"
#include "Bullet.hpp"
#include "Entity.hpp"
#include "Stage.hpp"

class Hero : public Entity
{
	public:
		Hero();
		virtual ~Hero();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void fire();
		void animate();
		void die();
		void revive();
		void levelup();
		std::string getType();
		bool isAlive();
		bool isFlash();
		void hit();
		static void loadResources();
	private:
		static std::vector<sf::Texture> m_heroTexture;
		static std::vector<sf::Texture> m_heroBlowupTexture;
		int m_heroImageCounter;
		bool m_isAlive;
		Status m_status;
        sf::Clock m_enemyAnimateClock;
		sf::Clock m_lastShootTime;
		sf::Clock m_invincible;
		sf::Clock m_invincibleFlash;
		bool m_isFlash;
		int m_hp;
		int m_level;
};

#endif // HERO_HPP
