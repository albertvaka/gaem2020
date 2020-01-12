#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <queue>
#include <random>
#include <set>


sf::Texture tex_tileset;

sf::Font font;

enum class GameKeys
{
	UP = 0, DOWN, LEFT, RIGHT,
	ACTION, START,
	COUNT
};
struct InputState
{
	std::map<GameKeys, sf::Keyboard::Key> input_map;
	bool isPressed[(int)GameKeys::COUNT];
	bool wasPressed[(int)GameKeys::COUNT];

	bool IsPressed(GameKeys key)
	{
		return isPressed[static_cast<int>(key)];
	}

	bool IsJustPressed(GameKeys key)
	{
		return !wasPressed[static_cast<int>(key)] && isPressed[static_cast<int>(key)];
	}

	void RemapInput()
	{
		input_map[GameKeys::UP] = sf::Keyboard::Key::W;
		input_map[GameKeys::DOWN] = sf::Keyboard::Key::S;
		input_map[GameKeys::LEFT] = sf::Keyboard::Key::A;
		input_map[GameKeys::RIGHT] = sf::Keyboard::Key::D;
		input_map[GameKeys::ACTION] = sf::Keyboard::Key::P;
		input_map[GameKeys::START] = sf::Keyboard::Key::Enter;
	}

	void UpdateInput()
	{
		for (const auto& kv : input_map)
		{
			int key = (int)kv.first;
			wasPressed[key] = isPressed[key];
			isPressed[key] = sf::Keyboard::isKeyPressed(kv.second);
		}
	}
};
InputState input_state;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 720;

enum AnimationType
{
	NONE,
	ANIM_EXAMPLE
};

struct AnimationData
{
	int frames;
	sf::IntRect anim_frames[16];
	int frame_timer[16];
};

AnimationData anim_lib[] =
{
	//NONE
	{
		1,
		{
			{0,0,0,0},
		},
		0
	},
	//ANIM_EXAMPLE
	{   1, 
		{ 
			{1 * 16, 1 * 16, 16, 16},
		}, 
		{
			100
		},
	}
};


struct Animation
{
	AnimationType anim_type;
	int anim_timer;
	int current_frame;

	void Update(int dt)
	{
		anim_timer += dt;

		AnimationData* anim_data = &anim_lib[(int)anim_type];

		if (anim_timer > anim_data->frame_timer[current_frame])
		{
			anim_timer -= anim_data->frame_timer[current_frame];

			current_frame++;
			if (current_frame >= anim_data->frames)
			{
				//current_frame = 0;
			}
		}
	}

	void ResetAnim()
	{
		anim_timer = 0;
		current_frame = 0;
	}

	void Ensure(AnimationType type)
	{
		if (anim_type != type)
		{
			anim_type = type;
			ResetAnim();
		}
	}

	sf::IntRect CurrentFrame()
	{
		AnimationData* anim_data = &anim_lib[(int)anim_type];
		return anim_data->anim_frames[current_frame];
	}

	static sf::IntRect AnimFrame(AnimationType type, int timer)
	{
		AnimationData* anim_data = &anim_lib[(int)type];

		int time_total = 0;
		for (int i = 0; i < anim_data->frames; ++i)
		{
			time_total += anim_data->frame_timer[i];
		}

		timer = timer % time_total;

		int current_frame = 0;
		while (timer > anim_data->frame_timer[current_frame])
		{
			timer -= anim_data->frame_timer[current_frame];
			current_frame++;
		}
		return anim_data->anim_frames[current_frame];
	}
};


enum class TileType
{
	NONE,
	TILE_EXAMPLE
};


struct Tile
{
	TileType type;
	int tp_x = -1;
	int tp_y = -1;

	void ResetTile()
	{
		type = TileType::NONE;
		tp_x = -1;
		tp_y = -1;
	}
};



enum PlayerState
{
	IDLE,
	WALKING
};

namespace EntS
{
	const int MAX_ENTITIES = 2048;
	enum EntityType
	{
		NONE = 0,
		ENTITY_EXAMPLE,

		COUNT
	};
	
	EntityType ent_type[MAX_ENTITIES];
	PlayerState ent_state[MAX_ENTITIES];
	int pos_x[MAX_ENTITIES];
	int pos_y[MAX_ENTITIES];
	int speed[MAX_ENTITIES];
	
	Animation anim[MAX_ENTITIES];

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
		speed[id] = 0;

		if (type == ENTITY_EXAMPLE)
		{
			ent_state[id] = PlayerState::IDLE;
			speed[id] = 5;
		}

		anim[id].ResetAnim();

		return id;
	}

	void UpdateEntityExample(int id, int dt)
	{
	}

	bool Collision(int a, int b)
	{
		int COLLISION_SIZE = 16;
		//rectangle colision
		return (pos_x[a] < pos_x[b] + COLLISION_SIZE && pos_x[a] + COLLISION_SIZE > pos_x[b] &&
			pos_y[a] < pos_y[b] + COLLISION_SIZE && pos_y[a] + COLLISION_SIZE > pos_y[b]);
	}

	void UpdateCollisions(int dt)
	{

		//Collisions
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			if (ent_type[i] == EntityType::NONE) continue;

			for (int j = 0; j < MAX_ENTITIES; j++)
			{
				if (ent_type[j] == EntityType::NONE) continue;
				if (i == j) continue;


				//TRAINER ACTIVATOR
				if (ent_type[i] == EntityType::ENTITY_EXAMPLE && 
					ent_type[j] != EntityType::ENTITY_EXAMPLE &&
					Collision(i,j))
				{
					ent_type[i] = EntityType::NONE;
					ent_type[j] = EntityType::NONE;
				}

			}
		}
	}

	void UpdateEntities(int dt)
	{
		UpdateCollisions(dt);

		for (int id = 0; id < MAX_ENTITIES; ++id)
		{
			switch (ent_type[id])
			{
				case EntityType::ENTITY_EXAMPLE:
				{
					UpdateEntityExample(dt, id);
				} break;
			}

			if (ent_type[id] != EntityType::NONE)
			{
				anim[id].Update(dt);
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
				draw_list.push_back(id);
			}
		}
		
		std::sort(draw_list.begin(), draw_list.end(), [](int i, int j)
		{

			return pos_y[i] < pos_y[j];
		});

		for (size_t i = 0; i < draw_list.size(); ++i)
		{
			int id = draw_list[i];

			spr.setScale(1, 1);
			spr.setOrigin(0, 0);
			
			int x = pos_x[id];
			int y = pos_y[id];

			spr.setTextureRect(anim[id].CurrentFrame());

			spr.setColor(sf::Color::White);

			spr.setPosition(x / 100.0f, y / 100.0f);

			wnd.draw(spr);
		}

	}
}

sf::Texture texture;
sf::Sprite sprite;

void LoadGame(sf::RenderWindow& window)
{
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

		//view.setCenter(cam_x, cam_y);

		window.setView(view);

#if _DEBUG
		//DrawImguiCosas();
#endif

		window.clear();

		EntS::DrawEntities(sprite, window);

		window.setView(window.getDefaultView());

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
