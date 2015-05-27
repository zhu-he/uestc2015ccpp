#ifndef __STAGE_HPP__
#define __STAGE_HPP__

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
		Stage(sf::RenderWindow& window, Background& background);
		virtual ~Stage();
		virtual void addEntity(Entity* entity);
		GameStatus getGameStatus();
		virtual void play();
		virtual void setHpText(int hp);
		void addScore(int score);
		void drawLight(sf::Vector2f lightPosition, sf::Color color, float lightAttenuation);
	protected:
		sf::RenderWindow& m_window;
		Entity* m_hero;
		Entity* m_controlHero;
		std::vector<Entity*> m_entitys;
		void animate();
		virtual void draw();
		virtual bool update();
		virtual void gameOver();
		virtual void dieEntity(Entity* entity);
		virtual void hitEntity(Entity* entity);
		virtual void init();
		virtual void pause();
		virtual void resume();
		virtual void bombup(Entity* hero);
		virtual void levelup(Entity* hero);
		sf::Texture m_bombTexture;
		sf::Sprite m_bombSprite;
		bool m_isBombing;
		sf::Clock m_bombClock;
		GameStatus m_gameStatus;
		sf::Text m_overText;
		sf::Text m_overScoreText;
		sf::Text m_overHighScoreText;
		sf::Text m_scoreText;
		sf::Text m_hpText;
	private:
		std::ifstream m_highScoreIfstream;
		std::ofstream m_highScoreOfstream;
		int m_highScore;
		int m_score;
		sf::Clock m_enemyClock[3];
		sf::Clock m_ufoClock;
		sf::Shader* m_lightShader;
		sf::Shader* m_shadowShader;
		sf::RenderStates m_lightRenderStates;
		sf::RenderStates m_shadowRenderStates;
		sf::RenderTexture m_lightRenderTexture;
		sf::RenderTexture m_shadowRenderTexture;
		sf::Sprite m_lightSprite;
		sf::Sprite m_shadowSprite;
		Background& m_background;
		Menu m_pausedMenu;
		bool m_waitingTextSwitch;
		bool m_isRunning;
		virtual sf::Vector2f getHeroPosition();
		virtual void useBomb();
		virtual bool isOver();
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
		virtual void restart();
		void drawShadow(sf::Vector2f lightPosition, float shadowAttenuation);
		float cross(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB) const;
		bool hitTest(const sf::ConvexShape& collisionA, const sf::ConvexShape& collisionB) const;
};

#endif // __STAGE_HPP__
