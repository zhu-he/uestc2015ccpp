#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <vector>
#include "SpriteSheet.hpp"
#include "Global.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
	public:
		Enemy(const int& enemyType);
		virtual ~Enemy();
		void animate();
		void die();
		void hit();
		std::string getType();
		Status getStatus();
		bool isAlive();
		int getEnemyType();
		static void loadResources();
	private:
		static std::vector<sf::Texture> m_enemyTexture[3];
		static std::vector<sf::Texture> m_enemyDownTexture[3];
		static sf::Texture m_enemyHitTexture[3];
		static sf::SoundBuffer m_enemyDownSoundBuffer[3];
		static sf::Sound m_enemyDownSound[3];
        sf::Clock m_enemyAnimateClock;
		int m_enemyImageCounter;
		bool m_isAlive;
		int m_hp;
		float m_speed;
		Status m_status;
		int m_enemyType;
};

#endif // ENEMY_HPP