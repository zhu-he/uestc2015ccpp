#include "Hero2.hpp"
#include "MultiplayerStage.hpp"

Hero2::Hero2() : Hero()
{
	m_color = sf::Color(64, 255, 64);
}

std::string Hero2::getType()
{
	return "Hero2";
}

void Hero2::hit()
{
	if (m_invincible.getElapsedTime() < sf::seconds(invincibleTime))
	{
		return;
	}
    m_hp--;
    ((MultiplayerStage*)m_stage)->setHp2Text(m_hp);
    if (m_hp <= 0 && m_status != Dying)
	{
		die();
	}
	else
	{
		m_invincible.restart();
		m_invincibleFlash.restart();
	}
}
