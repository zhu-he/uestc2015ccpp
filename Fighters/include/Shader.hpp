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
		static bool isAvailable();
		static void switchShader();
	private:
		static sf::Shader m_invertShader;
		static sf::Shader m_shadowShader;
		static sf::Shader m_lightShader;
		static bool m_shaderSwitch;
};

#endif // __SHADER_HPP__
