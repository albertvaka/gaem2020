#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <queue>
#include <random>
#include <set>

#include "rand.h"
#include "mates.h"
#include "input.h"
#include "animation.h"

sf::Texture tex_tileset;
sf::Font font;
InputState input_state;

const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 1000;

namespace EntS
{
	enum EntityState
	{
		MOVING,
		COLLIDED
	};

	enum EntityType
	{
		NONE = 0,
		ENTITY_EXAMPLE,

		COUNT
	};
	
#define ENTITY_NUM 3000

	const int MAX_ENTITIES = ENTITY_NUM;
#if true
	EntityType ent_type[MAX_ENTITIES];
	EntityState ent_state[MAX_ENTITIES];
	int pos_x[MAX_ENTITIES];
	int pos_y[MAX_ENTITIES];
	int speed_x[MAX_ENTITIES];
	int speed_y[MAX_ENTITIES];
	int timer[MAX_ENTITIES];
	Animation anim[MAX_ENTITIES];
#else
	vector<EntityType> ent_type(MAX_ENTITIES);
	vector< EntityState> ent_state(MAX_ENTITIES);
	vector<int> pos_x(MAX_ENTITIES);
	vector<int> pos_y(MAX_ENTITIES);
	vector<int> speed_x(MAX_ENTITIES);
	vector<int> speed_y(MAX_ENTITIES);
	vector<int> timer(MAX_ENTITIES);
	vector<Animation> anim(MAX_ENTITIES);
#endif

	int __GetNewID()
	{
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			if (ent_type[i] == EntityType::NONE)
			{
				return i;
			}
		}
		return -1;
	}

	void ResetEntities()
	{
		for (int i = 0; i < EntS::MAX_ENTITIES; i++)
		{
			EntS::ent_type[i] = EntS::NONE;
		}
	}

	int SpawnEntity(EntityType type, int x, int y, int id_parent = -1)
	{
		int id = __GetNewID();
		if (id < 0) return -1;

		ent_type[id] = type;
		pos_x[id] = x;
		pos_y[id] = y;
		speed_x[id] = 0;
		speed_y[id] = 0;

		if (type == ENTITY_EXAMPLE)
		{
			anim[id].Ensure(AnimationType::ANIM_EXAMPLE);
			ent_state[id] = EntityState::MOVING;

			float angle = Dice::rollf(360);

			pos_x[id] = Dice::roll(WINDOW_WIDTH * 99);
			pos_y[id] = Dice::roll(WINDOW_HEIGHT * 99);

			speed_x[id] = cosf(Mates::DegsToRads(angle)) * (1 + Dice::roll(8));
			speed_y[id] = sinf(Mates::DegsToRads(angle)) * (1 + Dice::roll(8));
		}

		anim[id].ResetAnim();

		return id;
	}

	void MoveEntityExample(int id, int dt)
	{
		pos_x[id] += speed_x[id] * dt;
		pos_y[id] += speed_y[id] * dt;

		if (pos_x[id] < 0 && speed_x[id] < 0)
		{
			speed_x[id] = -speed_x[id];
			pos_x[id] = 0;
		}
		if (pos_x[id] > WINDOW_WIDTH * 100 && speed_x[id] > 0)
		{
			speed_x[id] = -speed_x[id];
			pos_x[id] = WINDOW_WIDTH * 100;
		}
		if (pos_y[id] < 0 && speed_y[id] < 0)
		{
			speed_y[id] = -speed_y[id];
			pos_y[id] = 0;
		}
		if (pos_y[id] > WINDOW_HEIGHT * 100 && speed_y[id] > 0)
		{
			speed_y[id] = -speed_y[id];
			pos_y[id] = WINDOW_HEIGHT * 100;
		}
	}

	void UpdateEntityExample(int id, int dt)
	{
		MoveEntityExample(id, dt);
	}

	bool Collision(int a, int b)
	{
		int COLLISION_SIZE = 1600;
		//rectangle colision
		return 
			(pos_x[a] < pos_x[b] + COLLISION_SIZE && pos_x[a] + COLLISION_SIZE > pos_x[b] &&
			pos_y[a] < pos_y[b] + COLLISION_SIZE && pos_y[a] + COLLISION_SIZE > pos_y[b]);
	}

	void UpdateCollisions(int dt)
	{
		//Collisions
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			if (ent_type[i] == EntityType::NONE) continue;

			for (int j = 0; j < MAX_ENTITIES; ++j)
			{
				if (ent_type[j] == EntityType::NONE) continue;
				if (i == j) continue;

				if (ent_type[i] == EntityType::ENTITY_EXAMPLE && 
					ent_type[j] == EntityType::ENTITY_EXAMPLE &&
					Collision(i, j))
				{
					ent_state[i] = EntityState::COLLIDED;
					ent_state[j] = EntityState::COLLIDED;
				}
			}
		}
	}

	void UpdateEntities(int dt)
	{
		for (int id = 0; id < MAX_ENTITIES; ++id)
		{
			ent_state[id] = EntityState::MOVING;
		}
		UpdateCollisions(dt);

		for (int id = 0; id < MAX_ENTITIES; ++id)
		{
			switch (ent_type[id])
			{
				case EntityType::ENTITY_EXAMPLE:
				{
					UpdateEntityExample(id, dt);
				} break;
			}
		}
	}

	void DrawEntities(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		std::vector<int> draw_list;

		for (int id = 0; id < MAX_ENTITIES; ++id)
		{
			if (ent_type[id] != NONE)
			{


				float x = pos_x[id] / 100.0f;
				float y = pos_y[id] / 100.0f;
				spr.setPosition(x, y);

				spr.setTextureRect(sf::IntRect(0,16,16,16));

				if (ent_type[id] == EntityType::ENTITY_EXAMPLE &&
					ent_state[id] == EntityState::COLLIDED)
				{
					spr.setColor(sf::Color::Red);
				}
				else {
					spr.setColor(sf::Color::White);
				}

				wnd.draw(spr);
			}
		}

	}
}

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

const std::string GAME_TITLE = "Selda 2079";

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE);
	LoadGame(window);

	sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(view);

	sf::Clock clk_imgui;
	sf::Clock clk_frame;
	sf::Clock clk_general;

	sf::Clock clk_fps;
	int fps_counter = 0;

	for (int i = 0; i < ENTITY_NUM; ++i)
	{
		float x = ((float)rand() / (WINDOW_WIDTH));
		float y = ((float)rand() / (WINDOW_HEIGHT));
		EntS::SpawnEntity(EntS::EntityType::ENTITY_EXAMPLE, x, y);
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

		EntS::UpdateEntities(dt);

		window.setView(view);

#if _DEBUG
		//DrawImguiCosas();
#endif

		window.clear();

		EntS::DrawEntities(sprite, window);

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
