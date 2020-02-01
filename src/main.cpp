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
#include "pared.h"

sf::Font font;
sf::Texture texture;
sf::Sprite sprite;

std::vector< std::string > mapita = { // (30 * 15 tiles)
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
"X             X              X",
"X     0       X   X          X",
"X          XXXX   X          X",
"X                 X  X       X",
"XXXXX             X  X       X",
"X                 X  X       X",
"X    XXXXXXXXXXXXXX  X       X",
"X                            X",
"X     XXXXX XXXXXXXXXX       X",
"X         X X                X",
"X     XXXXX XXXXX            X",
"X                     X      X",
"X    XXXXXX XXXX             X",
"X         X X                X",
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
};

<<<<<<< HEAD
std::vector< std::vector<bool> > passable;
=======
>>>>>>> deprecated map (before born)

void LoadGame(sf::RenderWindow& window)
{
	texture.loadFromFile("data/spritesheet.png");
	font.loadFromFile("data/PressStart2P.ttf");

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
	sprite.setScale(4, 4);
	
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	Input::Init(window);

	passable.resize(mapita[0].size(), std::vector<bool>(mapita.size()));

	int x = 0, y = 0;
	for (auto row : mapita) {
		for (char c : row) {
			vec pos(6400 * x, 6400 * y);
			switch (c) {
				case '0': new Player(0, pos); break;
				case '1': new Player(1, pos); break;
				case '2': new Player(2, pos); break;
				case '3': new Player(3, pos); break;
				case 'X': new Pared(pos); break;
			}
			passable[x][y] = (c < 'A');
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

		new Cadaver(700, 700);
	}
	if (ImGui::Button("SPAWN PLAYER"))
	{
		static int count = 4;
		new Player(count++, vec::Rand(1600, 1600, GameData::WINDOW_WIDTH * 98, GameData::WINDOW_HEIGHT*98));
	}

	ImGui::End();
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

		UpdateEntities(time.asMilliseconds());

		DrawEntities(sprite, window);

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
