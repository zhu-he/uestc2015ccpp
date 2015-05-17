#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#include <string>
#include <vector>

enum Status
{
	Normal,
	Hit,
	Dying
};

const int screenWidth = 360;

const int screenHeight = 600;

const std::string fontPath = "resources/font/STHeiti Light.ttc";

const std::string gameMusicPath = "resources/sound/game_music.ogg";

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
	2,
	5
};

const std::vector<int> enemyScore =
{
	1,
	2,
	5
};

const std::vector<float> enemySpeed =
{
	0.1f,
	0.1f,
	0.1f
};

const float heroSpeed = 0.2f;

const float backgroundSpeed = 0.05f;

const float bulletSpeed = 0.5f;

const float bulletInterval = 0.2f;

const float bulletOffsetY = 5.0f;

const float enemySpawnTime = 0.1f;

const float animateInterval = 0.05f;

#endif // GLOBAL_HPP_INCLUDED
