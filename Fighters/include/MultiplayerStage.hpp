#ifndef __MULTIPLAYERSTAGE_HPP__
#define __MULTIPLAYERSTAGE_HPP__

#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "Stage.hpp"

class MultiplayerStage : public Stage
{
	public:
		MultiplayerStage(sf::RenderWindow& window, Background& background, sf::TcpSocket& socket);
		void setHpText(int hp);
		void setHp2Text(int hp);
	protected:
		sf::TcpSocket& m_socket;
		sf::Packet m_packet;
		Entity* m_hero2;
		bool isOver();
		void init();
		void draw();
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
		int m_sendCounter;
	private:
		void useBomb();
		sf::Text m_hp2Text;
		sf::Vector2f getHeroPosition();
		void pause();
		void resume();
		void restart();
};

#endif // __MULTIPLAYERSTAGE_HPP__
