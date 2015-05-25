#ifndef __UFO_HPP__
#define __UFO_HPP__

#include <cstdlib>
#include "Entity.hpp"

class Ufo : public Entity
{
	public:
		Ufo(UfoType ufoType);
		virtual ~Ufo();
		void animate();
		bool isAlive();
		void die();
		UfoType getUfoType();
		std::string getType();
		static void loadResources();
	private:
		static sf::Texture m_ufoTexture[2];
		bool m_isAlive;
		UfoType m_ufoType;
		sf::Vector2f m_ufoSpeed;
};

#endif // __UFO_HPP__
