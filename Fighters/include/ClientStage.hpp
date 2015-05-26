#ifndef __CLIENTSTAGE_HPP__
#define __CLIENTSTAGE_HPP__

#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include "Stage.hpp"

class ClientStage : public Stage
{
	public:
		ClientStage(sf::RenderWindow& window, sf::TcpSocket& server);
		virtual ~ClientStage();
		void addEntity(Entity* entity);
        void play();
	protected:
		sf::TcpSocket& m_server;
		Entity* m_hero2;
		void init();
		int m_sendCounter;
};

#endif // __CLIENTSTAGE_HPP__
