#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <queue>
#include <random>
#include <set>

#include "animation.h"
#include "entity_system.h"
#include "game_data.h"
#include "input.h"
#include "mates.h"
#include "rand.h"

sf::Texture tex_tileset;
sf::Font font;
InputState input_state;

sf::Texture texture;
sf::Sprite sprite;

void LoadGame(sf::RenderWindow& window)
{
	texture.loadFromFile("data/spritesheet.png");
	font.loadFromFile("data/PressStart2P.ttf");

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
	
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	input_state.RemapInput();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(GameData::WINDOW_WIDTH, GameData::WINDOW_HEIGHT), GameData::GAME_TITLE);
	LoadGame(window);

	sf::View view(sf::FloatRect(0, 0, GameData::WINDOW_WIDTH, GameData::WINDOW_HEIGHT));
	window.setView(view);

	sf::Clock clk_imgui;
	sf::Clock clk_frame;
	sf::Clock clk_general;

	sf::Clock clk_fps;
	int fps_counter = 0;

	for (int i = 0; i < 1000; ++i)
	{
		new EntityExample();
	}

	while (window.isOpen()) 
	{
		int time_general = clk_general.getElapsedTime().asMilliseconds();
		int dt = clk_frame.getElapsedTime().asMilliseconds();
		clk_frame.restart();

		sf::Event event;
		while (window.pollEvent(event)) 
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
		}

		input_state.UpdateInput();
		ImGui::SFML::Update(window, clk_imgui.restart());

		UpdateEntities(dt);

		window.setView(view);

#if _DEBUG
		//DrawImguiCosas();
#endif

		window.clear();

		DrawEntities(sprite, window);

		window.setView(window.getDefaultView());

		sf::Text txt_fps;
		txt_fps.setString(std::to_string(static_cast<int>(fps_counter / clk_fps.getElapsedTime().asSeconds())));
		txt_fps.setPosition(10, 10);
		txt_fps.setFont(font);
		window.draw(txt_fps);
		fps_counter++;

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
