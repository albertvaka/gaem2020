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
#include "tile.h"
#include "door.h"

sf::Font font;
sf::Texture texture;
sf::Sprite sprite;

sf::Clock mainClock;

int countGoods = 0;
int countBads = 0;

void LoadGame(sf::RenderWindow& window)
{
	texture.loadFromFile("data/spritesheet.png");
	font.loadFromFile("data/PressStart2P.ttf");

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));

	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	Input::Init(window);
	Camera::SetZoom(GameData::GAME_ZOOM);
	Camera::SetCameraCenter(vec(GameData::WINDOW_WIDTH / (2*GameData::GAME_ZOOM), GameData::WINDOW_HEIGHT/(2*GameData::GAME_ZOOM)));

	LoadMap();

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
	loadExtremityMap();

#ifdef _DEBUG
	new Cadaver(vec(100, 120));
#endif

}

void DrawGui()
{
#ifdef _DEBUG
	ImGui::Begin(GameData::GAME_TITLE.c_str());

	ImGui::Text(EntS<Player>::getAll()[0]->pos.ToString().c_str());
	if (ImGui::Button("SPAWN CADAVER"))
	{
		for (Spawner* s : EntS<Spawner>::getAll()) {
			s->spawn();
		}
	}

	ImGui::Checkbox("Blood", &withTaca);

	ImGui::Text(std::to_string(EntS<Cadaver>::getAll().size()).c_str());

	ImGui::Text(std::to_string(EntS<Taca>::getAll().size()).c_str());

	if (ImGui::Button("SPAWN ROOMBA"))
	{
		int spawners_count = EntS<CleanerSpawner>::getAll().size();

		int sp = Random::roll(0, spawners_count - 1);

		EntS<CleanerSpawner>::getAll()[sp]->TreuElGos();

	}

	ImGui::End();
#endif
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

		int dt = time.asMilliseconds();
		Mates::ClampMax(dt, 90); //Slow game down instead of epic jumps
		UpdateEntities(dt);


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
