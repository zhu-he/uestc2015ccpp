#ifndef __SERVERSTAGE_HPP__
#define __SERVERSTAGE_HPP__

#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "MultiplayerStage.hpp"

class ServerStage : public MultiplayerStage
{
	public:
		ServerStage(sf::RenderWindow& window, sf::TcpSocket& client);
		virtual ~ServerStage();
		void addEntity(Entity* entity);
		bool update();
	protected:
		int m_idCounter;
		void hitEntity(Entity* entity);
		void dieEntity(Entity* entity);
		void bombup(Entity* hero);
		void fire();
		void noFire();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void moveNoLeft();
		void moveNoRight();
		void moveNoUp();
		void moveNoDown();
};

#endif // __SERVERSTAGE_HPP__
