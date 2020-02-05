#pragma once

#include <vector>

const int TILE_SIZE = 16;

enum class TileType
{
	SIGN_GOOD,
	SIGN_BAD,
	SIGN_RIGHT_LEG,
	SIGN_LEFT_LEG,
	SIGN_LEFT_ARM,
	SIGN_RIGHT_ARM,
	SIGN_HEAD,
	WALL,
	BELT_RIGHT,
	BELT_LEFT,
	BELT_UP,
	BELT_DOWN,
	FLOOR,
	ROOMBA_HOME
};

std::vector< std::vector<TileType> > mapita;
std::vector< std::vector<bool> > passable;
std::vector< std::vector<bool> > passableCleaner;

const std::vector< std::string > mapita_inicial = 
{
	"XXYYYYYYYXwSXXYYYYYYYXX",
	"XX       XDDBX       XX",
	"XY XXXXX XAXBX XXXXX XX",
	"X  k   X XAXBX X   g XX",
	"X  XFKFX YACCY XFGFX XX",
	"XX X   X  1 2  X   X XX",
	"XX YYUYY  0 3  YYyYY XX",
	"XX       XXXXX       XX",
	"XX XXXXX X   X XXXmX XX",
	"XX X   l XFRFX X   X XX",
	"XX XFLFX X   r XFMFX YX",
	"XX X   X YYpYY X   X  X",
	"XX YYPYY       YYuYY  X",
	"XX                   XX",
	"XXXXXXXXXXBBBhXXXXXXXXX",
	"XXXXXXXXXXZZZXXXXXXXXXX",
};

TileType TileFromChar(char c)
{
	switch (c)
	{
		case 'y':
			return TileType::SIGN_HEAD;
		case 'u':
			return TileType::SIGN_RIGHT_ARM;
		case 'U':
			return TileType::SIGN_LEFT_ARM;
		case 'p':
			return TileType::SIGN_RIGHT_LEG;
		case 'P':
			return TileType::SIGN_LEFT_LEG;
		case 'h':
			return TileType::SIGN_GOOD;
		case 'w':
			return TileType::SIGN_BAD;
		case 'X':
		{
			return TileType::WALL;
		} break;
		case 'A':
		{
			return TileType::BELT_UP;
		} break;
		case 'S':
		case 'B':
		case 'T':
		{
			return TileType::BELT_DOWN;
		} break;
		case 'Z':
		case 'C':
		{
			return TileType::BELT_LEFT;
		} break;
		case 'D':
		{
			return TileType::BELT_RIGHT;
		} break;
		case 'Y':
		{
			return TileType::ROOMBA_HOME;
		} break;

	}
	return TileType::FLOOR;
}

ExtremityType letraToExtremity(char c) 
{
	switch (c) 
	{
		case 'G':
		case 'g':
			return ExtremityType::HEAD;
		case 'K':
		case 'k':
			return ExtremityType::LEFT_ARM;
		case 'L':
		case 'l':
			return ExtremityType::LEFT_LEG;
		case 'R':
		case 'r':
			return ExtremityType::RIGHT_LEG;
		case 'M':
		case 'm':
			return ExtremityType::RIGHT_ARM;
	}
}


void LoadMap()
{

	passable.resize(mapita_inicial[0].size(), std::vector<bool>(mapita_inicial.size()));
	passableCleaner.resize(mapita_inicial[0].size(), std::vector<bool>(mapita_inicial.size()));
	mapita.resize(mapita_inicial[0].size(), std::vector<TileType>(mapita_inicial.size()));

	int x = 0, y = 0;
	for (auto row : mapita_inicial)
	{
		for (char c : row)
		{
			passable[x][y] = (c < 'A');
			passableCleaner[x][y] = (c < 'E' || c == 'Z');
			mapita[x][y] = TileFromChar(c);


			vec pos(16 * x, 16 * y);
			switch (c)
			{
			case '0': new Player(0, pos); break;
			case '1': new Player(1, pos); break;
			case '2': new Player(2, pos); break;
			case '3': new Player(3, pos); break;
			case 'A': new Cinta(pos, EntityDirection::UP); break;
			case 'B': new Cinta(pos, EntityDirection::DOWN); break;
			case 'T': new Cinta(pos, EntityDirection::DOWN); break;
			case 'C': new Cinta(pos, EntityDirection::LEFT); break;
			case 'D': new Cinta(pos, EntityDirection::RIGHT); break;
			case 'G':
			case 'K':
			case 'L':
			case 'R':
			case 'M':
				new Mesa(pos, letraToExtremity(c));
				break;

			case 'g':
			case 'k':
			case 'l':
			case 'r':
			case 'm':
				new Collector(pos, letraToExtremity(c));
				break;
			case 'S':
			{
				Spawner *s = new Spawner(pos);
				new Detector(vec(pos.x - 16, pos.y + 16), s);
				new Cinta(pos, EntityDirection::DOWN);
			} break;

			case 'U': //Door: Left Arm
			{
				Door* d = new Door(pos, Door::Panel::LEFT_ARM);
				new DoorSensor(d);
				passable[x][y] = true;
			} break;
			case 'y': //Door: Head
			{
				Door* d = new Door(pos, Door::Panel::HEAD);
				new DoorSensor(d);
				passable[x][y] = true;
			} break;
			case 'P': //Door: Left Leg
			{
				Door* d = new Door(pos, Door::Panel::LEFT_LEG);
				new DoorSensor(d);
				passable[x][y] = true;
			} break;
			case 'p': //Door: Right Leg
			{
				Door* d = new Door(pos, Door::Panel::RIGHT_LEG);
				new DoorSensor(d);
				passable[x][y] = true;
			} break;
			case 'u': //Door: Right Arm
			{
				Door* d = new Door(pos, Door::Panel::RIGHT_ARM);
				new DoorSensor(d);
				passable[x][y] = true;
			} break;

			case 'Z':
			{
				new Despawner(pos);
				new Cinta(pos, EntityDirection::DOWN);
			} break;
			case 'Y':
			{
				new CleanerSpawner(pos);
			} break;

			}



			x += 1;
		}
		y += 1;
		x = 0;
	}

}