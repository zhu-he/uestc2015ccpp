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
		friend class Stage;
	protected:
		Stage* m_stage;
};

#endif // ENTITY_HPP
