#ifndef __HERO_HPP__
#define __HERO_HPP__

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
		void moveLeft(sf::Time frameTime);
		void moveRight(sf::Time frameTime);
		void moveUp(sf::Time frameTime);
		void moveDown(sf::Time frameTime);
		void fire();
		void animate(sf::Time frameTime);
		void die();
		void revive();
		void levelup();
		void bombup();
		int getBomb();
		void useBomb();
		void resetShootTime();
		virtual std::string getType();
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
        sf::Clock m_enemyAnimateClock;
		sf::Clock m_lastShootTime;
		bool m_isFlash;
		int m_bomb;
		int m_level;

};

#endif // __HERO_HPP__
