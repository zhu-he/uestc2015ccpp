#include "Hero2.hpp"

Hero2::Hero2() : Hero()
{
	m_color = sf::Color(64, 255, 64);
}

std::string Hero2::getType()
{
	return "Hero2";
}
