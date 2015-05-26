#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <SFML/Graphics/Shader.hpp>

class Shader
{
	public:
		static void loadResources();
		static sf::Shader* getInvertShader();
		static sf::Shader* getShadowShader();
		static sf::Shader* getLightShader();
	private:
		static sf::Shader m_invertShader;
		static sf::Shader m_shadowShader;
		static sf::Shader m_lightShader;
};

#endif // __SHADER_HPP__
