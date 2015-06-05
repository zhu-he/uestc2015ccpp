#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include "SpriteSheet.hpp"
#include "Background.hpp"
#include "Hero.hpp"
#include "Hero2.hpp"
#include "Enemy.hpp"
#include "Ufo.hpp"
#include "Game.hpp"
#include "Sound.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "PausableClock.hpp"

using namespace std;

PausableClock gameClock;

void init();

int main()
{
	init();
	Game game;
    game.play();
    return 0;
}

void init()
{
	srand((int)time(0));
	SpriteSheet::loadFromFile(packPath);
	Hero::loadResources();
	Enemy::loadResources();
	Bullet::loadResources();
	Ufo::loadResources();
	Sound::loadResources();
	Font::loadResources();
	Shader::loadResources();
	Hero2::loadResources();
	Background::loadResources();
}
