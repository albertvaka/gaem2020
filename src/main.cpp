#include <map>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>
#include "entity_system.h"
#include "game_data.h"
#include "input.h"
#include "mates.h"
#include "player.h"
#include "cadaver.h"
#include "spawner.h"
#include "cleaner.h"
#include "mesa.h"


sf::Font font;
sf::Texture texture;
sf::Sprite sprite;

sf::Clock mainClock;

const int TILE_SIZE = 16;

std::vector< std::string > mapita_inicial = {
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

Collector* collectDebug = nullptr;

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
int countGoods = 0;
int countBads = 0;
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

ExtremityType letraToExtremity(char c) {
	switch (c) {
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

#include "door.h"

void LoadGame(sf::RenderWindow& window)
{
	texture.loadFromFile("data/spritesheet.png");
	font.loadFromFile("data/PressStart2P.ttf");

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
	
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	Input::Init(window);
	Camera::SetZoom(4.f);
	Camera::SetCameraCenter(vec(GameData::WINDOW_WIDTH / 8, GameData::WINDOW_HEIGHT/8));

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
				case 'A': new Cinta(pos, EntityDirection::UP); passable[x][y] = true; break;
				case 'B': new Cinta(pos, EntityDirection::DOWN); passable[x][y] = true; break;
				case 'T': new Cinta(pos, EntityDirection::DOWN); passable[x][y] = true; break;
				case 'C': new Cinta(pos, EntityDirection::LEFT); passable[x][y] = true; break;
				case 'D': new Cinta(pos, EntityDirection::RIGHT); passable[x][y] = true; break;
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
					if (c == 'k') collectDebug = new Collector(pos, letraToExtremity(c));
					else new Collector(pos, letraToExtremity(c));;
					break;
				case 'S':
				{
					CadaverSpawner *s = new CadaverSpawner(pos + vec(8, 8));
					new Detector(vec(pos.x - 16, pos.y + 16), s);
					new Cinta(pos, EntityDirection::DOWN);
				} break;

				case 'U': //Door: Left Arm
				{
					Door* d = new Door(pos, Door::Panel::LEFT_ARM);
					DoorSensor* ds = new DoorSensor(d);
					passable[x][y] = true;
				} break;
				case 'y': //Door: Head
				{
					Door* d = new Door(pos, Door::Panel::HEAD);
					DoorSensor* ds = new DoorSensor(d);
					passable[x][y] = true;
				} break;
				case 'P': //Door: Left Leg
				{
					Door* d = new Door(pos, Door::Panel::LEFT_LEG);
					DoorSensor* ds = new DoorSensor(d);
					passable[x][y] = true;
				} break;
				case 'p': //Door: Right Leg
				{
					Door* d = new Door(pos, Door::Panel::RIGHT_LEG);
					DoorSensor* ds = new DoorSensor(d);
					passable[x][y] = true;
				} break;
				case 'u': //Door: Right Arm
				{
					Door* d = new Door(pos, Door::Panel::RIGHT_ARM);
					DoorSensor* ds = new DoorSensor(d);
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

	for (Collector* c : EntS<Collector>::getAll()) 
	{
		for (Mesa* m : EntS<Mesa>::getAll()) 
		{
			if (m->type == c->type) 
			{
				m->collector = c;
				c->mesa = m;
			}
		}
	}

#ifdef _DEBUG
	//new Cadaver(100, 100);
#endif
	loadExtremityMap();
	
}

void DrawGui()
{
#ifdef _DEBUG
	ImGui::Begin(GameData::GAME_TITLE.c_str());

	ImGui::Text(EntS<Player>::getAll()[0]->pos.ToString().c_str());
	if (ImGui::Button("SPAWN CADAVER"))
	{
		for (CadaverSpawner* s : EntS<CadaverSpawner>::getAll()) 
		{
			s->spawn();
		}
	}

	ImGui::Checkbox("Blood", &withTaca);
	ImGui::Text(std::to_string(!!collectDebug->extremity).c_str());

	ImGui::Text(std::to_string(EntS<Cadaver>::getAll().size()).c_str());

	ImGui::Text(std::to_string(EntS<Taca>::getAll().size()).c_str());

	if (ImGui::Button("SPAWN ROOMBA"))
	{
		int spawners_count = EntS<CleanerSpawner>::getAll().size();

		int sp = Random::roll(0, spawners_count);

		EntS<CleanerSpawner>::getAll()[sp]->TreuElGos();

	}

	ImGui::End();
#endif
}


sf::IntRect SelectTileWallWithBorders(int i, int j)
{
	return (sf::IntRect(64 + 16, 48, 16, 16));

	

	if (i == 1 && j == 0)
	{
		int asdf = 0;
	}

	bool isFloor[3][3];
	for (int ii = -1; ii < 2; ++ii)
	{
		for (int jj = -1; jj < 2; ++jj)
		{
			int x = i + ii;
			int y = j + jj;

			if (x < 0 || x >= mapita.size() ||
				y < 0 || y >= mapita[x].size())
			{
				isFloor[1 + ii][1 + jj] = false;
			}
			else
			{
				isFloor[1 + ii][1 + jj] = (mapita[x][y] == TileType::FLOOR);
			}
		}
	}

	bool TL = isFloor[0][0];
	bool T = isFloor[1][0];
	bool TR = isFloor[2][0];

	bool L = isFloor[0][1];
	bool R = isFloor[2][1];

	bool BL = isFloor[2][2];
	bool B = isFloor[2][2];
	bool BR = isFloor[2][2];

	if (T && !L && !R && !B)
	{
		return (sf::IntRect(48, 208, 16, 16));
	}
	if (!T && L && !R && !B)
	{
		return (sf::IntRect(32, 224, 16, 16));
	}
	if (!T && !L && R && !B)
	{
		return (sf::IntRect(64, 224, 16, 16));
	}
	if (!T && !L && !R && B)
	{
		return (sf::IntRect(48, 240, 16, 16));
	}


	return (sf::IntRect(64 + 16, 48, 16, 16));

}

void drawTile(sf::Sprite& sprite, sf::RenderTarget& window, int i, int j)
{
	int time = mainClock.getElapsedTime().asMilliseconds();
	TileType type = mapita[i][j];
	sprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);

	switch (type) {
	case TileType::ROOMBA_HOME:
	{
		sprite.setTextureRect(sf::IntRect(0, 13 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
	} break;
	case TileType::SIGN_GOOD:
		sprite.setTextureRect(sf::IntRect(5*16, 10 * 16, 16, 16));
		break;
	case TileType::SIGN_BAD:
		sprite.setTextureRect(sf::IntRect(6 * 16, 10 * 16, 16, 16));
		break;
		/* DEPRECATED
	case TileType::SIGN_HEAD:
		sprite.setTextureRect(sf::IntRect(0 * 16, 10 * 16, 16, 16));
		break;
	case TileType::SIGN_LEFT_ARM:
		sprite.setTextureRect(sf::IntRect(1 * 16, 10 * 16, 16, 16));
		break;
	case TileType::SIGN_RIGHT_ARM:
		sprite.setTextureRect(sf::IntRect(2 * 16, 10 * 16, 16, 16));
		break;
	case TileType::SIGN_LEFT_LEG:
		sprite.setTextureRect(sf::IntRect(3 * 16, 10 * 16, 16, 16));
		break;
	case TileType::SIGN_RIGHT_LEG:
		sprite.setTextureRect(sf::IntRect(4 * 16, 10 * 16, 16, 16));
		break;
		*/
	case TileType::FLOOR:
		sprite.setTextureRect(sf::IntRect(64, 48, 16, 16));
		break;
	case TileType::WALL:
	{
		sprite.setTextureRect(SelectTileWallWithBorders(i, j));
	} break;
	case TileType::BELT_DOWN:
		sprite.setTextureRect(Animation::AnimFrame(AnimationType::BELT_RIGHT, time));
		sprite.setOrigin(0, 16);
		sprite.setRotation(90);
		break;
	case TileType::BELT_UP:
		sprite.setTextureRect(Animation::AnimFrame(AnimationType::BELT_RIGHT, time));
		sprite.setOrigin(16, 0);
		sprite.setRotation(-90);
		break;
	case TileType::BELT_LEFT:
		sprite.setTextureRect(Animation::AnimFrame(AnimationType::BELT_RIGHT, time));
		sprite.setOrigin(16, 16);
		sprite.setRotation(180);
		break;
	case TileType::BELT_RIGHT:
		sprite.setTextureRect(Animation::AnimFrame(AnimationType::BELT_RIGHT, time));
		break;
	}
	window.draw(sprite);
	sprite.setRotation(0);
	sprite.setOrigin(0, 0);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(GameData::WINDOW_WIDTH, GameData::WINDOW_HEIGHT), GameData::GAME_TITLE);
	LoadGame(window);

	int fps_counter = 0;
	sf::Clock dtClock;
	sf::Clock fpsClock;

	sf::Text txt_fps;
	txt_fps.setPosition(10, 10);
	txt_fps.setFont(font);

	while (window.isOpen()) 
	{
		sf::Time time = dtClock.restart();

		Input::Update(time);

		//#if _DEBUG
		//Camera::MoveCameraWithArrows(50, time.asSeconds());
		//Camera::ChangeZoomWithPlusAndMinus(0.5f, time.asSeconds());
		//#endif

		UpdateEntities(time.asMilliseconds());


		window.clear(sf::Color(64, 64, 64));


		for (int i = 0; i < mapita.size(); ++i)
		{
			for (int j = 0; j < mapita[i].size(); ++j)
			{
				drawTile(sprite, window, i, j);

			}
		}

		DrawEntities(sprite, window);
		//DrawEntities(texture, window);

		Camera::StartGuiDraw();
		DrawGui();
		ImGui::SFML::Render(window);
#ifdef _DEBUG
		fps_counter++;
		if (fpsClock.getElapsedTime().asSeconds() > 0.5f) 
		{
			txt_fps.setString(std::to_string(static_cast<int>(fps_counter / fpsClock.restart().asSeconds())));
			fps_counter = 0;
		}
		window.draw(txt_fps);
#endif
		Camera::EndGuiDraw();
		
		window.display();
	}

	ImGui::SFML::Shutdown();
}
