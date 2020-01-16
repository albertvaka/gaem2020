#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "entity_system.h"
#include "game_data.h"
#include "input.h"
#include "mates.h"

sf::Font font;
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

	Input::Init(window);
}

void DrawGui()
{
	ImGui::Begin(GameData::GAME_TITLE.c_str());

	if (ImGui::Button("SPAWN BOLA"))
	{
		new EntityExample();
	}
	if (ImGui::Button("KILL BOLA"))
	{
		if (EntS<EntityExample>::getAll().size()) {
			delete EntS<EntityExample>::getAll()[0];
		}
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

	for (int i = 0; i < 100; ++i)
	{
		new EntityExample();
	}

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
		if (fpsClock.getElapsedTime().asSeconds() > 0.5f) {
			txt_fps.setString(std::to_string(static_cast<int>(fps_counter / fpsClock.restart().asSeconds())));
			fps_counter = 0;
		}
		window.draw(txt_fps);
		Camera::EndGuiDraw();

		window.display();
	}

	ImGui::SFML::Shutdown();
}
