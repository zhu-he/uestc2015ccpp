#ifndef __MULTIPLAYERSTAGE_HPP__
#define __MULTIPLAYERSTAGE_HPP__

#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "Stage.hpp"

class MultiplayerStage : public Stage
{
	public:
		MultiplayerStage(sf::RenderWindow& window);
		virtual ~MultiplayerStage();
		void setHpText(int hp);
		void setHp2Text(int hp);
	protected:
		sf::Packet m_packet;
		sf::Text m_hp2Text;
		Entity* m_hero2;
		void init();
		void draw();
		bool isOver();
		int m_sendCounter;
		bool m_isHeroFire;
		bool m_isHeroLeft;
		bool m_isHeroRight;
		bool m_isHeroUp;
		bool m_isHeroDown;
		bool m_isHero2Fire;
		bool m_isHero2Left;
		bool m_isHero2Right;
		bool m_isHero2Up;
		bool m_isHero2Down;
};

#endif // __MULTIPLAYERSTAGE_HPP__
