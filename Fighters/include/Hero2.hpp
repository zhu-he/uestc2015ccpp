#ifndef __HERO2_HPP__
#define __HERO2_HPP__

#include "Hero.hpp"

class Hero2 : public Hero
{
	public:
		Hero2();
		std::string getType();
		void hit();
};

#endif // __HERO2_HPP__
