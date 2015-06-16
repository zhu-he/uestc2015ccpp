#include "Shader.hpp"

sf::Shader Shader::m_invertShader;
sf::Shader Shader::m_shadowShader;
sf::Shader Shader::m_lightShader;
bool Shader::m_shaderSwitch;
bool Shader::m_shaderAvailable;

void Shader::loadResources()
{
	m_shaderSwitch = true;
	m_shaderAvailable = sf::Shader::isAvailable();
	if (Shader::isAvailable())
	{
		m_invertShader.loadFromFile("resources/shader/invert.frag", sf::Shader::Fragment);
		m_invertShader.setParameter("texture", m_invertShader.CurrentTexture);
		m_lightShader.loadFromFile("resources/shader/light.frag", sf::Shader::Fragment);
		m_shadowShader.loadFromFile("resources/shader/shadow.frag", sf::Shader::Fragment);
	}
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

bool Shader::isAvailable()
{
	return m_shaderSwitch && m_shaderAvailable;
}

void Shader::switchShader()
{
	m_shaderSwitch = !m_shaderSwitch;
}
