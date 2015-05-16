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
		bool isAlive();
	private:
		std::vector<sf::Texture> m_enemyTexture;
		std::vector<sf::Texture> m_enemyDownTexture;
		sf::Texture m_enemyHitTexture;
		int m_enemyImagePos;
		bool m_isAlive;
		int m_hp;
		float m_speed;
		sf::SoundBuffer m_enemyDownSoundBuffer;
		sf::Sound m_enemyDownSound;
		int m_status;
		static const int Normal = 0;
		static const int Hit = 1;
		static const int Die = 2;
};

#endif // ENEMY_HPP
