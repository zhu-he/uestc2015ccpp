#include "Stage.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Hero.hpp"

Stage::Stage(sf::RenderWindow& window) : m_window(window)
{
	m_score = 0;
	m_font.loadFromFile(fontPath);
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(24);
	m_scoreText.setColor(sf::Color::Black);
	m_scoreText.setPosition(10, 5);
	m_scoreText.setStyle(sf::Text::Bold);
	m_hpText.setFont(m_font);
	m_hpText.setCharacterSize(30);
	m_hpText.setColor(sf::Color::Red);
	m_hpText.setStyle(sf::Text::Bold);
	m_hpText.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
	m_waitingText.setFont(m_font);
	m_waitingText.setString("Press any key to start");
	m_waitingText.setCharacterSize(30);
	m_waitingText.setColor(sf::Color::Black);
	m_waitingText.setStyle(sf::Text::Bold);
	m_waitingText.setPosition(screenWidth / 2 - m_waitingText.getLocalBounds().width / 2, screenHeight / 2 - m_waitingText.getLocalBounds().height / 2);
	m_overScoreText.setFont(m_font);
	m_overScoreText.setCharacterSize(40);
	m_overScoreText.setColor(sf::Color::Black);
	m_overScoreText.setStyle(sf::Text::Bold);
	m_overHighScoreText.setFont(m_font);
	m_overHighScoreText.setCharacterSize(40);
	m_overHighScoreText.setColor(sf::Color::Black);
	m_overHighScoreText.setStyle(sf::Text::Bold);
	m_overText.setFont(m_font);
	m_overText.setString("Game Over");
	m_overText.setCharacterSize(40);
	m_overText.setColor(sf::Color::Black);
	m_overText.setStyle(sf::Text::Bold);
	m_overText.setPosition(screenWidth / 2 - m_overText.getLocalBounds().width / 2, screenHeight / 2 - m_overText.getLocalBounds().height * 4);
	m_gameStatus = Waiting;
	m_gameMusicSoundBuffer.loadFromFile(gameMusicPath);
	m_gameOverSoundBuffer.loadFromFile(gameOverPath);
	m_gameMusicSound.setBuffer(m_gameMusicSoundBuffer);
	m_gameOverSound.setBuffer(m_gameOverSoundBuffer);
	m_gameMusicSound.setLoop(true);
	m_gameMusicSound.play();
	m_waitingTextSwitch = true;
	m_highScore = 0;
}

Stage::~Stage()
{

}

void Stage::addEntity(Entity* entity)
{
	entitys.push_back(entity);
	entity->m_stage = this;
	if (entity->getType() == "Hero")
	{
		m_hero = entity;
	}
}

void Stage::addScore(int score)
{
	m_score += score;
	m_scoreText.setString("Score: " + std::to_string(m_score));
}

GameStatus Stage::getGameStatus()
{
	return m_gameStatus;
}

int Stage::getScore()
{
	return m_score;
}

void Stage::setHpText(int hp)
{
	if (hp < 0)
	{
		hp = 0;
	}
	wchar_t heartString[4];
	for (int i = 0; i < hp; ++i)
	{
		heartString[i] = L'♥';
	}
	heartString[hp] = 0;
	m_hpText.setString(heartString);
	m_hpText.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
}

void Stage::play()
{
	m_gameMusicSound.play();
	m_score = 0;
	m_scoreText.setString("Score: 0");
	setHpText(heroHp);
	m_gameStatus = Playing;
	((Hero*)m_hero)->revive();
	m_enemyClock.restart();
	for (std::vector<Entity*>::iterator it = entitys.begin(); it != entitys.end(); ++it)
	{
		if ((*it)->getType() != "Background" && (*it)->getType() != "Hero")
		{
			delete *it;
			entitys.erase(it);
			it--;
		}
	}
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
			// m_window.draw(entity->getCollision());
		}
	}
	if (m_gameStatus == Playing)
	{
		m_window.draw(m_scoreText);
		m_window.draw(m_hpText);
	}
	if (m_gameStatus == Waiting)
	{
		if (m_waitingFlashClock.getElapsedTime() >= sf::seconds(waitingFlashInterval))
		{
			m_waitingTextSwitch = !m_waitingTextSwitch;
			m_waitingFlashClock.restart();
		}
		if (m_waitingTextSwitch)
		{
			m_window.draw(m_waitingText);
		}
	}
	else if (m_gameStatus == Over)
	{
		m_window.draw(m_overText);
		m_window.draw(m_overScoreText);
		m_window.draw(m_overHighScoreText);
	}
	m_window.display();
}

void Stage::gameOver()
{
    m_gameStatus = Over;
    m_gameMusicSound.stop();
	m_gameOverSound.play();
	if (m_highScore < m_score)
	{
		m_highScore = m_score;
	}
	m_overScoreText.setString("Score: " + std::to_string(m_score));
	m_overHighScoreText.setString("High Score: " + std::to_string(m_highScore));
	m_overScoreText.setPosition(screenWidth / 2 - m_overScoreText.getLocalBounds().width / 2, screenHeight / 2 - m_overScoreText.getLocalBounds().height);
	m_overHighScoreText.setPosition(screenWidth / 2 - m_overHighScoreText.getLocalBounds().width / 2, screenHeight / 2 + 20);
}

void Stage::update()
{
	if (m_gameStatus == Over || m_gameStatus == Waiting)
	{
		draw();
		return;
	}
	if (m_enemyClock.getElapsedTime() >= sf::seconds(enemySpawnTime))
	{
		Enemy* enemy = new Enemy(rand() % 3);
		addEntity(enemy);
		m_enemyClock.restart();
	}
	for (Entity* entityA : entitys)
	{
		for (Entity* entityB : entitys)
		{
			if (hitTest(entityA->getCollision(), entityB->getCollision()))
			{
				if (entityA->getType() == "Enemy" &&
					entityB->getType() == "Bullet" &&
					((Enemy*)entityA)->getStatus() != Dying &&
					((Bullet*)entityB)->getBulletType() == HeroBullet)
				{
					((Enemy*)entityA)->hit();
					((Bullet*)entityB)->die();
				}
				else if (entityA->getType() == "Hero" &&
						entityB->getType() == "Bullet" &&
						((Bullet*)entityB)->getBulletType() == EnemyBullet)
				{
					((Hero*)entityA)->hit();
					((Bullet*)entityB)->die();
				}
				else if (entityA->getType() == "Enemy" &&
						entityB->getType() == "Hero" &&
						((Enemy*)entityA)->getStatus() != Dying)
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
			if ((*it)->getType() == "Hero")
			{
				gameOver();
			}
			else
			{
				delete *it;
				entitys.erase(it);
				it--;
			}
		}
	}
	for (Entity* entity : entitys)
	{
		if (entity->getType() == "Enemy" && ((Enemy*)entity)->getStatus() != Dying)
		{
			((Enemy*)entity)->fire(m_hero->getPosition());
		}
	}
    draw();
}

float Stage::cross(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB) const
{
	return vectorA.x * vectorB.y - vectorA.y * vectorB.x;
}

bool Stage::hitTest(const sf::ConvexShape& collisionA, const sf::ConvexShape& collisionB) const
{
    for	(int i = 0; i < (int)collisionA.getPointCount(); ++i)
	{
		for	(int j = 0; j < (int)collisionB.getPointCount(); ++j)
		{
			const sf::Vector2f& A = collisionA.getTransform().transformPoint(collisionA.getPoint(i));
			const sf::Vector2f& B = collisionA.getTransform().transformPoint(collisionA.getPoint((i + 1) % collisionA.getPointCount()));
			const sf::Vector2f& C = collisionB.getTransform().transformPoint(collisionB.getPoint(j));
			const sf::Vector2f& D = collisionB.getTransform().transformPoint(collisionB.getPoint((j + 1) % collisionB.getPointCount()));
			if (cross(B - A, C - A) * cross(B - A, D - A) < 0 && cross(D - C, A - C) * cross(D - C, B - C) < 0)
			{
				return true;
			}
		}
	}
	return false;
}
