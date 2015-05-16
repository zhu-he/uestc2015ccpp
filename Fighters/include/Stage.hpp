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
	private:
		sf::RenderWindow& m_window;
		std::vector<Entity*> entitys;
		void draw();
};

#endif // STAGE_HPP
