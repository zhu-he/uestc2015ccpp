#ifndef __SERVERSTAGE_HPP__
#define __SERVERSTAGE_HPP__

#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Stage.hpp"

class ServerStage : public Stage
{
	public:
		ServerStage(sf::RenderWindow& window, sf::TcpSocket& client);
		virtual ~ServerStage();
		void addEntity(Entity* entity);
		void update();
	protected:
		sf::TcpSocket& m_client;
		Entity* m_hero2;
		virtual void init();
		int m_sendCounter;
};

#endif // __SERVERSTAGE_HPP__
