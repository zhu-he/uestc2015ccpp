#include "Stage.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Hero.hpp"

Stage::Stage(sf::RenderWindow& window) : m_window(window)
{
	m_score = 0;
	m_font.loadFromFile(fontPath);
	m_scoreText.setFont(m_font);
	m_scoreText.setString("Score: 0");
	m_scoreText.setCharacterSize(24);
	m_scoreText.setColor(sf::Color::Black);
	m_scoreText.setPosition(10, 5);
	m_scoreText.setStyle(sf::Text::Bold);
	m_hpText.setFont(m_font);
	m_hpText.setString(L"♥♥♥");
	m_hpText.setCharacterSize(30);
	m_hpText.setColor(sf::Color::Red);
	m_hpText.setStyle(sf::Text::Bold);
	m_hpText.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
	m_status = Normal;
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

void Stage::setHpText(int hp)
{
	wchar_t heartString[4];
	for (int i = 0; i < hp; ++i)
	{
		heartString[i] = L'♥';
	}
	heartString[hp] = 0;
	m_hpText.setString(heartString);
	m_hpText.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
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
	m_window.draw(m_hpText);
	m_window.display();
}

void Stage::gameOver()
{
    m_status = Over;
}

void Stage::update()
{
	if (m_status == Over)
	{
		return;
	}
	for (Entity* entityA : entitys)
	{
		for (Entity* entityB : entitys)
		{
			if (entityA->getGlobalBounds().intersects(entityB->getGlobalBounds()))
			{
				if (entityA->getType() == "Enemy" && entityB->getType() == "Bullet" && ((Enemy*)entityA)->getStatus() != Dying)
				{
					((Enemy*)entityA)->hit();
					((Bullet*)entityB)->die();
				}
				else if (entityA->getType() == "Enemy" && entityB->getType() == "Hero" && ((Enemy*)entityA)->getStatus() != Dying)
				{
					((Enemy*)entityA)->die();
					((Hero*)entityB)->hit();
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
			else if ((*it)->getType() == "Hero")
			{
				gameOver();
			}
			entitys.erase(it);
			it--;
		}
	}
    draw();
}
