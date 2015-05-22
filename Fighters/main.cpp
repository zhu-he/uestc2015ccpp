#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "SpriteSheet.hpp"
#include "Background.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Global.hpp"
#include "Stage.hpp"
#include "Ufo.hpp"

using namespace std;

int main()
{
	srand((int)time(0));
	SpriteSheet::loadFromFile(packPath);
	Background::loadResources();
	Hero::loadResources();
	Enemy::loadResources();
	Bullet::loadResources();
	Ufo::loadResources();
	sf::Sprite iconSprite;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fighters", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(sf::Vector2u(360, 600));
    Stage stage(window);
    Background background;
    Hero hero;
    stage.setBackground(&background);
    stage.addEntity(&hero);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (stage.getGameStatus() == Waiting || stage.getGameStatus() == Over)
				{
					stage.play();
				}
				break;
			default:
				break;
			}
		}
		if (stage.getGameStatus() == Playing)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				hero.moveLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				hero.moveRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				hero.moveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				hero.moveDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				hero.fire();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				stage.useBomb();
			}
		}
		stage.update();
    }
    return 0;
}
