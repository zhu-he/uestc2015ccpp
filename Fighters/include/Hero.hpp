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
		void fire();
		void animate();
		void die();
		void revive();
		sf::ConvexShape getCollision();
		std::string getType();
		bool isAlive();
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
		sf::SoundBuffer m_bulletSoundBuffer;
		sf::Sound m_bulletSound;
		bool m_isFlash;
		int m_hp;
};

#endif // HERO_HPP
