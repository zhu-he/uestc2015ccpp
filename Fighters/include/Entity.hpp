#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Stage.hpp"

class Stage;

class Entity : public sf::Sprite
{
	public:
		virtual std::string getType() = 0;
		virtual bool isAlive() = 0;
		virtual void animate() = 0;
		virtual sf::ConvexShape getCollision();
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f& position);
		void setOrigin(float x, float y);
		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f& offset);
		void rotate(float angle);
		friend class Stage;
	protected:
		Stage* m_stage;
		sf::ConvexShape m_collision;
};

#endif // ENTITY_HPP
