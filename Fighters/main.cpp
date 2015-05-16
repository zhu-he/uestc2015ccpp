#include <SFML/Graphics.hpp>
#include "SpriteSheet.hpp"
#include <iostream>
#include "Background.hpp"
#include "Hero.hpp"
#include "Global.hpp"

using namespace std;

sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;

int main()
{
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fighters");
    Background background;
    Hero hero;
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
			default:
				break;
            }
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			hero.moveLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			hero.moveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			hero.fire();
		}
		background.animate();
        hero.animate();
        window.clear();
        window.draw(background);
        window.draw(hero);
        window.display();
    }

    return 0;
}
