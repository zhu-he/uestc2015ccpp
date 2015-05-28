#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics.hpp>
#include <string>
#include "Stage.hpp"

class Stage;

class Entity : public sf::Sprite
{
	friend class Stage;
	public:
		virtual void setId(int id);
		virtual int getId();
		void setPosition(float x, float y);
		virtual bool isAlive();
		virtual std::string getType() = 0;
		virtual void hit() = 0;
		virtual void die() = 0;
	protected:
		Stage* m_stage;
		bool m_isAlive;
		sf::ConvexShape m_collision;
		void setOrigin(float x, float y);
		void setPosition(const sf::Vector2f& position);
		void move(const sf::Vector2f& offset);
		void move(float offsetX, float offsetY);
		void rotate(float angle);
	private:
		virtual void animate() = 0;
		virtual sf::ConvexShape getCollision();
		int m_id;
};

#endif // __ENTITY_HPP__
