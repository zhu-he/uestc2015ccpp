#ifndef STAGE_HPP
#define STAGE_HPP

#include <SFML/Graphics.hpp>
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
		void setHpText(int hp);
	private:
		sf::RenderWindow& m_window;
		std::vector<Entity*> entitys;
		int m_score;
		sf::Font m_font;
		sf::Text m_scoreText;
		sf::Text m_hpText;
		Status m_status;
		void draw();
		void addScore(int score);
};

#endif // STAGE_HPP
