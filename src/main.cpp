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

std::vector< std::string > mapita = { // (23 * 17 tiles)
"XXXXXXXXXXXBXXXXXXXXXXX",
"XXXXXXXXXXDDBXXEEEEEXXX",
"XX0      XAXBXXE   EXXX",
"XX XXFXX XAXBX       XX",
"XE X F X XACCX XXXXX XX",
"XE X G X XX XX FF  X XX",
"XX X   X EE    X G   XX",
"XX XX XX    EE X   X XX",
"XX       XX XX XXXXX XX",
"XX XXXXX X  FF       XX",
"XX X   X X G X XXXXX XX",
"XX   G X X   X X   X XX",
"XX X  FF XXXXX X G X EE",
"XX XXXXX XEEEX FF  X EE",
"XX             XX XX XX",
"XXXXXXXXXXXBX        XX",
"CCCCCCCCCCCCXXXXXXXXXXX",

};

std::vector< std::vector<bool> > passable;

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

	passable.resize(mapita[0].size(), std::vector<bool>(mapita.size()));

	int x = 0, y = 0;
	for (auto row : mapita) {
		for (char c : row) {
			vec pos(16 * x, 16 * y);
			switch (c) {
				case '0': new Player(0, pos); break;
				case '1': new Player(1, pos); break;
				case '2': new Player(2, pos); break;
				case '3': new Player(3, pos); break;
				case 'X': new Pared(pos); break;
				case 'A': new Cinta(pos, EntityDirection::UP); break;
				case 'B': new Cinta(pos, EntityDirection::DOWN); break;
				case 'C': new Cinta(pos, EntityDirection::LEFT); break;
				case 'D': new Cinta(pos, EntityDirection::RIGHT); break;
			}
			passable[x][y] = (c != 'X');
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

		new Cadaver(200,200);
	}
	if (ImGui::Button("SPAWN PLAYER"))
	{
		static int count = 4;
		new Player(count++, vec::Rand(16, 16, GameData::WINDOW_WIDTH - 16, GameData::WINDOW_HEIGHT - 16));
	}
	ImGui::Text(std::to_string(Camera::GetCameraCenter().x).c_str());

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

		//#if _DEBUG
		//Camera::MoveCameraWithArrows(50, time.asSeconds());
		//Camera::ChangeZoomWithPlusAndMinus(0.5f, time.asSeconds());
		//#endif

		UpdateEntities(time.asMilliseconds());

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
