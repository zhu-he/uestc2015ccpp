#include <ctime>
#include "SpriteSheet.hpp"
#include "Background.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Global.hpp"
#include "Ufo.hpp"
#include "Game.hpp"

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
    Game game;
    game.play();
    return 0;
}
