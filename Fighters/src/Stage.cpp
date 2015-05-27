#include "Stage.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Hero.hpp"
#include "Ufo.hpp"
#include "SpriteSheet.hpp"
#include "Sound.hpp"
#include "Font.hpp"
#include "Shader.hpp"

extern sf::Clock gameClock;

Stage::Stage(sf::RenderWindow& window, Background& background) : m_window(window), m_background(background), m_pausedMenu(PauseMenu, screenHeight / 2)
{
	m_score = 0;
	m_scoreText.setFont(Font::getFont());
	m_scoreText.setCharacterSize(24);
	m_scoreText.setPosition(10, 4);
	m_scoreText.setStyle(sf::Text::Bold);
	m_hpText.setFont(Font::getFont());
	m_hpText.setCharacterSize(30);
	m_hpText.setColor(heartColor);
	m_hpText.setStyle(sf::Text::Bold);
	m_hpText.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
	m_overScoreText.setFont(Font::getFont());
	m_overScoreText.setCharacterSize(40);
	m_overScoreText.setStyle(sf::Text::Bold);
	m_overHighScoreText.setFont(Font::getFont());
	m_overHighScoreText.setCharacterSize(40);
	m_overHighScoreText.setStyle(sf::Text::Bold);
	m_overText.setFont(Font::getFont());
	m_overText.setString("Game Over");
	m_overText.setCharacterSize(40);
	m_overText.setStyle(sf::Text::Bold);
	m_highScore = 0;
	m_isBombing = false;
	m_lightShader = Shader::getLightShader();
	m_shadowShader = Shader::getShadowShader();
	m_lightRenderStates.shader = m_lightShader;
	m_lightRenderStates.blendMode = sf::BlendAdd;
	m_lightRenderTexture.create(screenWidth, screenHeight);
	m_lightSprite.setTexture(m_lightRenderTexture.getTexture());
	m_shadowRenderTexture.create(screenWidth, screenHeight);
	m_shadowSprite.setTexture(m_shadowRenderTexture.getTexture());
	m_shadowRenderStates.shader = m_shadowShader;
	m_bombTexture = SpriteSheet::getTexture(bombImage);
	m_bombSprite.setTexture(m_bombTexture);
	m_isRunning = true;
	m_highScoreIfstream.open(highScorePath, std::ios::in);
	if (!m_highScoreIfstream.is_open())
	{
		m_highScore = 0;
	}
	else
	{
		m_highScoreIfstream >> m_highScore;
		m_highScoreIfstream.close();
	}
	m_hero = new Hero();
	m_controlHero = m_hero;
	addEntity(m_hero);
}

Stage::~Stage()
{
	m_highScoreOfstream.open(highScorePath, std::ios::out);
	m_highScoreOfstream << m_highScore;
	m_highScoreOfstream.close();
}

void Stage::addEntity(Entity* entity)
{
	m_entitys.push_back(entity);
	entity->m_stage = this;
}

void Stage::dieEntity(Entity* entity)
{
	if (entity != nullptr)
	{
		entity->die();
	}
}

void Stage::hitEntity(Entity* entity)
{
	if (entity != nullptr)
	{
		entity->hit();
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

void Stage::setHpText(int hp)
{
	if (hp < 0)
	{
		hp = 0;
	}
	wchar_t heartString[heroHp + 1];
	for (int i = 0; i < hp; ++i)
	{
		heartString[i] = L'♥';
	}
	heartString[hp] = 0;
	m_hpText.setString(heartString);
	m_hpText.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
}

void Stage::init()
{
	m_score = 0;
	m_isRunning = true;
	m_scoreText.setString("Score: 0");
	setHpText(heroHp);
	m_gameStatus = Playing;
	((Hero*)m_hero)->revive();
	gameClock.restart();
	m_scoreText.setColor(Font::getColor());
	m_overScoreText.setColor(Font::getColor());
	m_overHighScoreText.setColor(Font::getColor());
	m_overText.setColor(Font::getColor());
	for (int i = 0; i < 3; ++i)
	{
		m_enemyClock[i].restart();
	}
	m_ufoClock.restart();
	for (std::vector<Entity*>::iterator it = m_entitys.begin(); it != m_entitys.end(); ++it)
	{
		if ((*it)->getType() != "Hero" && (*it)->getType() != "Hero2")
		{
			delete *it;
			m_entitys.erase(it);
			it--;
		}
	}
	Sound::playGameMusicSound();
}

void Stage::play()
{
	init();
	while (m_window.isOpen() && m_isRunning)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape && m_gameStatus == Playing)
				{
					pause();
				}
				else if (event.key.code == sf::Keyboard::Escape && m_gameStatus == Over)
				{
					m_isRunning = false;
				}
				else if (event.key.code == sf::Keyboard::Down && m_gameStatus == Paused)
				{
					m_pausedMenu.next();
				}
				else if (event.key.code == sf::Keyboard::Up && m_gameStatus == Paused)
				{
					m_pausedMenu.previous();
				}
				else if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return) && m_gameStatus == Paused)
				{
					if (m_pausedMenu.getMenuCursor() == 0)
					{
						resume();
					}
					else if (m_pausedMenu.getMenuCursor() == 1)
					{
						restart();
					}
					else
					{
						m_isRunning = false;
					}
				}
				else if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return) && m_gameStatus == Over)
				{
					restart();
				}
				break;
			default:
				break;
			}
		}
		if (getGameStatus() == Playing && m_controlHero->isAlive())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				moveLeft();
			}
			else
			{
				moveNoLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				moveRight();
			}
			else
			{
				moveNoRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				moveUp();
			}
			else
			{
				moveNoUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				moveDown();
			}
			else
			{
				moveNoDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				fire();
			}
			else
			{
				noFire();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				useBomb();
			}
		}
		if (!update())
		{
			break;
		}
		m_window.draw(m_lightSprite, sf::BlendAdd);
		m_lightRenderTexture.clear(sf::Color::Transparent);
		m_window.display();
    }
	Sound::playGameMusicSound();
}

void Stage::draw()
{
	m_window.clear();
	m_window.draw(m_background);
	for (Entity* entity : m_entitys)
	{
		if (entity->isAlive())
		{
			if (entity->getType() == "Bullet")
			{
				if (((Bullet*)entity)->getBulletType() == EnemyBullet)
				{
					drawLight(entity->getPosition(), sf::Color::Blue, 200);
				}
				else if (((Bullet*)entity)->getBulletType() == HeroBullet)
				{
					drawLight(entity->getPosition(), sf::Color::Red, 200);
				}
				else
				{
					drawLight(entity->getPosition(), sf::Color::Green, 200);
				}
			}
			else if (entity->getType() == "Ufo")
			{
				if (((Ufo*)entity)->getUfoType() == Weapon)
				{
					drawLight(entity->getPosition(), sf::Color::Blue, 100);
				}
				else
				{
					drawLight(entity->getPosition(), sf::Color::Red, 100);
				}
			}
		}
	}
	m_shadowRenderTexture.clear(sf::Color::Transparent);
	drawShadow(sf::Vector2f(screenWidth / 2, screenHeight / 2), 50);
	m_window.draw(m_shadowSprite);
	for (Entity* entity : m_entitys)
	{
		if (entity->isAlive())
		{
			m_window.draw(*entity);
			// m_window.draw(entity->getCollision());
		}
	}
	if (m_gameStatus == Playing)
	{
		m_window.draw(m_scoreText);
		m_window.draw(m_hpText);
	}
	else if (m_gameStatus == Overing || m_gameStatus == Over)
	{
		m_window.draw(m_overText);
		m_window.draw(m_overScoreText);
		m_window.draw(m_overHighScoreText);
	}
	else if (m_gameStatus == Paused)
	{
		m_window.draw(m_scoreText);
		m_window.draw(m_hpText);
		m_window.draw(m_pausedMenu);
	}
	for (int i = 0; i < ((Hero*)m_hero)->getBomb(); ++i)
	{
		m_bombSprite.setPosition(i * m_bombTexture.getSize().x, screenHeight - m_bombTexture.getSize().y);
		m_window.draw(m_bombSprite);
	}
	for (int i = 0; i < ((Hero*)m_hero)->getBomb(); ++i)
	{
		drawLight(sf::Vector2f((i + 0.5f) * m_bombTexture.getSize().x , screenHeight - m_bombTexture.getSize().y / 2), sf::Color::Red, 100);
	}
}

void Stage::gameOver()
{
	if (m_gameStatus != Playing)
	{
		return;
	}
    m_gameStatus = Overing;
    Sound::stopGameMusicSound();
	Sound::playGameOverSound();
	if (m_highScore < m_score)
	{
		m_highScore = m_score;
	}
	m_overScoreText.setString("Score: " + std::to_string(m_score));
	m_overHighScoreText.setString("High Score: " + std::to_string(m_highScore));
	m_overScoreText.setPosition(screenWidth / 2 - m_overScoreText.getLocalBounds().width / 2, screenHeight);
	m_overHighScoreText.setPosition(screenWidth / 2 - m_overHighScoreText.getLocalBounds().width / 2, screenHeight + m_overScoreText.getLocalBounds().height + 20);
	m_overText.setPosition(screenWidth / 2 - m_overText.getLocalBounds().width / 2, -m_overText.getLocalBounds().height * 4);
}

void Stage::animate()
{
	if (m_isBombing)
	{
		if (m_bombClock.getElapsedTime() < sf::seconds(bombTime))
		{
			drawLight(sf::Vector2f(screenWidth / 2, screenHeight / 2), sf::Color(255, 128, 128), 0.2 / m_bombClock.getElapsedTime().asSeconds());
		}
		else if (m_bombClock.getElapsedTime() < sf::seconds(bombTime * 1.5))
		{
			for (Entity* entity : m_entitys)
			{
				if (entity->isAlive())
				{
					if (entity->getType() == "Enemy")
					{
						dieEntity(entity);
					}
					else if (entity->getType() == "Bullet" && ((Bullet*)entity)->getBulletType() == EnemyBullet)
					{
						dieEntity(entity);
					}
				}
			}
			drawLight(sf::Vector2f(screenWidth / 2, screenHeight / 2), sf::Color(255, 128, 128), 0.2 / (bombTime * 3 - m_bombClock.getElapsedTime().asSeconds() * 2));
		}
		else
		{
			m_isBombing = false;
		}
	}
	m_background.animate();
	for (std::vector<Entity*>::iterator it = m_entitys.begin(); it != m_entitys.end(); ++it)
	{
		if (!(*it)->isAlive())
		{
			if ((*it)->getType() != "Hero" && (*it)->getType() != "Hero2")
			{
				delete *it;
				m_entitys.erase(it);
				it--;
			}
		}
		else
		{
			(*it)->animate();
		}
	}
}

bool Stage::update()
{
	if (isOver())
	{
		gameOver();
	}
	if (m_gameStatus == Overing)
	{
		m_overText.move(0, 10);
		m_overScoreText.move(0, -10);
		m_overHighScoreText.move(0, -10);
		if (m_overText.getPosition().y >= screenHeight / 2 - m_overText.getLocalBounds().height * 4)
		{
			m_gameStatus = Over;
		}
		animate();
		draw();
		return true;
	}
	if (m_gameStatus == Over)
	{
		animate();
		draw();
		return true;
	}
	if (m_gameStatus == Paused)
	{
		draw();
		return true;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (m_enemyClock[i].getElapsedTime() >= sf::seconds(enemySpawnTime[i] / (gameClock.getElapsedTime().asSeconds() / 45 + 1)))
		{
			Enemy* enemy = new Enemy(i);
			addEntity(enemy);
			m_enemyClock[i].restart();
		}
	}
	if (m_ufoClock.getElapsedTime() >= sf::seconds(ufoSpawnTime * (gameClock.getElapsedTime().asSeconds() / 30 + 1)))
	{
		Ufo* ufo = new Ufo((UfoType)(rand() % 2));
		addEntity(ufo);
		m_ufoClock.restart();
	}
	for (Entity* entityA : m_entitys)
	{
		if (!entityA->isAlive())
		{
			continue;
		}
		for (Entity* entityB : m_entitys)
		{
			if (!entityB->isAlive())
			{
				continue;
			}
			if (hitTest(entityA->getCollision(), entityB->getCollision()))
			{
				if (entityA->getType() == "Enemy" &&
					entityB->getType() == "Bullet" &&
					((Enemy*)entityA)->getStatus() != Dying &&
					((Bullet*)entityB)->getBulletType() != EnemyBullet)
				{
					hitEntity(entityA);
					dieEntity(entityB);
				}
				else if ((entityA->getType() == "Hero" ||
						entityA->getType() == "Hero2") &&
						entityB->getType() == "Bullet" &&
						((Bullet*)entityB)->getBulletType() == EnemyBullet &&
						!m_isBombing)
				{
					hitEntity(entityA);
					dieEntity(entityB);
				}
				else if (entityA->getType() == "Enemy" &&
						(entityB->getType() == "Hero" ||
						entityB->getType() == "Hero2") &&
						((Enemy*)entityA)->getStatus() != Dying &&
						!m_isBombing)
				{
					hitEntity(entityB);
					dieEntity(entityA);
				}
				else if (entityA->getType() == "Ufo" &&
						(entityB->getType() == "Hero" ||
						entityB->getType() == "Hero2"))
				{
					if (((Ufo*)entityA)->getUfoType() == Weapon)
					{
						levelup(entityB);
					}
					else
					{
						bombup(entityB);
					}
					dieEntity(entityA);
				}
			}
		}
	}
	for (int i = 0; i < (int)m_entitys.size(); ++i)
	{
		if (m_entitys[i]->getType() == "Enemy" && ((Enemy*)m_entitys[i])->getStatus() != Dying)
		{
			((Enemy*)m_entitys[i])->fire(getHeroPosition());
		}
	}
	animate();
    draw();
	return true;
}

bool Stage::isOver()
{
	return !m_hero->isAlive();
}

float Stage::cross(const sf::Vector2f& vectorA, const sf::Vector2f& vectorB) const
{
	return vectorA.x * vectorB.y - vectorA.y * vectorB.x;
}

bool Stage::hitTest(const sf::ConvexShape& collisionA, const sf::ConvexShape& collisionB) const
{
	if (!collisionA.getGlobalBounds().intersects(collisionB.getGlobalBounds()))
	{
		return false;
	}
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

void Stage::drawLight(sf::Vector2f lightPosition, sf::Color color, float lightAttenuation)
{
	if (Shader::isAvailable())
	{
		m_lightShader->setParameter("frag_LightAttenuation", lightAttenuation);
		m_lightShader->setParameter("frag_LightOrigin", lightPosition);
		m_lightShader->setParameter("frag_LightColor", color.r, color.g, color.b, color.a);
		m_lightRenderTexture.draw(m_lightSprite, m_lightRenderStates);
	}
}

void Stage::drawShadow(sf::Vector2f lightPosition, float shadowAttenuation)
{
	if (Shader::isAvailable())
	{
		m_shadowShader->setParameter("frag_LightOrigin", lightPosition);
		m_shadowShader->setParameter("frag_shadowAttenuation", shadowAttenuation);
		for (Entity* castEntity : m_entitys)
		{
			if (castEntity->isAlive() && castEntity->getType() != "Bullet" && !(castEntity->getType() == "Hero" && ((Hero*)castEntity)->isFlash()))
			{
				sf::Transform transform = castEntity->getCollision().getTransform();
				for	(int i = 0; i < (int)castEntity->getCollision().getPointCount(); ++i)
				{
					const sf::Vector2f& A = transform.transformPoint(castEntity->getCollision().getPoint(i % castEntity->getCollision().getPointCount()));
					const sf::Vector2f& B = transform.transformPoint(castEntity->getCollision().getPoint((i + 1) % castEntity->getCollision().getPointCount()));
					if (cross(lightPosition - A, B - A) > 0)
					{
						m_shadowShader->setParameter("frag_castPosition1", A);
						m_shadowShader->setParameter("frag_castPosition2", B);
						m_shadowRenderTexture.draw(m_shadowSprite, m_shadowRenderStates);
					}
				}
			}
		}
	}
}

sf::Vector2f Stage::getHeroPosition()
{
	return m_hero->getPosition();
}

void Stage::useBomb()
{
	if (((Hero*)m_controlHero)->getBomb() > 0 && !m_isBombing)
	{
		((Hero*)m_controlHero)->useBomb();
		m_isBombing = true;
		m_bombClock.restart();
		Sound::playUseBombSound();
	}
}

void Stage::fire()
{
	((Hero*)m_hero)->fire();
}

void Stage::noFire()
{

}

void Stage::moveLeft()
{
	((Hero*)m_controlHero)->moveLeft();
}

void Stage::moveRight()
{
	((Hero*)m_controlHero)->moveRight();
}

void Stage::moveUp()
{
	((Hero*)m_controlHero)->moveUp();
}

void Stage::moveDown()
{
	((Hero*)m_controlHero)->moveDown();
}

void Stage::moveNoLeft()
{

}

void Stage::moveNoRight()
{

}

void Stage::moveNoUp()
{

}

void Stage::moveNoDown()
{

}

void Stage::pause()
{
	m_gameStatus = Paused;
	m_pausedMenu.setMenuCursor(0);
}

void Stage::resume()
{
	m_gameStatus = Playing;
}

void Stage::restart()
{
	init();
}

void Stage::bombup(Entity* hero)
{
    ((Hero*)hero)->bombup();
}

void Stage::levelup(Entity* hero)
{
    ((Hero*)hero)->levelup();
}
