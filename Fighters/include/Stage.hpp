#ifndef STAGE_HPP
#define STAGE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Global.hpp"
#include "Entity.hpp"

class Entity;

class Stage
{
	public:
		Stage(sf::RenderWindow& window);
		virtual ~Stage();
		void addEntity(Entity* entity);
		void update();
		void gameOver();
		GameStatus getGameStatus();
		int getScore();
		void play();
		void setHpText(int hp);
		void addScore(int score);
	private:
		sf::RenderWindow& m_window;
		std::vector<Entity*> entitys;
		int m_highScore;
		int m_score;
		sf::Font m_font;
		sf::Text m_scoreText;
		sf::Text m_hpText;
		sf::Text m_waitingText;
		sf::Text m_overText;
		sf::Text m_overScoreText;
		sf::Text m_overHighScoreText;
		sf::SoundBuffer m_gameMusicSoundBuffer;
		sf::SoundBuffer m_gameOverSoundBuffer;
		sf::Sound m_gameMusicSound;
		sf::Sound m_gameOverSound;
		sf::Clock m_enemyClock;
		sf::Clock m_waitingFlashClock;
		GameStatus m_gameStatus;
		Entity* m_hero;
		bool m_waitingTextSwitch;
		void draw();
		float cross(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB) const;
		bool hitTest(const sf::ConvexShape& collisionA, const sf::ConvexShape& collisionB) const;
};

#endif // STAGE_HPP
