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

std::vector< std::string > mapita_inicial = { // (23 * 16 tiles)
"XXXXXXXXXXXSXXXXXXXXXXX",
"XXR      XDDBX       XX",
"XX XXXXX XAXBX XXXXX XX",
"X  X   X XAXBX X   X XX",
"X  XFGFX XACCX XFGFX XX",
"XX X   X  1 2  X   X XX",
"XX XX XX  0 3  XX XX XX",
"XX       XXXXX       XX",
"XX XXXXX X   X XXXXX XX",
"XX X   X XFGFX X   X XX",
"XX XFGFX X   X XFGFX XX",
"XX X   X XX XX X   X  X",
"XX XX XX       XX XX  X",
"XX                  RXX",
"XXXXXXXXXXBBBXXXXXXXXXX",
"XXXXXXXXXXTTTXXXXXXXXXX",
"XXXXXXXXXQ    XXXXXXXXX",
"XXXXXXXXXXXXXXXXXXXXXXX",
};

enum class TileType
{
	WALL,
	BELT_RIGHT,
	BELT_LEFT,
	BELT_UP,
	BELT_DOWN,
	FLOOR
};

std::vector< std::vector<TileType> > mapita;

std::vector< std::vector<bool> > passable;
std::vector< std::vector<bool> > passableCleaner;

TileType TileFromChar(char c)
{
	switch (c)
	{
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

	}
	return TileType::FLOOR;
}

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

	initMesaVector();

	passable.resize(mapita_inicial[0].size(), std::vector<bool>(mapita_inicial.size()));
	passableCleaner.resize(mapita_inicial[0].size(), std::vector<bool>(mapita_inicial.size()));
	mapita.resize(mapita_inicial[0].size(), std::vector<TileType>(mapita_inicial.size()));

	int x = 0, y = 0;
	for (auto row : mapita_inicial) 
	{
		for (char c : row) 
		{
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
				case 'G': new Mesa(pos); break;
				case 'S': 
					new Spawner(pos); 
					new Cinta(pos, EntityDirection::DOWN); 
					break;
				case 'Z':
					new Despawner(pos);
					new Cinta(pos, EntityDirection::LEFT);
					break;
				case 'R':
				case 'Q':
					new Cleaner(pos);
					break;
				
			}


			passable[x][y] = (c < 'A');
			passableCleaner[x][y] = (c < 'E' || c =='R' || c == 'Q');

			mapita[x][y] = TileFromChar(c);
			x += 1;
		}
		y += 1;
		x = 0;
	}

	loadExtremityMap();
	
}

void DrawGui()
{
	ImGui::Begin(GameData::GAME_TITLE.c_str());

	ImGui::Text(EntS<Player>::getAll()[0]->pos.ToString().c_str());
	if (ImGui::Button("SPAWN CADAVER"))
	{
		for (Spawner* s : EntS<Spawner>::getAll()) {
			s->spawn();
		}
	}
	ImGui::Text(std::to_string(EntS<Cadaver>::getAll().size()).c_str());

	ImGui::End();
}

void drawTile(sf::Sprite& sprite, sf::RenderTarget& window, int i, int j)
{
	int time = mainClock.getElapsedTime().asMilliseconds();
	TileType type = mapita[i][j];
	sprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
	switch (type) {
	case TileType::FLOOR:
		sprite.setTextureRect(sf::IntRect(64, 48, 16, 16));
		break;
	case TileType::WALL:
		sprite.setTextureRect(sf::IntRect(64+16, 48, 16, 16));
		break;
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
		fps_counter++;
		if (fpsClock.getElapsedTime().asSeconds() > 0.5f) 
		{
			txt_fps.setString(std::to_string(static_cast<int>(fps_counter / fpsClock.restart().asSeconds())));
			fps_counter = 0;
		}
		window.draw(txt_fps);
		Camera::EndGuiDraw();
		
		window.display();
	}

	ImGui::SFML::Shutdown();
}
