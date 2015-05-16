#include "Stage.hpp"

Stage::Stage(sf::RenderWindow& window) : m_window(window)
{

}

Stage::~Stage()
{

}

void Stage::addEntity(Entity& entity)
{
	entitys.push_back(entity);
	entity.m_stage = this;
}

void Stage::draw()
{
	m_window.clear();
	for (Entity& entity : entitys)
	{
		if (entity.isAlive())
		{
			entity.animate();
			m_window.draw(entity);
		}
	}
	m_window.display();
}

void Stage::update()
{

    draw();
}
