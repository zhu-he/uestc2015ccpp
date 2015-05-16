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
		std::string getType();
		bool isAlive();
	private:
		std::vector<sf::Texture> m_heroTexture;
		std::vector<sf::Texture> m_heroBlowupTexture;
		int m_heroImagePos;
		bool m_isAlive;
		sf::Clock m_lastShootTime;
		sf::SoundBuffer m_bulletSoundBuffer;
		sf::Sound m_bulletSound;
};

#endif // HERO_HPP
