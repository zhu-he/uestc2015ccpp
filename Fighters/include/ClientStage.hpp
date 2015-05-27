#ifndef __CLIENTSTAGE_HPP__
#define __CLIENTSTAGE_HPP__

#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include "MultiplayerStage.hpp"

class ClientStage : public MultiplayerStage
{
	public:
		ClientStage(sf::RenderWindow& window, sf::TcpSocket& server);
		virtual ~ClientStage();
		void addEntity(Entity* entity);
		bool update();
	protected:
		Entity* findEntityById(int id);
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

#endif // __CLIENTSTAGE_HPP__
