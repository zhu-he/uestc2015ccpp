#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#include <string>
#include <vector>
#include <functional>
#include <cmath>

enum GameStatus
{
	Waiting,
	Playing,
	Pausing,
	Over
};

enum Status
{
	Normal,
	Hit,
	Dying
};

enum BulletType
{
	HeroBullet,
	EnemyBullet
};

const float PI = acos(-1);

const int screenWidth = 480;

const int screenHeight = 800;

const std::string fontPath = "resources/font/STHeiti Light.ttc";

const std::string gameMusicPath = "resources/sound/game_music.ogg";

const std::string gameOverPath = "resources/sound/game_over.ogg";

const std::string bulletSoundPath = "resources/sound/bullet.ogg";

const std::string backgroundImagePath = "resources/image/background.png";

const std::string packPath = "resources/image/shoot.pack";

const std::vector<std::string> heroImage =
{
	"hero1",
	"hero2"
};

const std::vector<std::string> heroBlowupImage =
{
	"hero_blowup_n1",
	"hero_blowup_n2",
	"hero_blowup_n3",
	"hero_blowup_n4"
};

const std::vector<std::string> bulletImage =
{
	"bullet1",
	"bullet2"
};

const std::vector<std::vector<std::string> > enemyImage =
{
	{
		"enemy1"
	},
	{
		"enemy2"
	},
	{
		"enemy3_n1",
		"enemy3_n2"
	}
};

const std::vector<std::string> enemyHitImage =
{
	"",
	"enemy2_hit",
	"enemy3_hit"
};

const std::vector<std::string> enemyDownSoundPath =
{
	"resources/sound/enemy1_down.ogg",
	"resources/sound/enemy2_down.ogg",
	"resources/sound/enemy3_down.ogg"
};

const std::vector<std::vector<std::string> > enemyDownImage =
{
	{
		"enemy1_down1",
		"enemy1_down2",
		"enemy1_down3",
		"enemy1_down4"
	},
	{
		"enemy2_down1",
		"enemy2_down2",
		"enemy2_down3",
		"enemy2_down4"
	},
	{
		"enemy3_down1",
		"enemy3_down2",
		"enemy3_down3",
		"enemy3_down4",
		"enemy3_down5",
		"enemy3_down6"
	}
};

const std::vector<int> enemyHp =
{
	1,
	3,
	10
};

const std::vector<int> enemyScore =
{
	1,
	2,
	5
};

const std::vector<float> enemySpeed =
{
	3.0f,
	2.5f,
	2.0f
};

const float heroSpeed = 8.0f;

const float backgroundSpeed = 2.0f;

const std::vector<float> bulletSpeed =
{
	20.0f,
	4.0f
};

const float heroBulletInterval = 0.2f;

const std::vector<float> enemyBulletInterval =
{
	0.6f,
	0.6f,
	0.6f
};

const std::vector<std::vector<float> > enemyBulletDirection =
{
	{
		-20, 0, 20
	},
	{
		-40, -20, 0, 20, 40
	},
	{
		-60, -40, -20, 0, 20, 40, 60
	}
};

const float bulletOffsetY = -60.0f;

const float enemySpawnTime = 2.0f;

const float animateInterval = 0.05f;

const float enemyFireDistance = 200.0f;

const float waitingFlashInterval = 0.5f;

const int heroHp = 3;

const float invincibleTime = 2.0f;

const float invincibleFlashInterval = 0.08f;

#endif // GLOBAL_HPP_INCLUDED
