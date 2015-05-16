#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <string>
#include <vector>

const int screenWidth = 360;

const int screenHeight = 600;

const std::string backGroundImage = "resources/image/background.png";

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
}

const float heroSpeed = 0.2f;

const float backgroundSpeed = 0.1f;

#endif // GLOBAL_H_INCLUDED
