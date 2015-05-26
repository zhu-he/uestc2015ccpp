#include "Shader.hpp"

sf::Shader Shader::m_invertShader;
sf::Shader Shader::m_shadowShader;
sf::Shader Shader::m_lightShader;

void Shader::loadResources()
{
	m_invertShader.loadFromFile("resources/shader/invert.frag", sf::Shader::Fragment);
	m_invertShader.setParameter("texture", m_invertShader.CurrentTexture);
	m_lightShader.loadFromFile("resources/shader/light.frag", sf::Shader::Fragment);
	m_shadowShader.loadFromFile("resources/shader/shadow.frag", sf::Shader::Fragment);
}

sf::Shader* Shader::getInvertShader()
{
	return &m_invertShader;
}

sf::Shader* Shader::getShadowShader()
{
	return &m_shadowShader;
}

sf::Shader* Shader::getLightShader()
{
	return &m_lightShader;
}

