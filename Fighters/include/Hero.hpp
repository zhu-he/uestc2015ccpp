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
		void bombup();
		int getBomb();
		void useBomb();
		void resetShootTime();
		virtual std::string getType();
		bool isAlive();
		bool isFlash();
		virtual void hit();
		static void loadResources();
	protected:
		sf::Color m_color;
		Status m_status;
		sf::Clock m_invincible;
		sf::Clock m_invincibleFlash;
		int m_hp;
	private:
		static std::vector<sf::Texture> m_heroTexture;
		static std::vector<sf::Texture> m_heroBlowupTexture;
		int m_heroImageCounter;
		bool m_isAlive;
        sf::Clock m_enemyAnimateClock;
		sf::Clock m_lastShootTime;
		bool m_isFlash;
		int m_bomb;
		int m_level;

};

#endif // HERO_HPP
