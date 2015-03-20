#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
	#include <conio.h>
	#define GETCH() _getch()
	#define INIT()
	#define END()
	inline void clearScreen()
	{
		system("cls");
	}
#else
	#include <curses.h>
	#define GETCH() getch()
	#define INIT() initscr()
	#define END() endwin()
	inline void clearScreen()
	{
		system("clear");
	}
#endif

struct Point
{
	int x, y;
	Point(int x = 0, int y = 0): x(x), y(y) {}
	bool operator == (const Point &pos) const
	{
		return x == pos.x && y == pos.y;
	}
	Point operator + (const Point &pos) const
	{
		return Point(x + pos.x, y + pos.y);
	}
};

const int levelCount = 2;
const int width[levelCount] = {8, 8};
const int height[levelCount] = {8, 9};
const int maxWidth = 100;
const int maxHeight = 100;
const Point delta[4] =
{
	Point(-1, 0),
	Point(1, 0),
	Point(0, -1),
	Point(0, 1)
};

const Point startPos[levelCount] =
{
	Point(4, 4),
	Point(2, 2)
};

const char sokoban[levelCount][maxHeight][maxWidth] =
{
	{
		"  ###   ",
		"  #a#   ",
		"  # ####",
		"###   a#",
		"#a   ###",
		"#### #  ",
		"   #a#  ",
		"   ###  "
	},
	{
		"  ##### ",
		"###   # ",
		"#a    # ",
		"###  a# ",
		"#a##  # ",
		"# # a ##",
		"#  a  a#",
		"#   a  #",
		"########"
	}
};

const char box[levelCount][maxHeight][maxWidth] =
{
	{
		"        ",
		"        ",
		"        ",
		"   O O  ",
		"   O    ",
		"    O   ",
		"        ",
		"        "
	},
	{
		"        ",
		"        ",
		"   O    ",
		"    O   ",
		"    O   ",
		"        ",
		" O OOO  ",
		"        ",
		"        "
	}
};

enum Direction
{
	NONE = -1,
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

enum Movement
{
	INVAILD,
	MOVE,
	PUSH,
};

Point playerPos;
int currentLevel = 0;
int step = 0;
char currentBox[maxHeight][maxWidth];

inline void changeLevel(int level);
inline void showSokoban();
inline void clearScreen();
inline Direction getDirection();
inline Movement tryMove(Direction direction);
inline bool isSuccess();

inline void changeLevel(int level)
{
	currentLevel = level;
	memcpy(currentBox, box[level], sizeof(currentBox));
	playerPos = startPos[level];
	step = 0;
}

inline void showSokoban()
{
	clearScreen();
	printf("Level: %d Step: %d\n", currentLevel, step);
	for (int i = 0; i < height[currentLevel]; ++i)
	{
		for (int j = 0; j < width[currentLevel]; ++j)
		{
			if (playerPos.x == i && playerPos.y == j)
			{
				putchar('P');
			}
			else if (currentBox[i][j] == 'O')
			{
				if (sokoban[currentLevel][i][j] == 'a')
				{
					putchar('@');
				}
				else
				{
					putchar('O');
				}
			}
			else
			{
				putchar(sokoban[currentLevel][i][j]);
			}
		}
		putchar('\n');
	}
	printf("\nPress w, s, a, d to move, press r to restart.\n\nW: Wall\nP: Player\nO: Box\na: Target\n@: Box on target\n");
}

inline Direction getDirection()
{
	char c = GETCH();
	switch (c)
	{
	case 'w':
	case 'W':
		return UP;
	case 's':
	case 'S':
		return DOWN;
	case 'a':
	case 'A':
		return LEFT;
	case 'd':
	case 'D':
		return RIGHT;
	case 'r':
	case 'R':
		changeLevel(currentLevel);
		showSokoban();
		return NONE;
	default:
		return NONE;
	}
}

inline Movement tryMove(Direction direction)
{
	Point nextPos = playerPos + delta[direction];
	if (sokoban[currentLevel][nextPos.x][nextPos.y] == '#')
	{
		return INVAILD;
	}
	if (currentBox[nextPos.x][nextPos.y] == ' ')
	{
		playerPos = nextPos;
		return MOVE;
	}
	Point nextNextPos = nextPos + delta[direction];
	if (sokoban[currentLevel][nextNextPos.x][nextNextPos.y] == '#' ||
		currentBox[nextNextPos.x][nextNextPos.y] != ' ')
	{
		return INVAILD;
	}
	playerPos = nextPos;
	currentBox[nextPos.x][nextPos.y] = ' ';
	currentBox[nextNextPos.x][nextNextPos.y] = 'O';
	return PUSH;
}

inline bool isSuccess()
{
	for (int i = 0; i < height[currentLevel]; ++i)
	{
		for (int j = 0; j < width[currentLevel]; ++j)
		{
			if (currentBox[i][j] == 'O' && sokoban[currentLevel][i][j] != 'a')
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	INIT();
	for (int level = 0; level < levelCount; ++level)
	{
		changeLevel(level);
		showSokoban();
		bool success = false;
		while (!success)
		{
			Direction nextDirection = getDirection();
			if (nextDirection != NONE)
			{
				Movement nextMovement = tryMove(nextDirection);
				if (nextMovement != INVAILD)
				{
					if (nextMovement == PUSH)
					{
						success = isSuccess();
					}
					step++;
					showSokoban();
				}
			}
		}
		printf("\nYou win! Press any key to next level.\n");
		GETCH();
	}
	END();
	return 0;
}
