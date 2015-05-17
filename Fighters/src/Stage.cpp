#include "Stage.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

Stage::Stage(sf::RenderWindow& window) : m_window(window)
{
	m_score = 0;
	m_font.loadFromFile(fontPath);
	m_scoreText.setFont(m_font);
	m_scoreText.setString("Score: 0");
	m_scoreText.setCharacterSize(24);
	m_scoreText.setColor(sf::Color::Black);
	m_scoreText.setPosition(5, 5);
	m_scoreText.setStyle(sf::Text::Bold);
}

Stage::~Stage()
{

}

void Stage::addEntity(Entity* entity)
{
	entitys.push_back(entity);
	entity->m_stage = this;
}

void Stage::addScore(int score)
{
	m_score += score;
	m_scoreText.setString("Score: " + std::to_string(m_score));
}

void Stage::draw()
{
	m_window.clear();
	for (Entity* entity : entitys)
	{
		entity->animate();
		m_window.draw(*entity);
	}
	m_window.draw(m_scoreText);
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
				if (entitys[i]->getType() == "Enemy" && entitys[j]->getType() == "Bullet" && ((Enemy*)entitys[i])->getStatus() != Dying)
				{
					((Enemy*)entitys[i])->hit();
					((Bullet*)entitys[j])->die();
				}
				else if (entitys[i]->getType() == "Bullet" && entitys[j]->getType() == "Enemy" && ((Enemy*)entitys[j])->getStatus() != Dying)
				{
					((Bullet*)entitys[i])->die();
					((Enemy*)entitys[j])->hit();
				}
			}
		}
	}
	for (std::vector<Entity*>::iterator it = entitys.begin(); it != entitys.end(); ++it)
	{
		if (!(*it)->isAlive())
		{
			if ((*it)->getType() == "Enemy")
			{
				addScore(enemyScore[((Enemy*)(*it))->getEnemyType()]);
			}
			entitys.erase(it);
			it--;
		}
	}
    draw();
}
