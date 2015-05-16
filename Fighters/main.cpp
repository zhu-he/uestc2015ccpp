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

using namespace std;

int main()
{
	srand((int)time(0));
	SpriteSheet::loadFromFile(packPath);
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fighters");
    Stage stage(window);
    Background background;
    Hero hero;
    stage.addEntity(&background);
    stage.addEntity(&hero);
    sf::SoundBuffer buffer;
    buffer.loadFromFile(gameMusicPath);
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    sf::Clock enemyClock;
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
		if (enemyClock.getElapsedTime() >= sf::seconds(enemySpawnTime))
		{
			Enemy* enemy = new Enemy(rand() % 3);
            stage.addEntity(enemy);
            enemyClock.restart();
		}
        stage.update();
    }
    return 0;
}
