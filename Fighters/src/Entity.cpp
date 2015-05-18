#include <Entity.hpp>

void Entity::setPosition(const sf::Vector2f& position)
{
	sf::Sprite::setPosition(position);
	m_collision.setPosition(position);
}

void Entity::setPosition(float x, float y)
{
	sf::Sprite::setPosition(x, y);
	m_collision.setPosition(x, y);
}

void Entity::setOrigin(float x, float y)
{
	sf::Sprite::setOrigin(x, y);
	m_collision.setOrigin(x, y);
}

void Entity::move(float offsetX, float offsetY)
{
	sf::Sprite::move(offsetX, offsetY);
	m_collision.move(offsetX, offsetY);
}

void Entity::move(const sf::Vector2f& offset)
{
	sf::Sprite::move(offset);
	m_collision.move(offset);
}

void Entity::rotate(float angle)
{
	sf::Sprite::rotate(angle);
	m_collision.rotate(angle);
}
