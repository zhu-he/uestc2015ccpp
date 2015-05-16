#include "Stage.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

Stage::Stage(sf::RenderWindow& window) : m_window(window)
{

}

Stage::~Stage()
{

}

void Stage::addEntity(Entity* entity)
{
	entitys.push_back(entity);
	entity->m_stage = this;
}

void Stage::draw()
{
	m_window.clear();
	for (Entity* entity : entitys)
	{
		if (entity->isAlive())
		{
			entity->animate();
			m_window.draw(*entity);
		}
	}
	m_window.display();
}

void Stage::update()
{
	for (int i = 0; i < (int)entitys.size() - 1; ++i)
	{
		if (!entitys[i]->isAlive() || entitys[i]->getType() == "Background")
		{
			continue;
		}
		for (int j = i + 1; j < (int)entitys.size(); ++j)
		{
			if (!entitys[j]->isAlive() || entitys[j]->getType() == "Background" || entitys[i]->getType() == entitys[j]->getType())
			{
				continue;
			}
			if (entitys[i]->getGlobalBounds().intersects(entitys[j]->getGlobalBounds()))
			{
				if (entitys[i]->getType() == "Enemy" && entitys[j]->getType() == "Bullet")
				{
					((Enemy*)entitys[i])->hit();
					((Bullet*)entitys[j])->die();
				}
				else if (entitys[i]->getType() == "Bullet" && entitys[j]->getType() == "Enemy")
				{
					((Bullet*)entitys[i])->die();
					((Enemy*)entitys[j])->hit();
				}
			}
		}
	}
    draw();
}
