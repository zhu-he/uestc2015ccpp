#ifndef STAGE_HPP
#define STAGE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "Global.hpp"
#include "Menu.hpp"
#include "Entity.hpp"
#include "Background.hpp"

class Entity;

class Stage
{
	public:
		Stage(sf::RenderWindow& window);
		virtual ~Stage();
		virtual void addEntity(Entity* entity);
		void setBackground(Background* background);
		virtual bool update();
		virtual void gameOver();
		GameStatus getGameStatus();
		int getScore();
		virtual void play();
		virtual void useBomb();
		virtual void setHpText(int hp);
		void addScore(int score);
		void drawShadow(sf::Vector2f lightPosition, float shadowAttenuation);
		void drawLight(sf::Vector2f lightPosition, sf::Color color, float lightAttenuation);
	protected:
		sf::RenderWindow& m_window;
		std::vector<Entity*> m_entitys;
		std::ifstream m_highScoreIfstream;
		std::ofstream m_highScoreOfstream;
		int m_highScore;
		int m_score;
		sf::Text m_scoreText;
		sf::Text m_hpText;
		sf::Text m_waitingText;
		sf::Text m_overText;
		sf::Text m_overScoreText;
		sf::Text m_overHighScoreText;
		sf::Clock m_enemyClock[3];
		sf::Clock m_ufoClock;
		sf::Clock m_waitingFlashClock;
		sf::Clock m_bombClock;
		sf::Shader* m_lightShader;
		sf::Shader* m_shadowShader;
		sf::RenderStates m_lightRenderStates;
		sf::RenderStates m_shadowRenderStates;
		sf::RenderTexture m_lightRenderTexture;
		sf::RenderTexture m_shadowRenderTexture;
		sf::Sprite m_lightSprite;
		sf::Sprite m_shadowSprite;
		sf::Texture m_bombTexture;
		sf::Sprite m_bombSprite;
		GameStatus m_gameStatus;
		Entity* m_hero;
		Entity* m_controlHero;
		Background* m_background;
		Menu m_pausedMenu;
		bool m_waitingTextSwitch;
		bool m_isBombing;
		bool m_isRunning;
		void animate();
		virtual bool isOver();
		virtual void pause();
		virtual void resume();
		virtual void draw();
		virtual void fire();
		virtual void noFire();
		virtual void moveLeft();
		virtual void moveRight();
		virtual void moveUp();
		virtual void moveDown();
		virtual void moveNoLeft();
		virtual void moveNoRight();
		virtual void moveNoUp();
		virtual void moveNoDown();
		virtual void bombup(Entity* hero);
		virtual void init();
		virtual void restart();
		virtual void hitEntity(Entity* entity);
		virtual void dieEntity(Entity* entity);
		float cross(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB) const;
		bool hitTest(const sf::ConvexShape& collisionA, const sf::ConvexShape& collisionB) const;
};

#endif // STAGE_HPP
