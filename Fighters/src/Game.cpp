#include "Game.hpp"
#include "Menu.hpp"
#include "Stage.hpp"
#include "Hero.hpp"
#include "Global.hpp"
#include "Sound.hpp"
#include "Font.hpp"

Game::Game() : m_window(sf::VideoMode(screenWidth, screenHeight), "Fighters", sf::Style::Titlebar | sf::Style::Close)
{
	m_window.setFramerateLimit(60);
	m_window.setSize(sf::Vector2u(360, 600));
	m_titleText.setFont(Font::getFont());
	m_titleText.setString("Fighters");
	m_titleText.setCharacterSize(100);
	m_titleText.setColor(sf::Color::White);
	m_titleText.setStyle(sf::Text::Bold);
	m_titleText.setPosition((screenWidth - m_titleText.getLocalBounds().width) / 2, 150);
	m_invertShader.loadFromFile("resources/shader/invert.frag", sf::Shader::Fragment);
	m_invertShader.setParameter("texture", m_invertShader.CurrentTexture);
}

Game::~Game()
{

}

void Game::quit()
{
	m_isRunning = false;
}

void Game::play()
{
	Sound::playGameMusicSound();
	m_isRunning = true;
	Menu menu(MainMenu);
	Stage stage(m_window);
	stage.setBackground(&m_background);
	Hero hero;
	stage.addEntity(&hero);
	while (m_window.isOpen())
	{
		sf::Event event;
        while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
                switch (event.key.code)
                {
				case sf::Keyboard::Down:
					menu.next();
					break;
				case sf::Keyboard::Up:
					menu.previous();
					break;
				case sf::Keyboard::Space: case sf::Keyboard::Return:
					switch (menu.getMenuStatus())
					{
					case MainMenu:
						switch (menu.getMenuCursor())
						{
						case 0:
							stage.play();
							break;
						case 1:
							menu.setMenu(MultiplayerMenu);
							break;
						case 2:
							menu.setMenu(SettingMenu);
							menu.bindSwitch(0, Sound::getBgmSwitch, Sound::switchBgm);
							menu.bindSwitch(1, Sound::getSfxSwitch, Sound::switchSfx);
							break;
						case 3:
							m_window.close();
							break;
						default:
							break;
						}
						break;
					case MultiplayerMenu:
						switch (menu.getMenuCursor())
						{
						case 0:

							break;
						case 1:
							menu.setMenu(JoinMenu);
							break;
						case 2:
							menu.setMenu(MainMenu);
							break;
						default:
							break;
						}
						break;
					case SettingMenu:
						switch (menu.getMenuCursor())
						{
						case 0:
							menu.toggleSwitch();
							break;
						case 1:
							menu.toggleSwitch();
							break;
						case 2:
							menu.setMenu(MainMenu);
							break;
						default:
							break;
						}
						break;
					case JoinMenu:
						switch (menu.getMenuCursor())
						{
						case 0:

							break;
						case 1:

							break;
						case 2:
							menu.setMenu(MultiplayerMenu);
							break;
						default:
							break;
						}
						break;
					}
					break;
				default:
					menu.input(event.key.code);
					break;
                }
				break;
			default:
				break;
			}
		}
		m_background.animate();
		m_window.clear();
		m_window.draw(m_background, &m_invertShader);
		m_window.draw(m_titleText);
		m_window.draw(menu);
		m_window.display();
	}
}
