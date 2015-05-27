#include "MultiplayerStage.hpp"
#include "Sound.hpp"
#include "Hero2.hpp"
#include "Font.hpp"

extern sf::Clock gameClock;

MultiplayerStage::MultiplayerStage(sf::RenderWindow& window, Background& background, sf::TcpSocket& socket) : Stage(window, background), m_socket(socket)
{
	m_sendCounter = 0;
	m_hero2 = new Hero2();
	addEntity(m_hero2);
	m_hero->setId(-1);
	m_hero2->setId(-2);
	m_scoreText.setPosition(screenWidth / 2 - 55, 4);
	m_hpText.setPosition(10, 0);
	m_hp2Text.setFont(Font::getFont());
	m_hp2Text.setCharacterSize(30);
	m_hp2Text.setColor(heartColor);
	m_hp2Text.setStyle(sf::Text::Bold);
	m_hp2Text.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
}

void MultiplayerStage::init()
{
	Stage::init();
	m_isHeroFire = false;
	m_isHeroLeft = false;
	m_isHeroRight = false;
	m_isHeroUp = false;
	m_isHeroDown = false;
	m_isHero2Fire = false;
	m_isHero2Left = false;
	m_isHero2Right = false;
	m_isHero2Up = false;
	m_isHero2Down = false;
	setHp2Text(heroHp);
	((Hero2*)m_hero2)->revive();
	m_hero->setPosition(screenWidth / 3, m_hero->getPosition().y);
	m_hero2->setPosition(screenWidth / 3 * 2, m_hero->getPosition().y);
}

void MultiplayerStage::setHpText(int hp)
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
}

void MultiplayerStage::setHp2Text(int hp)
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
	m_hp2Text.setString(heartString);
	m_hp2Text.setPosition(screenWidth - m_hp2Text.getLocalBounds().width - 10, 0);
}

void MultiplayerStage::useBomb()
{
	if (((Hero*)m_controlHero)->getBomb() > 0 && !m_isBombing)
	{
		m_packet << "U";
		((Hero*)m_controlHero)->useBomb();
		m_isBombing = true;
		m_bombClock.restart();
		Sound::playUseBombSound();
	}
}

void MultiplayerStage::draw()
{
	Stage::draw();
	for (int i = 0; i < ((Hero2*)m_hero2)->getBomb(); ++i)
	{
		m_bombSprite.setPosition(screenWidth - (i + 1) * m_bombTexture.getSize().x, screenHeight - m_bombTexture.getSize().y);
		m_window.draw(m_bombSprite);
	}
	for (int i = 0; i < ((Hero2*)m_hero2)->getBomb(); ++i)
	{
		drawLight(sf::Vector2f(screenWidth - (i + 0.5f) * m_bombTexture.getSize().x , screenHeight - m_bombTexture.getSize().y / 2), sf::Color::Red, 100);
	}
	m_window.draw(m_hp2Text);
}

bool MultiplayerStage::isOver()
{
	return !m_hero->isAlive() && !m_hero2->isAlive();
}

void MultiplayerStage::pause()
{
	m_packet << "P";
	m_socket.send(m_packet);
	m_packet.clear();
	Stage::pause();
}

void MultiplayerStage::resume()
{
	m_packet << "C";
	m_socket.send(m_packet);
	m_packet.clear();
	Stage::resume();
}

void MultiplayerStage::restart()
{
    m_packet << "I";
	m_socket.send(m_packet);
	m_packet.clear();
	init();
}

sf::Vector2f MultiplayerStage::getHeroPosition()
{
	if (m_hero2->isAlive())
	{
		if (m_hero->isAlive())
		{
			return rand() % 2 ? m_hero->getPosition() : m_hero2->getPosition();
		}
		return m_hero2->getPosition();
	}
	return m_hero->getPosition();
}
