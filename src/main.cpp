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
#include "persona.h"
#include "pared.h"

sf::Font font;
sf::Texture texture;
sf::Sprite sprite;

std::vector< std::string > mapita = { // (30 * 15 tiles)
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
"X          X                 X",
"X     0    X                 X",
"X          X                 X",
"X          X                 X",
"XXXXXXXXXXXX                 X",
"X                            X",
"X                            X",
"X                            X",
"X                            X",
"X                            X",
"X                            X",
"X                            X",
"X                            X",
"X                            X",
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
};



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

	vec pos(0, 0);
	for (auto row : mapita) {
		for (char c : row) {
			switch (c) {
				case '0': new Player(0, pos); break;
				case '1': new Player(1, pos); break;
				case '2': new Player(2, pos); break;
				case '3': new Player(3, pos); break;
				case 'X': new Pared(pos); break;
			}
			pos.x += 6400;
		}
		pos.y += 6400;
		pos.x = 0;

	}
}

void DrawGui()
{
	ImGui::Begin(GameData::GAME_TITLE.c_str());

	ImGui::Text(EntS<Player>::getAll()[0]->pos.ToString().c_str());
	if (ImGui::Button("SPAWN PERSONA"))
	{

		new Persona(350, 350);
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

	new Persona(300, 300);

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
