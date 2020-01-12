#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <queue>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <random>
#include <set>
#if _DEBUG
static bool free_cam_view_on = false;
static int free_cam_x = 0;
static int free_cam_y = 0;
#endif

std::default_random_engine rnd_gen;
std::uniform_int_distribution<int> rnd_1d100(1, 100);
std::uniform_int_distribution<int> rnd_coin(1, 3);
int Roll1d100()
{
	return rnd_1d100(rnd_gen);
}
int RollCoinFlip()
{
	return rnd_coin(rnd_gen) - 1;
}

int rnd_point(int max, int min)
{
	return  (rand() % max) + min;
}

int Distance(int x1, int y1, int x2, int y2)
{
	long x = (long)(x2) - (long)(x1);
	long y = (long)(y2) - (long)(y1);

	return static_cast<long>(sqrt(x * x +  y * y));
}

sf::Texture tex_tileset;
sf::Texture tex_mex;

sf::Font font;

enum class GameKeys
{
	UP = 0, DOWN, LEFT, RIGHT,
	ACTION, START,
	CAM_UP, CAM_DOWN, CAM_LEFT, CAM_RIGHT,
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

		input_map[GameKeys::CAM_UP] = sf::Keyboard::Key::Up;
		input_map[GameKeys::CAM_DOWN] = sf::Keyboard::Key::Down;
		input_map[GameKeys::CAM_LEFT] = sf::Keyboard::Key::Left;
		input_map[GameKeys::CAM_RIGHT] = sf::Keyboard::Key::Right;
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

const int TILE_SIZE = 3200; //In world coordenadas, o sea, 200 ints destos is 1 pixel
const int MAP_SIZE_X = 32; //In tiles
const int MAP_SIZE_Y = 18; //In tiles
const int WORLD_MAP_SIZE_X = 4; //In rejillas of maps
const int WORLD_MAP_SIZE_Y = 4; //In rejillas of maps
const int MEMORY_WORLD_MAP_SIZE_X = 4;
const int MEMORY_WORLD_MAP_SIZE_Y = 4;

const int SWORD_TIME = 300;
const int GREEN_BLOB_TIME = 200;
const int PUFF_TIME = 300;

const int HIT_TIME = 250;
const int VANISH_TIME = 600;

const int LINK_MAX_HP = 6;
const int LINK_WALKING_SPEED = 12;

const int GREEN_BLOB_DMG = 1;

const int HEART_HEAL = 2;
const int COLLECTIBLE_DISSAPEAR_TIME = 12000;
const int COLLECTIBLE_BLINKING_TIME = 100;

const int GREEN_RUPEE_VALUE = 1;
const int BLUE_RUPEE_VALUE = 5;

const int INVULNERABLE_TIME_PLAYER = HIT_TIME*3;
const int INVULNERABLE_TIME = HIT_TIME;

const int CUT_GRASS_TIME = 400;

const float MARGIN_TOP_GUI = TILE_SIZE * 4.5f / 100.0f;

const int SMOKE_PARTICLE_TIME = 200;
const int TRAINER_VANISHING_TIME = 300;

//GUI TIMERS
const int GUI_HEART_HEAL_TIME = 200;
const int GUI_HEART_DMG_TIME = 100;

int GUI_hp_draw = 0;
int GUI_hearts_timer = 0;
bool GUI_isPlayerHealing = false;

int GUI_hearts_dmg_timer = 0;

bool GUI_is_dmg = false;

const int GUI_RUPEE_RICHER_TIME = 150;
int GUI_rupees = 0;
int GUI_rupee_richer_timer = 0;

sf::Text GUI_text;


enum AnimationType
{
	NONE,
	LINK_IDLE_RIGHT,
	LINK_IDLE_LEFT,
	LINK_IDLE_UP,
	LINK_IDLE_DOWN,
	LINK_WALK_RIGHT,
	LINK_WALK_LEFT,
	LINK_WALK_UP,
	LINK_WALK_DOWN,
	LINK_ATTACK_RIGHT,
	LINK_ATTACK_LEFT,
	LINK_ATTACK_UP,
	LINK_ATTACK_DOWN,
	LINK_ATTACK_2_RIGHT,
	LINK_ATTACK_2_LEFT,
	LINK_ATTACK_2_UP,
	LINK_ATTACK_2_DOWN,
	SWORD_ATTACK_RIGHT,
	SWORD_ATTACK_LEFT,
	SWORD_ATTACK_UP,
	SWORD_ATTACK_DOWN,
	SWORD_ATTACK_2_RIGHT,
	SWORD_ATTACK_2_LEFT,
	SWORD_ATTACK_2_UP,
	SWORD_ATTACK_2_DOWN,
	GREEN_BLOB,
	BAT_IDLE,
	BAT_WALK,
	FADA,
	PUFF,
	HEART,
	GREEN_RUPEE,
	BLUE_RUPEE,
	CAVE_KEY,
	GRASS,
	GRASS_CUT,
	SPARRING,
	PLAYER_DEAD,
	SMOKE_PARTICLE,
	TRAINER,
	TRAINER_ACTIVATOR_COMBO_SWORD,
	TRAINER_ACTIVATOR_COMBO_ATTACK2
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
	//LINK_IDLE_RIGHT
	{   1, 
		{ 
			{1 * 16, 1 * 16, 16, 16},
		}, 
		{
			100
		},
	},
	//LINK_IDLE_LEFT
	{   1,
		{
			{4 * 16, 0 * 16, 16, 16},
		},
		{
			100
		},
	},
	//LINK_IDLE_UP
	{   1,
		{
			{4 * 16, 1 * 16, 16, 16},
		},
		{
			100
		},
	},
	//LINK_IDLE_DOWN
	{   1,
		{
			{8 * 16, 1 * 16, 16, 16},
		},
		{
			1000
		},
	},
	//LINK_WALK_RIGHT
	{	2,
		{
			{ 0 * 16, 1 * 16, 16, 16 },
			{ 1 * 16, 1 * 16, 16, 16 }
		},
		{
			250, 250
		},
	},
	//LINK_WALK_LEFT
	{	2,
		{
			{ 8 * 16, 0 * 16, 16, 16 },
			{ 4 * 16, 0 * 16, 16, 16 }
		},
		{
			250, 250
		},
	},
	//LINK_WALK_UP
	{ 2,
		{
			{ 10 * 16, 1 * 16, 16, 16 },
			{ 4 * 16, 1 * 16, 16, 16 }
		},
		{
			250, 250
		},
	},
	//LINK_WALK_DOWN
	{	2,
		{
			{ 11 * 16, 1 * 16, 16, 16 },
			{ 8 * 16, 1 * 16, 16, 16 }
		},
		{
			250, 250
		},
	},
	//LINK_ATTACK_RIGHT
	{	3,
		{
			{ 11 * 16, 2 * 16, 16, 16 },
			{ 11 * 16, 2 * 16, 16, 16 },
			{ 5 * 16, 1 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},
	//LINK_ATTACK_LEFT
	{	3,
		{
			{ 10 * 16, 2 * 16, 16, 16 },
			{ 10 * 16, 2 * 16, 16, 16 },
			{ 9 * 16, 0 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},	
	//LINK_ATTACK_UP
	{ 3,
		{
			{ 8 * 16, 2 * 16, 16, 16 },
			{ 8 * 16, 2 * 16, 16, 16 },
			{ 7 * 16, 1 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},
	//LINK_ATTACK_DOWN
	{	3,
		{
			{ 9 * 16, 2 * 16, 16, 16 },
			{ 9 * 16, 2 * 16, 16, 16 },
			{ 6 * 16, 1 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},
	//LINK_ATTACK_2_RIGHT
	{ 3,
		{
			{ 6 * 16, 1 * 16, 16, 16 },
			{ 14 * 16, 0 * 16, 16, 16 },
			{ 5 * 16, 1 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},
	//LINK_ATTACK_2_LEFT
	{	3,
		{
			{ 6 * 16, 1 * 16, 16, 16 },
			{ 9 * 16, 2 * 16, 16, 16 },
			{ 9 * 16, 0 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},
	//LINK_ATTACK_2_UP
	{	3,
		{
			{ 9 * 16, 0 * 16, 16, 16 },
			{ 8 * 16, 2 * 16, 16, 16 },
			{ 7 * 16, 1 * 16, 16, 16 },
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},
	//LINK_ATTACK_2_DOWN
	{	3,
		{
			{ 5 * 16, 1 * 16, 16, 16 },
			{ 14 * 16, 0 * 16, 16, 16 },
			{ 8 * 16, 1 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3
		},
	},
	//SWORD_ATTACK_RIGHT
	{	3,
		{
			{ 1 * 16, 6 * 16, 16, 16 },
			{ 3 * 16, 6 * 16, 16, 16 },
			{ 2 * 16, 6 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//SWORD_ATTACK_LEFT
	{	3,
		{
			{ 1 * 16, 6 * 16, 16, 16 },
			{ 5 * 16, 6 * 16, 16, 16 },
			{ 6 * 16, 5 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//SWORD_ATTACK_UP
	{	3,
		{
			{ 2 * 16, 6 * 16, 16, 16 },
			{ 3 * 16, 6 * 16, 16, 16 },
			{ 1 * 16, 6 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//SWORD_ATTACK_DOWN
	{	3,
		{
			{ 6 * 16, 5 * 16, 16, 16 },
			{ 4 * 16, 6 * 16, 16, 16 },
			{ 5 * 16, 5 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//SWORD_ATTACK_2_RIGHT
	{	3,
		{
			{ 5 * 16, 5 * 16, 16, 16 },
			{ 6 * 16, 6 * 16, 16, 16 },
			{ 2 * 16, 6 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//SWORD_ATTACK_2_LEFT
	{	3,
		{
			{ 5 * 16, 5 * 16, 16, 16 },
			{ 4 * 16, 6 * 16, 16, 16 },
			{ 6 * 16, 5 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//SWORD_ATTACK_2_UP
	{	3,
		{
			{ 6 * 16, 5 * 16, 16, 16 },
			{ 5 * 16, 6 * 16, 16, 16 },
			{ 1 * 16, 6 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//SWORD_ATTACK_2_DOWN
	{	3,
		{
			{ 2 * 16, 6 * 16, 16, 16 },
			{ 6 * 16, 6 * 16, 16, 16 },
			{ 5 * 16, 5 * 16, 16, 16 }
		},
		{
			SWORD_TIME / 3, SWORD_TIME / 3, SWORD_TIME / 3,
		},
	},
	//GREEN BLOB
	{	2,
		{
			{ 8 * 16, 5 * 16, 16, 16 },
			{ 7 * 16, 5 * 16, 16, 16 },
		},
		{
			GREEN_BLOB_TIME/2, GREEN_BLOB_TIME / 2
		},
	},
	//BAT_IDLE
	{ 1,
		{
			{ 4 * 16, 10 * 16, 16, 16 }
		},
		{
			1
		},
	},
	//BAT_WALKING
	{	2,
		{
			{ 4 * 16, 10 * 16, 16, 16 },
			{ 5 * 16, 10 * 16, 16, 16 },
		},
		{
			GREEN_BLOB_TIME / 2, GREEN_BLOB_TIME / 2
		},
	},
	//FADA
	{   1,
		{
			{2 * 16, 3 * 16, 16, 16},
		},
		{
			1000
		},
	},
	//PUFF
	{ 3,
		{
			{ 4 * 16, 8 * 16, 16, 16 },
			{ 5 * 16, 8 * 16, 16, 16 },
			{ 0 * 16, 9 * 16, 16, 16 }
		},
		{
			PUFF_TIME / 3, PUFF_TIME / 3, PUFF_TIME / 3,
		},
	},
	//HEART
	{
		1,
		{
			{ 0, 3 * 16, 16, 16}
		},
		{
			0
		}
	},
	//GREEN RUPEE
	{
		1,
		{
			{ 10 * 16, 5 * 16, 16, 16}
		},
		{
			0
		}
	},
	//BLUE RUPEE
	{
		1,
		{
			{ 11 * 16, 5 * 16, 16, 16}
		},
		{
			0	
		}
	},
	//CAVE KEY
	{
		1,
		{
			{ 9 * 16, 4 * 16, 16, 16}
		},
		{
			0
		}
	},
	//GRASS
	{
		1,
		{
			{ 0 * 16, 11 * 16, 16, 16}
		},
		{
			0
		}
	},
	//GRASS CUT
	{
		1,
		{
			{ 4 * 8, 16 * 8, 8, 8}
		},
		CUT_GRASS_TIME / 2
	},
	//GRASS CUT
	{
		1,
		{
			{ 9 * 16, 5 * 16, 16, 16}
		},
		{
			1
		}
	},
	//PLAYER_DEAD
	{
		1,
		{
			{ 12 * 16, 2 * 16, 16, 16}
		},
		{
			1
		}
	},
	//SMOKE_PARTICLE
	{
		1,
		{
			{ 4 * 16, 8 * 16, 16, 16}
		},
		1
	},
	//TRAINER
	{
		2,
		{
			{ 0 * 16, 4 * 16, 16, 16},
			{ 1 * 16, 4 * 16, 16, 16},
		},
		{500, 500}
	},
	//TRAINER_ACTIVATOR_COMBO_SWORD
	{
		3,
		{
			{ 3 * 16, 11 * 16, 16, 16},
			{ 2 * 16, 11 * 16, 16, 16},
			{ 2 * 16, 11 * 16, 16, 16},
		},
		{150, 150, 500}
	},
	//TRAINER_ACTIVATOR_COMBO_ATTACK2
	{
		5,
		{
			{ 2 * 16, 11 * 16, 16, 16},
			{ 3 * 16, 11 * 16, 16, 16},
			{ 2 * 16, 11 * 16, 16, 16},
			{ 3 * 16, 11 * 16, 16, 16},
			{ 2 * 16, 11 * 16, 16, 16},
		},
		{150, 150, 150, 150, 500}
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
				//TODO: Remove this legendary hack
				if (anim_type != AnimationType::SWORD_ATTACK_DOWN &&
					anim_type != AnimationType::SWORD_ATTACK_UP &&
					anim_type != AnimationType::SWORD_ATTACK_LEFT &&
					anim_type != AnimationType::SWORD_ATTACK_RIGHT &&
					anim_type != AnimationType::SWORD_ATTACK_2_DOWN &&
					anim_type != AnimationType::SWORD_ATTACK_2_UP &&
					anim_type != AnimationType::SWORD_ATTACK_2_LEFT &&
					anim_type != AnimationType::SWORD_ATTACK_2_RIGHT
					)
				{
					current_frame = 0;
				}

				
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

	FLOWER,
	GRASS,
	SUPER_GRASS,
	CUT_GRASS,

	ROCK,

	FIELD,
	FIELD_TL,
	FIELD_T,
	FIELD_TR,
	FIELD_L,
	FIELD_R,
	FIELD_BL,
	FIELD_B,
	FIELD_BR,

	WATER,

	TREE_TL,
	TREE_TR,
	TREE_BL,
	TREE_BR,

	ROOF_TL,
	ROOF_T,
	ROOF_TR,
	ROOF_BR,
	ROOF_BL,
	ROOF_B,

	HOUSE_WINDOW_STONE,
	HOUSE_DOOR_STONE,

	HOUSE_WINDOW_WOOD,
	HOUSE_DOOR_WOOD,

	HOUSE_INSIDE_FLOOR,

	HOUSE_INSIDE_DOOR_LEFT,
	HOUSE_INSIDE_DOOR_HOLE,
	HOUSE_INSIDE_DOOR_RIGHT,

	CAVE_TL,
	CAVE_T,
	CAVE_TR,
	CAVE_BL,
	CAVE_BR,

	CAVE_WALL_TL,
	CAVE_WALL_T,
	CAVE_WALL_TR,
	CAVE_WALL_L,
	CAVE_WALL_R,
	CAVE_WALL_BL,
	CAVE_WALL_B,
	CAVE_WALL_BR,
	CAVE_WALL_TL_BR,
	CAVE_WALL_TR_BL,


	CAVE_DOOR,

	CAVE_FLOOR,
	CAVE_STAIRS,

	CAVE_DOOR_LOCKED,

	PUZZLE_BUTTON,
	PUZZLE_BUTTON_PRESSED,

	TILE_SPECIAL
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

Tile world_map[MAP_SIZE_Y * WORLD_MAP_SIZE_Y * MEMORY_WORLD_MAP_SIZE_Y][MAP_SIZE_X * WORLD_MAP_SIZE_X * MEMORY_WORLD_MAP_SIZE_X];


namespace WorldMap
{
	int wx_sword_start;
	int wy_sword_start;

	int wx_cave_room_entrance;
	int wy_cave_room_entrance;

	int sword_tx;
	int sword_ty;
};

void SetTeleportLink(int a_x, int a_y, int b_x, int b_y)
{
	world_map[a_y][a_x].tp_x = b_x;
	world_map[a_y][a_x].tp_y = b_y;
}

bool IsTeleportLink(int tx, int ty)
{
	return
		world_map[ty][tx].tp_x != -1 &&
		world_map[ty][tx].tp_y != -1;
}

bool IsTileInBounds(int x, int y)
{
	if (x < 0 || x >= MEMORY_WORLD_MAP_SIZE_X* WORLD_MAP_SIZE_X * MAP_SIZE_X || y < 0 || y >= MEMORY_WORLD_MAP_SIZE_Y * WORLD_MAP_SIZE_Y * MAP_SIZE_Y)
	{
		return false;
	}
	return true;
}

inline TileType Tile_GetOnWorldMap(int tile_x, int tile_y)
{
	if (!IsTileInBounds(tile_x, tile_y)) return TileType::NONE;

	return (world_map[tile_y][tile_x]).type;
}


inline TileType Tile_GetOnScreenMap(int world_x, int world_y, int tile_x, int tile_y)
{
	int tx = world_x * MAP_SIZE_X + tile_x;
	int ty = world_y * MAP_SIZE_Y + tile_y;

	if (!IsTileInBounds(tx, ty)) return TileType::NONE;

	return (world_map[ty][tx]).type;
}

bool IsTilePassable(TileType type)
{
	return type == TileType::GRASS ||
		type == TileType::CUT_GRASS ||
		type == TileType::FIELD ||
		type == TileType::FLOWER ||
		type == TileType::GRASS ||
		type == TileType::HOUSE_DOOR_STONE ||
		type == TileType::HOUSE_DOOR_WOOD ||
		type == TileType::HOUSE_INSIDE_FLOOR ||
		type == TileType::HOUSE_INSIDE_DOOR_HOLE ||
		type == TileType::TILE_SPECIAL ||
		type == TileType::CAVE_DOOR ||
		type == TileType::CAVE_FLOOR ||
		type == TileType::CAVE_STAIRS ||
		type == TileType::PUZZLE_BUTTON ||
		type == TileType::PUZZLE_BUTTON_PRESSED;
}

bool IsTileWorldPassable(int x, int y)
{
	if (!IsTileInBounds(x, y)) return false;

	TileType type = Tile_GetOnWorldMap(x, y);
	return IsTilePassable(type);
}

bool IsTileWorldPassable(int w_x, int w_y, int x, int y)
{
	int tx = w_x * MAP_SIZE_X + x;
	int ty = w_y * MAP_SIZE_Y + y;

	if (!IsTileInBounds(tx, ty)) return false;

	TileType type = Tile_GetOnWorldMap(tx, ty);
	return IsTilePassable(type);
}

bool IsTileMoreOrLessPassable(int new_x, int new_y)
{
	int center_x = new_x + TILE_SIZE / 2;
	int center_y = new_y + TILE_SIZE / 2;

	int tile_x[4] = { (center_x + TILE_SIZE / 4), (center_x + TILE_SIZE / 4), (center_x - TILE_SIZE / 4), (center_x - TILE_SIZE / 4) };
	int tile_y[4] = { (center_y + TILE_SIZE / 4), (center_y - TILE_SIZE / 4), (center_y + TILE_SIZE / 4), (center_y - TILE_SIZE / 4) };

	for (int i = 0; i < 4; ++i)
	{
		if (!IsTileWorldPassable(tile_x[i] / TILE_SIZE, tile_y[i] / TILE_SIZE))
		{
			return false;
		}
	}
	return true;
}

bool IsInCurrentMap(int wx, int wy, int x, int y)
{
	return
		x > wx*MAP_SIZE_X*TILE_SIZE &&
		x < (wx + 1)*MAP_SIZE_X*TILE_SIZE &&
		y > wy*MAP_SIZE_Y*TILE_SIZE  &&
		y < (wy + 1)*MAP_SIZE_Y*TILE_SIZE;

}


inline void Tile_SetOnScreenMap(int wx, int wy, int x, int y, TileType t)
{
	int tx = wx * MAP_SIZE_X + x;
	int ty = wy * MAP_SIZE_Y + y;

	world_map[ty][tx].type = t;
}


inline void Tile_SetOnWorldMap(int tile_x, int tile_y, TileType t)
{
	world_map[tile_y][tile_x].type = t;
}

#include <stack>
bool CheckIsArrivableInMap(int w_x, int w_y, int start_x, int start_y, int end_x, int end_y)
{
	bool visited[MAP_SIZE_X][MAP_SIZE_Y];
	for (int i = 0; i < MAP_SIZE_X; ++i)
	{
		for (int j = 0; j < MAP_SIZE_Y; ++j)
		{
			visited[i][j] = false;
		}
	}

	std::queue<int> queue_x;
	std::queue<int> queue_y;
	queue_x.push(start_x);
	queue_y.push(start_y);
	visited[start_x][start_y] = true;

	while (!queue_x.empty())
	{

		int x = queue_x.front();
		queue_x.pop();
		int y = queue_y.front();
		queue_y.pop();

		if (x == end_x && y == end_y)
		{
			return true;
		}

		int dx[] = { -1, 1, 0, 0 };
		int dy[] = { 0, 0, -1, 1};

		for (int d = 0; d < 4; d++)
		{
			int next_x = x + dx[d];
			int next_y = y + dy[d];

			if ((next_x >= 1 && next_x <= MAP_SIZE_X - 2 && next_y >= 1 && next_y <= MAP_SIZE_Y - 2) &&
				IsTileWorldPassable(w_x, w_y, next_x, next_y) && !visited[next_x][next_y])
			{
				queue_x.push(next_x);
				queue_y.push(next_y);
				visited[next_x][next_y] = true;
			}
		}

	}

	return false;
}



namespace PlayerInfo
{
	int rupees = 0;
	bool sword_unlocked = false;
	bool attack2_unlocked = false;
	bool has_key = false;

	void Reset()
	{
		rupees = 0;
		sword_unlocked = false;
		attack2_unlocked = false;
		has_key = false;
	}
};

enum Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};
Direction ReverseDir(Direction dir)
{
	if (dir == UP) return DOWN;
	if (dir == DOWN) return UP;
	if (dir == LEFT) return RIGHT;
	if (dir == RIGHT) return LEFT;
}

enum PlayerState
{
	IDLE,
	WALKING,
	ATTACK,
	ATTACK2,
	DEAD,
	SPAWNING,
	VANISHING,
	DISSAPEAR,
	LEARNING_SKILL_SWORD,
	LEARNING_SKILL_ATTACK2
};

namespace EntS
{
	const int MAX_ENTITIES = 2048;
	enum EntityType
	{
		NONE = 0,

		LINK,
		FADA,
		SWORD, SWORD2,
		BLOB,
		BLOB_SPAWNER,
		BAT,
		PUFF,
		HEART,
		GREEN_RUPEE,
		BLUE_RUPEE,
		CAVE_KEY,
		GRASS_CUT_PARTICLE,
		SPARRING,
		SMOKE_PARTICLE,

		TRAINER_ACTIVATOR_SWORD,
		TRAINER_NPC_ATTACK2,
		TRAINER_ACTIVATOR_ATTACK2,

		PUZZLE_CAVEKEY,
		PUZZLE_CAVEKEY_BUTTON,

		COUNT
	};
	

	inline bool IsAliveEntity(EntityType ent)
	{
		return 
			(ent == EntityType::LINK) ||
			(ent == EntityType::BLOB) ||
			(ent == EntityType::BAT) ||
			(ent == EntityType::SPARRING);
	}
	inline bool IsDamager(EntityType ent)
	{
		return
			ent == EntityType::BLOB ||
			(ent == EntityType::BAT);
	}
	inline bool IsCollectible(EntityType ent)
	{
		return
			ent == EntityType::HEART ||
			ent == EntityType::GREEN_RUPEE ||
			ent == EntityType::BLUE_RUPEE ||
			ent == EntityType::CAVE_KEY;

	}
	inline bool IsCollectibleForever(EntityType ent)
	{
		return
			ent == EntityType::CAVE_KEY;
	}
	inline bool IsHittableBySword(EntityType ent)
	{
		return
			ent == EntityType::BLOB ||
			ent == EntityType::BAT	||
			ent == EntityType::SPARRING;
	}
	inline bool IsWeapon(EntityType ent)
	{
		return
			ent == EntityType::SWORD ||
			ent == EntityType::SWORD2;
	}
	inline bool IsTrainerActivator(EntityType ent)
	{
		return
			ent == EntityType::TRAINER_ACTIVATOR_SWORD ||
			ent == EntityType::TRAINER_ACTIVATOR_ATTACK2;
	}
	

	EntityType ent_type[MAX_ENTITIES];
	PlayerState ent_state[MAX_ENTITIES];
	int pos_x[MAX_ENTITIES];
	int pos_y[MAX_ENTITIES];
	int speed[MAX_ENTITIES];
	int angle[MAX_ENTITIES];
	Direction ent_dir[MAX_ENTITIES];
	Animation anim[MAX_ENTITIES];
	int ent_timer[MAX_ENTITIES];
	int target[MAX_ENTITIES];
	int ent_hp[MAX_ENTITIES];
	int ent_status[MAX_ENTITIES];
	int ent_idparent[MAX_ENTITIES];
	int id_weapon[MAX_ENTITIES];

	bool is_hitted[MAX_ENTITIES];
	int timer_hit[MAX_ENTITIES];
	int timer_invulnerable[MAX_ENTITIES];
	inline bool IsInvulnerable(int id)
	{
		return timer_invulnerable[id] > 0;
	}

	int id_player;

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
		ent_timer[id] = 0;
		ent_state[id] = IDLE;
		ent_status[id] = 0;
		angle[id] = 0;
		is_hitted[id] = false;
		ent_hp[id] = 0;
		timer_invulnerable[id] = 0;
		ent_idparent[id] = id_parent;

		if (type == LINK)
		{
			ent_state[id] = PlayerState::IDLE;
			speed[id] = LINK_WALKING_SPEED;
			ent_dir[id] = Direction::DOWN;
			anim[id].Ensure(AnimationType::LINK_IDLE_DOWN);
			ent_hp[id] = 5;
		}

		if (type == BLOB)
		{
			ent_hp[id] = 2;
			speed[id] = 10;
		}

		if (type == BAT)
		{
			ent_hp[id] = 3;
			speed[id] = 9;
			anim[id].Ensure(AnimationType::BAT_IDLE);
		}

		if (type == FADA)
		{
			anim[id].Ensure(AnimationType::FADA);
			speed[id] = 10;
		}

		if (type == HEART)
		{
			anim[id].Ensure(AnimationType::HEART);
			ent_state[id] = PlayerState::SPAWNING;
			ent_timer[id] = 0;
		}

		if (type == GREEN_RUPEE)
		{
			anim[id].Ensure(AnimationType::GREEN_RUPEE);
			ent_state[id] = PlayerState::SPAWNING;
			ent_timer[id] = 0;
		}
		if (type == BLUE_RUPEE)
		{
			anim[id].Ensure(AnimationType::BLUE_RUPEE);
			ent_state[id] = PlayerState::SPAWNING;
			ent_timer[id] = 0;
		}
		if (type == CAVE_KEY)
		{
			anim[id].Ensure(AnimationType::CAVE_KEY);
			ent_state[id] = PlayerState::SPAWNING;
			ent_timer[id] = 0;
		}

		if (type == GRASS)
		{
			anim[id].Ensure(AnimationType::GRASS);
		}

		if (type == GRASS_CUT_PARTICLE)
		{
			anim[id].Ensure(AnimationType::GRASS_CUT);
		}

		if (type == SWORD || type == SWORD2)
		{
			ent_dir[id] = ent_dir[id_parent];

		}

		if (type == SPARRING)
		{
			anim[id].Ensure(AnimationType::SPARRING);
		}

		if (type == SMOKE_PARTICLE)
		{
			anim[id].Ensure(AnimationType::SMOKE_PARTICLE);
			ent_state[id] = PlayerState::VANISHING;
		}

		if (type == TRAINER_NPC_ATTACK2)
		{
			anim[id].Ensure(AnimationType::TRAINER);
			ent_state[id] = PlayerState::IDLE;
		}

		if (type == TRAINER_ACTIVATOR_SWORD)
		{
			anim[id].Ensure(AnimationType::NONE);
			ent_state[id] = PlayerState::IDLE;
		}
		if (type == TRAINER_ACTIVATOR_ATTACK2)
		{
			anim[id].Ensure(AnimationType::NONE);
			ent_state[id] = PlayerState::IDLE;
		}
		if (type == TRAINER_ACTIVATOR_SWORD)
		{
			//todo: poner imagen espada
		}

		if (type == PUZZLE_CAVEKEY)
		{
			anim[id].Ensure(AnimationType::NONE);
			ent_state[id] = PlayerState::IDLE;
		}
		if (type == PUZZLE_CAVEKEY_BUTTON)
		{
			anim[id].Ensure(AnimationType::NONE);
			ent_state[id] = PlayerState::IDLE;
		}
		
		anim[id].ResetAnim();

		return id;
	}

	void MoveToEntityDirection(int id, int dt)
	{
		if (ent_dir[id] == Direction::UP)
		{
			pos_x[id] -= speed[id] * dt;
			pos_y[id] -= speed[id] * dt;
		}
		else if (ent_dir[id] == Direction::DOWN)
		{
			pos_x[id] += speed[id] * dt;
			pos_y[id] += speed[id] * dt;
		}
		else if (ent_dir[id] == Direction::RIGHT)
		{
			pos_x[id] += speed[id] * dt;
			pos_y[id] -= speed[id] * dt;
		}
		else
		{
			pos_x[id] -= speed[id] * dt;
			pos_y[id] += speed[id] * dt;
		}
	}

	void SpawnLeaf(int x, int y)
	{
		int max_rnd = TILE_SIZE / 2;
		int min_rnd = 300;

		int id_leaf_0 = EntS::SpawnEntity(EntityType::GRASS_CUT_PARTICLE, x + rnd_point(max_rnd, min_rnd), y + rnd_point(max_rnd, min_rnd));
		int id_leaf_1 = EntS::SpawnEntity(EntityType::GRASS_CUT_PARTICLE, x - rnd_point(max_rnd, min_rnd), y - rnd_point(max_rnd, min_rnd));
		int id_leaf_2 = EntS::SpawnEntity(EntityType::GRASS_CUT_PARTICLE, x + rnd_point(max_rnd, min_rnd), y - rnd_point(max_rnd, min_rnd));
		int id_leaf_3 = EntS::SpawnEntity(EntityType::GRASS_CUT_PARTICLE, x - rnd_point(max_rnd, min_rnd), y + rnd_point(max_rnd, min_rnd));

		angle[id_leaf_0] = rand() % 359;
		angle[id_leaf_1] = rand() % 359;
		angle[id_leaf_2] = rand() % 359;
		angle[id_leaf_3] = rand() % 359;

		ent_dir[id_leaf_0] = Direction::DOWN;
		ent_dir[id_leaf_1] = Direction::UP;
		ent_dir[id_leaf_2] = Direction::RIGHT;
		ent_dir[id_leaf_3] = Direction::LEFT;

		speed[id_leaf_0] = rand() % 5;
		speed[id_leaf_1] = rand() % 5;
		speed[id_leaf_2] = rand() % 5;
		speed[id_leaf_3] = rand() % 5;
	}

	void SpawnSmoke(int parent_id, int qty)
	{
		int max_rnd = TILE_SIZE / 2;
		int min_rnd = 300;

		Direction direction = ent_dir[parent_id];
		Direction smoke_dir;

		int id_smoke;

		for (int i = 0; i < qty; ++i)
		{
			int x = pos_x[parent_id];
			int y = pos_y[parent_id];

			switch (direction)
			{
			case Direction::RIGHT:
				{
					x -= 4*TILE_SIZE/10;
					y += rnd_point(max_rnd, min_rnd);
					smoke_dir = Direction::LEFT;

				}break;
				case Direction::LEFT:
				{

					x += TILE_SIZE;
					y += rnd_point(max_rnd, min_rnd); 
					smoke_dir = Direction::RIGHT;

				} break;
				case Direction::UP:
				{
					x += rnd_point(max_rnd, min_rnd);
					y += 120*TILE_SIZE/100;
					smoke_dir = Direction::DOWN;

				} break;
				case Direction::DOWN:
				{
					x += rnd_point(max_rnd, min_rnd);
					y -= TILE_SIZE/2;
					smoke_dir = Direction::UP;
				} break;
			}

			id_smoke = EntS::SpawnEntity(EntityType::SMOKE_PARTICLE, x, y);

			ent_dir[id_smoke] = smoke_dir;

			angle[id_smoke] = rand() % 359;
			speed[id_smoke] = rnd_point(10, 5);

		}
	}

	void ApplyMovement(int id, int dt)
	{
		int new_x = pos_x[id];
		int new_y = pos_y[id];

		if (ent_dir[id] == Direction::UP) new_y -= speed[id] * dt;
		if (ent_dir[id] == Direction::DOWN) new_y += speed[id] * dt;
		if (ent_dir[id] == Direction::LEFT) new_x -= speed[id] * dt;
		if (ent_dir[id] == Direction::RIGHT) new_x += speed[id] * dt;

		int center_x = new_x + TILE_SIZE / 2;
		int center_y = new_y + TILE_SIZE / 2;

		int tile_x[4] = { (center_x + TILE_SIZE / 4), (center_x + TILE_SIZE / 4), (center_x - TILE_SIZE / 4), (center_x - TILE_SIZE / 4) };
		int tile_y[4] = { (center_y + TILE_SIZE / 4), (center_y - TILE_SIZE / 4), (center_y + TILE_SIZE / 4), (center_y - TILE_SIZE / 4) };

		bool can_pass = true;
		for (int i = 0; i < 4; ++i)
		{
			if (!IsTileWorldPassable(tile_x[i]/ TILE_SIZE, tile_y[i]/ TILE_SIZE))
			{
				can_pass = false;
			}
		}
		if (can_pass)
		{
			pos_x[id] = new_x;
			pos_y[id] = new_y;
		}


		//if (pos_x[id] < TILE_SIZE) pos_x[id] = TILE_SIZE;
		//if (pos_x[id] > TILE_SIZE*MAP_SIZE_X - TILE_SIZE * 2) pos_x[id] = TILE_SIZE * MAP_SIZE_X - TILE_SIZE * 2 - 2;
		//if (pos_y[id] < TILE_SIZE) pos_y[id] = TILE_SIZE;
		//if (pos_y[id] > TILE_SIZE*MAP_SIZE_Y - TILE_SIZE * 2) pos_y[id] = TILE_SIZE * MAP_SIZE_Y - TILE_SIZE * 2 - 2;
	}
	

	void UpdateBlob(int dt, int id)
	{
		if (is_hitted[id]) return;

		anim[id].Ensure(AnimationType::GREEN_BLOB);
		
		if (ent_state[id] == PlayerState::IDLE)
		{
			ent_timer[id] -= dt;
			if (ent_timer[id] < 0)
			{
				ent_state[id] = PlayerState::WALKING;

				ent_timer[id] = GREEN_BLOB_TIME + 3*Roll1d100();

				int x = pos_x[id];
				int y = pos_y[id];

				int chance_up = 15;
				int chance_down = 15;
				int chance_left = 15;
				int chance_right = 15;


				int roll = rnd_1d100(rnd_gen);

				if (roll < chance_up)
				{
					ent_dir[id] = Direction::UP;
				}
				else if (roll - chance_up < chance_down)
				{
					ent_dir[id] = Direction::DOWN;
				}
				else if (roll - chance_up - chance_down < chance_left)
				{
					ent_dir[id] = Direction::LEFT;
				}
				else if (roll - chance_up - chance_left - chance_down < chance_right)
				{
					ent_dir[id] = Direction::RIGHT;
				}
			}
		}
		else if(ent_state[id] == PlayerState::WALKING)
		{
			ent_timer[id] -= dt;

			ApplyMovement(id, dt);

			if (ent_timer[id] < 0)
			{
				ent_timer[id] = GREEN_BLOB_TIME + 5 * Roll1d100();
				ent_state[id] = PlayerState::IDLE;
				/*
				{
					timer[id] = 2 * timer[id];
					ent_state[id] = PlayerState::IDLE;
				}
				*/
			}
		}
	}

	void UpdateBat(int dt, int id)
	{
		if (is_hitted[id]) return;

		int x = (pos_x[id] + TILE_SIZE / 2) / TILE_SIZE;
		int y = (pos_y[id] + TILE_SIZE / 2) / TILE_SIZE;
		int xp = (pos_x[id_player] + TILE_SIZE / 2) / TILE_SIZE;
		int yp = (pos_y[id_player] + TILE_SIZE / 2) / TILE_SIZE;

		int distance = Distance(x, y, xp, yp);

		if (ent_state[id] == PlayerState::IDLE)
		{

			if (distance <= 3)
			{
				ent_state[id] = PlayerState::WALKING;
				anim[id].Ensure(AnimationType::BAT_WALK);
			}
		}
		else if (ent_state[id] == PlayerState::WALKING)
		{	
			if (distance > 0 && distance < 10)
			{
				pos_x[id] += (pos_x[id_player] - pos_x[id]) * dt / distance * speed[id] / TILE_SIZE;
				pos_y[id] += (pos_y[id_player] - pos_y[id]) * dt / distance * speed[id] / TILE_SIZE;
			} 
			else
			{
				ent_state[id] = PlayerState::IDLE;
				anim[id].Ensure(AnimationType::BAT_IDLE);
			}
		}
	}

	void UpdateLink(int id, int dt)
	{
		if (is_hitted[id]) return;

		int tx = pos_x[id] / TILE_SIZE;
		int ty = pos_y[id] / TILE_SIZE;

		int ctx = (pos_x[id] + TILE_SIZE / 2) / TILE_SIZE;
		int cty = (pos_y[id] + TILE_SIZE / 2) / TILE_SIZE;

		if (PlayerInfo::has_key && Tile_GetOnWorldMap(ctx, ty) == TileType::CAVE_DOOR_LOCKED)
		{
			PlayerInfo::has_key = false;
			Tile_SetOnWorldMap(ctx, ty, TileType::CAVE_DOOR);
		}


		switch (ent_state[id])
		{
			case IDLE:
			{
				if (input_state.IsPressed(GameKeys::LEFT))
				{
					ent_dir[id] = Direction::LEFT;
					ent_state[id] = PlayerState::WALKING;
				}
				else if (input_state.IsPressed(GameKeys::RIGHT))
				{
					ent_dir[id] = Direction::RIGHT;
					ent_state[id] = PlayerState::WALKING;
				}
				if (input_state.IsPressed(GameKeys::UP))
				{
					ent_dir[id] = Direction::UP;
					ent_state[id] = PlayerState::WALKING;
				}
				else if (input_state.IsPressed(GameKeys::DOWN))
				{
					ent_dir[id] = Direction::DOWN;
					ent_state[id] = PlayerState::WALKING;
				}
				else if (input_state.IsJustPressed(GameKeys::ACTION) && PlayerInfo::sword_unlocked)
				{
					ent_state[id] = PlayerState::ATTACK;

					int x = pos_x[id];
					int y = pos_y[id];

					id_weapon[id] = EntS::SpawnEntity(EntityType::SWORD, x, y, id);
					
					ent_timer[id] = 0;
				}

				if (ent_dir[id] == Direction::RIGHT) anim[id].Ensure(AnimationType::LINK_IDLE_RIGHT);
				if (ent_dir[id] == Direction::UP) anim[id].Ensure(AnimationType::LINK_IDLE_UP);
				if (ent_dir[id] == Direction::LEFT) anim[id].Ensure(AnimationType::LINK_IDLE_LEFT);
				if (ent_dir[id] == Direction::DOWN) anim[id].Ensure(AnimationType::LINK_IDLE_DOWN);
			} break;

			case WALKING:
			{
				int new_x = pos_x[id];
				int new_y = pos_y[id];

				if (input_state.IsPressed(GameKeys::LEFT))
				{
					new_x -= speed[id] * dt;
					ent_dir[id] = Direction::LEFT;
					ent_state[id] = PlayerState::WALKING;
				}
				else if (input_state.IsPressed(GameKeys::RIGHT))
				{
					new_x += speed[id] * dt;
					ent_dir[id] = Direction::RIGHT;
					ent_state[id] = PlayerState::WALKING;
				}
				if (input_state.IsPressed(GameKeys::UP))
				{
					new_y -= speed[id] * dt;
					ent_dir[id] = Direction::UP;
					ent_state[id] = PlayerState::WALKING;
				}
				else if (input_state.IsPressed(GameKeys::DOWN))
				{
					new_y += speed[id] * dt;
					ent_dir[id] = Direction::DOWN;
					ent_state[id] = PlayerState::WALKING;
				}

				if (IsTileMoreOrLessPassable(new_x, pos_y[id]))
				{
					pos_x[id] = new_x;
				}
				if (IsTileMoreOrLessPassable(pos_x[id], new_y))
				{
					pos_y[id] = new_y;
				}

				if (!input_state.IsPressed(GameKeys::UP) && 
					!input_state.IsPressed(GameKeys::DOWN) &&
					!input_state.IsPressed(GameKeys::LEFT) &&
					!input_state.IsPressed(GameKeys::RIGHT))
				{
					ent_state[id] = PlayerState::IDLE;
				}

				if (PlayerInfo::sword_unlocked && input_state.IsJustPressed(GameKeys::ACTION))
				{
					ent_state[id] = PlayerState::ATTACK;

					int x = pos_x[id];
					int y = pos_y[id];

					EntS::SpawnEntity(EntityType::SWORD, x, y, id);

					ent_timer[id] = 0;
				}

				if (ent_dir[id] == Direction::RIGHT) anim[id].Ensure(AnimationType::LINK_WALK_RIGHT);
				if (ent_dir[id] == Direction::UP) anim[id].Ensure(AnimationType::LINK_WALK_UP);
				if (ent_dir[id] == Direction::LEFT) anim[id].Ensure(AnimationType::LINK_WALK_LEFT);
				if (ent_dir[id] == Direction::DOWN) anim[id].Ensure(AnimationType::LINK_WALK_DOWN);
			} break;

			case ATTACK:
			{
				if (PlayerInfo::attack2_unlocked && input_state.IsJustPressed(GameKeys::ACTION))
				{
					int x = pos_x[id];
					int y = pos_y[id];

					if (ent_type[id_weapon[id]] == EntityType::SWORD)
					{
						ent_type[id_weapon[id]] = EntityType::NONE;
					}
					
					id_weapon[id] = EntS::SpawnEntity(EntityType::SWORD2, x, y, id);
					
					ent_state[id] = PlayerState::ATTACK2;
					ent_timer[id] = 0;
					break;

				}

				if (ent_dir[id] == Direction::RIGHT) anim[id].Ensure(AnimationType::LINK_ATTACK_RIGHT);
				if (ent_dir[id] == Direction::UP) anim[id].Ensure(AnimationType::LINK_ATTACK_UP);
				if (ent_dir[id] == Direction::LEFT) anim[id].Ensure(AnimationType::LINK_ATTACK_LEFT);
				if (ent_dir[id] == Direction::DOWN) anim[id].Ensure(AnimationType::LINK_ATTACK_DOWN);

				ent_timer[id] += dt;
		
				int new_pos_x = pos_x[id];
				int new_pos_y = pos_y[id];

				if (ent_dir[id] == Direction::UP) new_pos_y -= static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE / 3);
				if (ent_dir[id] == Direction::DOWN) new_pos_y += static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE / 3);
				if (ent_dir[id] == Direction::LEFT) new_pos_x -= static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE / 3);
				if (ent_dir[id] == Direction::RIGHT) new_pos_x += static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE / 3);

				if (ent_timer[id] >= SWORD_TIME)
				{
					ent_state[id] = PlayerState::IDLE;

					if (ent_dir[id] == Direction::UP) new_pos_y += TILE_SIZE / 3;
					if (ent_dir[id] == Direction::DOWN) new_pos_y -= TILE_SIZE / 3;
					if (ent_dir[id] == Direction::LEFT) new_pos_x += TILE_SIZE / 3;
					if (ent_dir[id] == Direction::RIGHT) new_pos_x -= TILE_SIZE / 3;

					ent_timer[id] = 0;
				}

				if (IsTileMoreOrLessPassable(new_pos_x, new_pos_y))
				{
					pos_x[id] = new_pos_x;
					pos_y[id] = new_pos_y;
				}

			} break;

			case ATTACK2:
			{
				if (ent_dir[id] == Direction::RIGHT) anim[id].Ensure(AnimationType::LINK_ATTACK_2_RIGHT);
				if (ent_dir[id] == Direction::UP) anim[id].Ensure(AnimationType::LINK_ATTACK_2_UP);
				if (ent_dir[id] == Direction::LEFT) anim[id].Ensure(AnimationType::LINK_ATTACK_2_LEFT);
				if (ent_dir[id] == Direction::DOWN) anim[id].Ensure(AnimationType::LINK_ATTACK_2_DOWN);

				ent_timer[id] += dt;

				int new_pos_x = pos_x[id];
				int new_pos_y = pos_y[id];

				if (ent_dir[id] == Direction::UP) new_pos_y -= static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE*2);
				if (ent_dir[id] == Direction::DOWN) new_pos_y += static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE*2);
				if (ent_dir[id] == Direction::LEFT) new_pos_x -= static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE*2);
				if (ent_dir[id] == Direction::RIGHT) new_pos_x += static_cast<int>(((float)(dt) / SWORD_TIME)*TILE_SIZE*2);

				if (IsTileMoreOrLessPassable(new_pos_x, new_pos_y))
				{
					pos_x[id] = new_pos_x;
					pos_y[id] = new_pos_y;
				}

				if (ent_timer[id] >= SWORD_TIME)
				{
					ent_state[id] = PlayerState::IDLE;
					ent_timer[id] = 0;
				}

			} break;


			case LEARNING_SKILL_SWORD:
			{
				ent_timer[id] += dt;

				anim[id].Ensure(AnimationType::LINK_IDLE_UP);
				ent_dir[id] = Direction::UP;

				if (input_state.IsJustPressed(GameKeys::ACTION))
				{
					ent_state[id] = PlayerState::ATTACK;

					int x = pos_x[id];
					int y = pos_y[id];

					EntS::SpawnEntity(EntityType::SWORD, x, y, id);

					ent_timer[id] = 0;
				}

			} break;

			case LEARNING_SKILL_ATTACK2:
			{
				ent_timer[id] += dt;

				anim[id].Ensure(AnimationType::LINK_IDLE_UP);
				ent_dir[id] = Direction::UP;

				if (input_state.IsJustPressed(GameKeys::ACTION))
				{
					ent_state[id] = PlayerState::ATTACK;

					int x = pos_x[id];
					int y = pos_y[id];

					EntS::SpawnEntity(EntityType::SWORD, x, y, id);

					ent_timer[id] = 0;
				}

			} break;

			case DEAD:
			{
				anim[id].Ensure(AnimationType::PLAYER_DEAD);
			} break;
		}
	}

	bool Collision(int a, int b)
	{
		//rectangle colision
		return (pos_x[a] < pos_x[b] + TILE_SIZE && pos_x[a] + TILE_SIZE > pos_x[b] &&
			pos_y[a] < pos_y[b] + TILE_SIZE && pos_y[a] + TILE_SIZE > pos_y[b]);
	}

	void RespawnBlobInWorldMap()
	{
		int roll_x = 2 + rnd_1d100(rnd_gen) % (MAP_SIZE_X - 4);
		int roll_y = 2 + rnd_1d100(rnd_gen) % (MAP_SIZE_Y - 4);

		int roll_wx = Roll1d100() % WORLD_MAP_SIZE_X;
		int roll_wy = Roll1d100() % WORLD_MAP_SIZE_Y;

		while (!IsTileWorldPassable(roll_x + roll_wx*MAP_SIZE_X, roll_y + roll_wy*MAP_SIZE_Y))
		{
			roll_x = 2 + rnd_1d100(rnd_gen) % (MAP_SIZE_X - 4);
			roll_y = 2 + rnd_1d100(rnd_gen) % (MAP_SIZE_Y - 4);
			roll_wx = Roll1d100()*Roll1d100() % WORLD_MAP_SIZE_X*MAP_SIZE_X;
			roll_wy = Roll1d100()*Roll1d100() % WORLD_MAP_SIZE_Y*MAP_SIZE_Y;
		}

		EntS::SpawnEntity(EntS::EntityType::BLOB, (roll_x + roll_wx * MAP_SIZE_X)*TILE_SIZE, (roll_y + roll_wy * MAP_SIZE_Y)*TILE_SIZE);
	}

	void OnApplyHitToBlob(int id)
	{
		ent_hp[id]--;
		if (ent_hp[id] <= 0)
		{
			ent_type[id] = NONE;

			EntS::SpawnEntity(EntS::EntityType::PUFF, pos_x[id], pos_y[id]);

			RespawnBlobInWorldMap();

			if (Roll1d100() < 20)
			{
				RespawnBlobInWorldMap();
			}
		}
		else
		{
			ent_state[id] = PlayerState::IDLE;
		}
	}

	void OnApplyHitToBat(int id)
	{
		static int it = 0;

		ent_hp[id]--;
		if (ent_hp[id] <= 0)
		{
			ent_type[id] = NONE;

			EntS::SpawnEntity(EntS::EntityType::PUFF, pos_x[id], pos_y[id]);
		}
		else
		{
			ent_state[id] = PlayerState::IDLE;
			anim[id].Ensure(AnimationType::BAT_IDLE);
		}
	}

	void OnTakeCollectible(int id)
	{
		EntityType type = ent_type[id];

		if (type == EntityType::HEART)
		{
			ent_hp[id_player] += HEART_HEAL;
			if (ent_hp[id_player] > LINK_MAX_HP)
			{
				ent_hp[id_player] = LINK_MAX_HP;
			}
		}

		if (type == EntityType::GREEN_RUPEE)
		{
			PlayerInfo::rupees += GREEN_RUPEE_VALUE;
			if (PlayerInfo::rupees > 50)
			{
				PlayerInfo::rupees = 50;
			}
		}
		if (type == EntityType::BLUE_RUPEE)
		{
			PlayerInfo::rupees += BLUE_RUPEE_VALUE;
			if (PlayerInfo::rupees > 50)
			{
				PlayerInfo::rupees = 50;
			}
		}
		if (type == EntityType::CAVE_KEY)
		{
			PlayerInfo::has_key = true;
		}

	}

	void UpdateCollisions(int dt)
	{

		//Collisions
		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			if (ent_type[i] == EntityType::NONE) continue;

#if _DEBUG
			bool is_weapon =
				(ent_type[i] == EntityType::SWORD ||
				 ent_type[i] == EntityType::SWORD2);
#else
			bool is_weapon = IsWeapon(ent_type[i]);
#endif

			//SWORD CORTA XESPA
			if (is_weapon)
			{
				int tiles[5][2] = 
				{
					{ (pos_x[i] + TILE_SIZE / 2 ) / TILE_SIZE, (pos_y[i] + TILE_SIZE / 2) / TILE_SIZE},

					{ (pos_x[i]+TILE_SIZE/2 + TILE_SIZE / 3) / TILE_SIZE, (pos_y[i]+TILE_SIZE/2 + TILE_SIZE / 3) / TILE_SIZE},
					{ (pos_x[i]+TILE_SIZE/2 + TILE_SIZE / 3) / TILE_SIZE, (pos_y[i]+TILE_SIZE/2 - TILE_SIZE / 3) / TILE_SIZE},
					{ (pos_x[i]+TILE_SIZE/2 - TILE_SIZE / 3) / TILE_SIZE, (pos_y[i]+TILE_SIZE/2 + TILE_SIZE / 3) / TILE_SIZE},
					{ (pos_x[i]+TILE_SIZE/2 - TILE_SIZE / 3) / TILE_SIZE, (pos_y[i]+TILE_SIZE/2 - TILE_SIZE / 3) / TILE_SIZE},
				};
				for (int t = 0; t < 5; ++t)
				{
					TileType tile = Tile_GetOnWorldMap(tiles[t][0], tiles[t][1]);
					if (	tile == TileType::GRASS
						||	tile == TileType::SUPER_GRASS)
					{
						SpawnLeaf(tiles[t][0]*TILE_SIZE + TILE_SIZE / 2, tiles[t][1] * TILE_SIZE + TILE_SIZE / 2);

						int x = pos_x[i] / TILE_SIZE;
						int y = pos_y[i] / TILE_SIZE;
						Tile_SetOnWorldMap(tiles[t][0], tiles[t][1], TileType::CUT_GRASS);

						if (Roll1d100() < 8)
						{
							if (Roll1d100() > 2)
							{
								if (tile == TileType::SUPER_GRASS)
								{
									if (Roll1d100() < 5)
									{
										EntS::SpawnEntity(EntityType::BLUE_RUPEE, pos_x[i], pos_y[i]);
									}
								}
								else
								{
									EntS::SpawnEntity(EntityType::GREEN_RUPEE, pos_x[i], pos_y[i]);
								}
							}
							else
							{
								EntS::SpawnEntity(EntityType::HEART, pos_x[i], pos_y[i]);
							}		
						}
					}
				}
				
			}

			bool is_link = ent_type[i] == EntityType::LINK;
			if (is_link)
			{

			}


			for (int j = 0; j < MAX_ENTITIES; j++)
			{
				if (ent_type[j] == EntityType::NONE) continue;
				if (i == j) continue;

				//WEAPON HITS BITXOS
				if (is_weapon && IsHittableBySword(ent_type[j]))
				{
					if (!IsInvulnerable(j) && Collision(i, j))
					{
						is_hitted[j] = true;
						timer_hit[j] = 0;
						ent_dir[j] = ReverseDir(ent_dir[i]);
						timer_invulnerable[j] = INVULNERABLE_TIME;
					}
				}

				//TRAINER ATTACK2
				if (ent_type[i] == EntityType::SWORD2 && ent_type[j] == EntityType::TRAINER_NPC_ATTACK2 && ent_state[j] != PlayerState::VANISHING)
				{
					ent_state[j] = PlayerState::VANISHING;
					ent_timer[j] = 0;
				}

				//LINK APRENDE LO QUE ES EL DOLOR
				if (ent_type[i] == EntityType::LINK && IsDamager(ent_type[j]))
				{
					if (!IsInvulnerable(i) && !IsInvulnerable(j) && Collision(i, j))
					{
						ent_hp[i] -= GREEN_BLOB_DMG;
						is_hitted[i] = true;
						timer_hit[i] = 0;
						timer_invulnerable[i] = INVULNERABLE_TIME_PLAYER;
						ent_state[i] = PlayerState::IDLE;
					}
				}

				//LINK PILLA COSAS
				if ((ent_type[i] == EntityType::LINK && IsCollectible(ent_type[j])) ||
					(IsWeapon(ent_type[i]) && IsCollectible(ent_type[j])))
				{
					if (ent_state[j] != SPAWNING && ent_state[j] != VANISHING && Collision(i, j))
					{
						OnTakeCollectible(j);

						ent_state[j] = PlayerState::VANISHING;
						ent_timer[j] = 0;
					}
				}

				//LINK PAGA COSAS
				/* TODO...
				if ((ent_type[i] == EntityType::LINK && IsCollectible(ent_type[j])) ||
					(IsWeapon(ent_type[i]) && IsCollectible(ent_type[j])))
				{
					if (ent_state[j] != SPAWNING && ent_state[j] != VANISHING && Collision(i, j))
					{
						OnTakeCollectible(j);

						ent_state[j] = PlayerState::VANISHING;
						ent_timer[j] = 0;
					}
				}
				*/


				//LINK PISA BUTTON
				if (ent_type[i] == EntityType::LINK &&
					ent_state[i] != PlayerState::ATTACK &&
					ent_state[i] != PlayerState::ATTACK2 &&
					ent_type[j] == EntityType::PUZZLE_CAVEKEY_BUTTON &&
					Collision(i, j))
				{
					Tile_SetOnWorldMap(pos_x[j]/TILE_SIZE, pos_y[j]/TILE_SIZE, TileType::PUZZLE_BUTTON_PRESSED);

					int id_parent = ent_idparent[j];
					ent_hp[id_parent] += 1;
					ent_type[j] = EntityType::NONE;
				}

				//TRAINER ACTIVATOR
				if (ent_type[i] == EntityType::LINK && 
					ent_state[i] != PlayerState::ATTACK &&
					ent_state[i] != PlayerState::ATTACK2 &&
					IsTrainerActivator(ent_type[j]) &&
					Collision(i,j))
				{
					int tx = (pos_x[i] + TILE_SIZE / 2);
					int ty = (pos_y[i] - TILE_SIZE / 2);

					int sx = (pos_x[j] + TILE_SIZE / 2);
					int sy = (pos_y[j] - TILE_SIZE / 2);

					if (Distance(tx, ty, sx, sy) < TILE_SIZE/4)
					{
						pos_x[i] = pos_x[j];
						pos_y[i] = pos_y[j];

						if (ent_type[j] == EntityType::TRAINER_ACTIVATOR_SWORD)
						{
							ent_type[j] = EntityType::NONE;
							ent_state[i] = PlayerState::LEARNING_SKILL_SWORD;
							ent_dir[i] = Direction::UP;
							PlayerInfo::sword_unlocked = true;
						}
						if (ent_type[j] == EntityType::TRAINER_ACTIVATOR_ATTACK2)
						{
							ent_state[i] = PlayerState::LEARNING_SKILL_ATTACK2;
							ent_dir[i] = Direction::UP;
							PlayerInfo::attack2_unlocked = true;
						}

						
					}

					
				}

			}
		}
	}

	void UpdateEntities(int dt)
	{

		for (int i = 0; i < MAX_ENTITIES; ++i)
		{
			ent_status[i] = 0;
		}

		UpdateCollisions(dt);

		for (int id = 0; id < MAX_ENTITIES; ++id)
		{
			if (ent_type[id] != EntityType::NONE  && is_hitted[id])
			{
				timer_hit[id] += dt;

				//Push after hit
				//if (ent_type[id] != EntityType::SPARRING)
				{
					int new_x = pos_x[id];
					int new_y = pos_y[id];

					if (ent_dir[id] == Direction::RIGHT) new_x -= dt * TILE_SIZE*2/HIT_TIME;
					if (ent_dir[id] == Direction::UP) new_y += dt * TILE_SIZE*2/ HIT_TIME;
					if (ent_dir[id] == Direction::LEFT) new_x += dt * TILE_SIZE*2/ HIT_TIME;
					if (ent_dir[id] == Direction::DOWN) new_y -= dt * TILE_SIZE*2/ HIT_TIME;

					if (IsTileMoreOrLessPassable(new_x, pos_y[id]))
					{
						pos_x[id] = new_x;
					}
					if (IsTileMoreOrLessPassable(pos_x[id], new_y))
					{
						pos_y[id] = new_y;
					}

				}

				if (timer_hit[id] >= HIT_TIME)
				{
					is_hitted[id] = false;

					if (ent_type[id] == EntityType::BLOB)
					{
						OnApplyHitToBlob(id);
					}

					if (ent_type[id] == EntityType::BAT)
					{
						OnApplyHitToBat(id);
					}
					
					if (ent_type[id] == EntityType::LINK)
					{
						if (ent_hp[id] <= 0)
						{
							ent_state[id] = PlayerState::DEAD;
						}
					}
					
				}
			}

			timer_invulnerable[id] -= dt;

			switch (ent_type[id])
			{
				case EntityType::BLOB:
				{
					UpdateBlob(dt, id);
				} break;

				case EntityType::BAT:
				{
					UpdateBat(dt, id);
				}break;

				case EntityType::FADA:
				{
					ent_timer[id] += dt;

					target[id] = id_player;

					int target_x = pos_x[target[id]];
					int target_y = pos_y[target[id]];

					double s = sin(ent_timer[id]*3.14f / 2500.0f );
					double c = sin(ent_timer[id]*3.14f / 1250.0f );
					int dest_x = static_cast<int>(target_x + s * 4800);
					int dest_y = static_cast<int>(target_y + c * 4800);
					
					int diff_x = (dest_x - pos_x[id]);
					if (diff_x > 0) pos_x[id] += speed[id]*dt;
					else if (diff_x < 0) pos_x[id] -= speed[id]*dt;

					int diff_y = (dest_y - pos_y[id]);
					if (diff_y > 0) pos_y[id] += speed[id] * dt;
					else if (diff_y < 0) pos_y[id] -= speed[id] * dt;

					if (diff_x < 0) diff_x = -diff_x;
					if (diff_x < speed[id]*15) pos_x[id] = dest_x;
					if (diff_y < 0) diff_y = -diff_y;
					if (diff_y < speed[id]*15) pos_y[id] = dest_y;

				} break;

				case EntityType::LINK:
				{
					UpdateLink(id, dt);
				} break;

				case EntityType::SWORD:
				{
					if (ent_dir[id] == Direction::UP) anim[id].Ensure(AnimationType::SWORD_ATTACK_UP);
					if (ent_dir[id] == Direction::DOWN) anim[id].Ensure(AnimationType::SWORD_ATTACK_DOWN);
					if (ent_dir[id] == Direction::LEFT) anim[id].Ensure(AnimationType::SWORD_ATTACK_LEFT);
					if (ent_dir[id] == Direction::RIGHT) anim[id].Ensure(AnimationType::SWORD_ATTACK_RIGHT);

					int time_before = ent_timer[id];
					ent_timer[id] += dt;
					
					pos_x[id] = pos_x[id_player];
					pos_y[id] = pos_y[id_player];

					if (ent_timer[id] < SWORD_TIME/3)
					{
						if (ent_dir[id] == Direction::UP)
						{
							pos_x[id] += TILE_SIZE;
							pos_y[id] -= TILE_SIZE / 4;
						}
						if (ent_dir[id] == Direction::DOWN)
						{
							pos_x[id] -= 3 * TILE_SIZE / 4;
						}
						if (ent_dir[id] == Direction::LEFT)
						{
							pos_y[id] -= TILE_SIZE;
						}
						if (ent_dir[id] == Direction::RIGHT)
						{
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] -= TILE_SIZE;
						}
					}
					else if (ent_timer[id] < 2*SWORD_TIME/3)
					{
						if (ent_dir[id] == Direction::UP)
						{
							pos_x[id] += TILE_SIZE;
							pos_y[id] -= TILE_SIZE / 4;
							pos_x[id] -= TILE_SIZE/4;
							pos_y[id] -= TILE_SIZE/4;
						}
						if (ent_dir[id] == Direction::DOWN)
						{
							pos_x[id] -= 3 * TILE_SIZE / 4;
							pos_y[id] += 2*TILE_SIZE/3;
						}
						if (ent_dir[id] == Direction::LEFT)
						{
							pos_y[id] -= TILE_SIZE;
							pos_x[id] -= 2*TILE_SIZE/3;
							pos_y[id] += TILE_SIZE / 8;
						}
						if (ent_dir[id] == Direction::RIGHT)
						{
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] -= TILE_SIZE;
							pos_x[id] += TILE_SIZE/3;
							pos_y[id] += TILE_SIZE / 8;
						}
					}
					else if (ent_timer[id] < SWORD_TIME)
					{
						if (ent_dir[id] == Direction::UP)
						{
							pos_x[id] += TILE_SIZE;
							pos_y[id] -= TILE_SIZE / 4;
							pos_x[id] -= TILE_SIZE / 4;
							pos_y[id] -= TILE_SIZE / 4;
							pos_x[id] -= TILE_SIZE *3/4;
							pos_y[id] -= TILE_SIZE / 4;
						}
						if (ent_dir[id] == Direction::DOWN)
						{
							pos_x[id] -= 3 * TILE_SIZE / 4;
							pos_y[id] += 2 * TILE_SIZE / 3;
							pos_x[id] += 3*TILE_SIZE/4;
							pos_y[id] += TILE_SIZE / 3;
						}
						if (ent_dir[id] == Direction::LEFT)
						{
							pos_y[id] -= TILE_SIZE;
							pos_x[id] -= 2 * TILE_SIZE / 3;
							pos_y[id] += TILE_SIZE / 8;
							pos_x[id] -= TILE_SIZE / 3;
							pos_y[id] += 7*TILE_SIZE / 8;
						}
						if (ent_dir[id] == Direction::RIGHT)
						{
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] -= TILE_SIZE;
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] += TILE_SIZE / 8;
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] += 7*TILE_SIZE/8;
						}
					}
					else
					{
						ent_type[id] = EntityType::NONE;
					}
				} break;

				case EntityType::SWORD2:
				{
					if (ent_dir[id] == Direction::UP) anim[id].Ensure(AnimationType::SWORD_ATTACK_2_UP);
					if (ent_dir[id] == Direction::DOWN) anim[id].Ensure(AnimationType::SWORD_ATTACK_2_DOWN);
					if (ent_dir[id] == Direction::LEFT) anim[id].Ensure(AnimationType::SWORD_ATTACK_2_LEFT);
					if (ent_dir[id] == Direction::RIGHT) anim[id].Ensure(AnimationType::SWORD_ATTACK_2_RIGHT);

					int time_before = ent_timer[id];
					ent_timer[id] += dt;

					pos_x[id] = pos_x[id_player];
					pos_y[id] = pos_y[id_player];

					if (ent_timer[id] < SWORD_TIME / 3)
					{
						if (ent_dir[id] == Direction::UP)
						{
						//	pos_x[id] += TILE_SIZE;
						// pos_y[id] -= TILE_SIZE / 4;

							pos_y[id] -= TILE_SIZE;
							pos_x[id] -= 2 * TILE_SIZE / 3;
							pos_y[id] += TILE_SIZE / 8;
							pos_x[id] -= TILE_SIZE / 3;
							pos_y[id] += 7 * TILE_SIZE / 8;
						}
						if (ent_dir[id] == Direction::DOWN)
						{
							//pos_x[id] -= 3 * TILE_SIZE / 4;

							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] -= TILE_SIZE;
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] += TILE_SIZE / 8;
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] += 7 * TILE_SIZE / 8;
						}
						if (ent_dir[id] == Direction::LEFT)
						{
							//pos_y[id] -= TILE_SIZE;

							pos_x[id] -= 3 * TILE_SIZE / 4;
							pos_y[id] += 2 * TILE_SIZE / 3;
							pos_x[id] += 3 * TILE_SIZE / 4;
							pos_y[id] += TILE_SIZE / 3;
						}
						if (ent_dir[id] == Direction::RIGHT)
						{
							//pos_x[id] += TILE_SIZE / 3;
							//pos_y[id] -= TILE_SIZE;

							pos_x[id] -= 3 * TILE_SIZE / 4;
							pos_y[id] += 2 * TILE_SIZE / 3;
							pos_x[id] += 3 * TILE_SIZE / 4;
							pos_y[id] += TILE_SIZE / 3;
						}
					}
					else if (ent_timer[id] < 2 * SWORD_TIME / 3)
					{
						if (ent_dir[id] == Direction::UP)
						{
							//pos_x[id] += TILE_SIZE;
							//pos_y[id] -= TILE_SIZE / 4;
							//pos_x[id] -= TILE_SIZE / 4;
							//pos_y[id] -= TILE_SIZE / 4;

							pos_y[id] -= TILE_SIZE;
							pos_x[id] -= 2 * TILE_SIZE / 3;
							pos_y[id] += TILE_SIZE / 8;
						}
						if (ent_dir[id] == Direction::DOWN)
						{
							//pos_x[id] -= 3 * TILE_SIZE / 4;
							//pos_y[id] += 2 * TILE_SIZE / 3;

							pos_x[id] += 3 * TILE_SIZE / 4;
							pos_y[id] += 2 * TILE_SIZE / 3;
						}
						if (ent_dir[id] == Direction::LEFT)
						{
							//pos_y[id] -= TILE_SIZE;
							//pos_x[id] -= 2 * TILE_SIZE / 3;
							//pos_y[id] += TILE_SIZE / 8;

							pos_x[id] -= 3 * TILE_SIZE / 4;
							pos_y[id] += 2 * TILE_SIZE / 3;
						}
						if (ent_dir[id] == Direction::RIGHT)
						{
							//pos_x[id] += TILE_SIZE / 3;
							//pos_y[id] -= TILE_SIZE;
							//pos_x[id] += TILE_SIZE / 3;
							//pos_y[id] += TILE_SIZE / 8;

							pos_x[id] += 3 * TILE_SIZE / 4;
							pos_y[id] += 2 * TILE_SIZE / 3;
						}
					}
					else if (ent_timer[id] < SWORD_TIME)
					{
						if (ent_dir[id] == Direction::UP)
						{
							pos_x[id] += TILE_SIZE;
							pos_y[id] -= TILE_SIZE / 4;
							pos_x[id] -= TILE_SIZE / 4;
							pos_y[id] -= TILE_SIZE / 4;
							pos_x[id] -= TILE_SIZE * 3 / 4;
							pos_y[id] -= TILE_SIZE / 4;
						}
						if (ent_dir[id] == Direction::DOWN)
						{
							pos_x[id] -= 3 * TILE_SIZE / 4;
							pos_y[id] += 2 * TILE_SIZE / 3;
							pos_x[id] += 3 * TILE_SIZE / 4;
							pos_y[id] += TILE_SIZE / 3;
						}
						if (ent_dir[id] == Direction::LEFT)
						{
							pos_y[id] -= TILE_SIZE;
							pos_x[id] -= 2 * TILE_SIZE / 3;
							pos_y[id] += TILE_SIZE / 8;
							pos_x[id] -= TILE_SIZE / 3;
							pos_y[id] += 7 * TILE_SIZE / 8;
						}
						if (ent_dir[id] == Direction::RIGHT)
						{
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] -= TILE_SIZE;
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] += TILE_SIZE / 8;
							pos_x[id] += TILE_SIZE / 3;
							pos_y[id] += 7 * TILE_SIZE / 8;
						}
					}
					else
					{
						ent_type[id] = NONE;
					}
				} break;

				case EntityType::PUFF:
				{
					ent_timer[id] += dt;

					anim[id].Ensure(AnimationType::PUFF);

					if (ent_timer[id] > PUFF_TIME)
					{
						ent_type[id] = NONE;

						//HEART SPAWN
						int r = Roll1d100();
						if (r < 50)
						{
							if (r < 10)
							{
								EntS::SpawnEntity(EntS::EntityType::HEART, pos_x[id], pos_y[id]);
							}
							else if (r < 50)
							{
								EntS::SpawnEntity(EntityType::BLUE_RUPEE, pos_x[id], pos_y[id]);
							}
							else
							{
								EntS::SpawnEntity(EntityType::GREEN_RUPEE, pos_x[id], pos_y[id]);
							}
						}
					}
				} break;

				case EntityType::HEART:
				case EntityType::GREEN_RUPEE:
				case EntityType::BLUE_RUPEE:
				case EntityType::CAVE_KEY:
				{
					int timer_before = ent_timer[id];
					ent_timer[id] += dt;

					if (ent_state[id] == SPAWNING)
					{
						if (ent_timer[id] < 150)
						{
							pos_y[id] -= dt * TILE_SIZE / 75;
							
						}
						else if (ent_timer[id] < 300)
						{
							pos_y[id] += dt * TILE_SIZE / 75;

						}
						else if (ent_timer[id] < 400)
						{
							pos_y[id] -= dt * TILE_SIZE / 100;
						}
						else if (ent_timer[id] < 500)
						{
							pos_y[id] += dt * TILE_SIZE / 100;
						}
						
						else
						{
							ent_state[id] = PlayerState::IDLE;
						}
					}

					if (ent_state[id] == PlayerState::IDLE)
					{
						if (!IsCollectibleForever(ent_type[id]) && ent_timer[id] >= (COLLECTIBLE_DISSAPEAR_TIME*3)/4)
						{
							ent_state[id] = PlayerState::DISSAPEAR;
							ent_timer[id] = 0;
						}
					}

					if (ent_state[id] == PlayerState::DISSAPEAR)
					{
						if (ent_timer[id] >= (COLLECTIBLE_DISSAPEAR_TIME*1)/4)
						{
							ent_type[id] = NONE;
						}
					}

					if (ent_state[id] == PlayerState::VANISHING)
					{
						int player_x = pos_x[id_player];
						int player_y = pos_y[id_player];

						int dir_x = 1;
						if (player_x - pos_x[id] < 0) dir_x = -1;

						int dir_y = 1;
						if (player_y - pos_y[id] < 0) dir_y = -1;

						pos_x[id] += dt * dir_x * 5;
						pos_y[id] += dt * dir_y * 5;

						ent_timer[id] += dt;

						if (ent_timer[id] > VANISH_TIME)
						{
							ent_type[id] = NONE;
						}
					}

				} break;

				case EntityType::GRASS_CUT_PARTICLE:
				{
					ent_timer[id] += dt;

					if (ent_timer[id] < CUT_GRASS_TIME / 2)
					{
						angle[id] += 2;
					}
					else if (ent_timer[id] > CUT_GRASS_TIME / 2 &&
						ent_timer[id] < CUT_GRASS_TIME)
					{
						angle[id] += 1;
					}

					MoveToEntityDirection(id, dt);

					if (speed[id] > 3)
					{
						speed[id] -= 1;
					}
					else
					{
						speed[id] = 3;
					}

					if (ent_timer[id] > CUT_GRASS_TIME)
					{
						ent_type[id] = EntityType::NONE;
					}

				} break;

				case SMOKE_PARTICLE:
				{
					ent_timer[id] += dt;

					if (ent_timer[id] < SMOKE_PARTICLE_TIME / 2)
					{
						angle[id] += 4;
						angle[id] %= 359;
					}
					else if (ent_timer[id] > SMOKE_PARTICLE_TIME / 2 &&
						ent_timer[id] < CUT_GRASS_TIME)
					{
						angle[id] += 2;
						angle[id] %= 359;
					}
					
					MoveToEntityDirection(id, dt);

					if (ent_timer[id] > SMOKE_PARTICLE_TIME)
					{
						ent_type[id] = EntityType::NONE;
					}

				} break;


				case TRAINER_NPC_ATTACK2:
				{
					if (ent_state[id] == PlayerState::VANISHING)
					{
						ent_timer[id] += dt;

						if (ent_timer[id] > TRAINER_VANISHING_TIME)
						{
							ent_type[id] = NONE;
							ent_type[ent_idparent[id]] = NONE;
						}
					}
					
				} break;

				case TRAINER_ACTIVATOR_ATTACK2:
				{
					
					
				} break;

				case PUZZLE_CAVEKEY:
				{
					if (ent_hp[id] >= 4)
					{
						SpawnEntity(EntityType::CAVE_KEY, pos_x[id], pos_y[id] - TILE_SIZE/2);

						ent_type[id] = EntityType::NONE;
					}
				} break;

			}

			if (ent_type[id] != EntityType::NONE)
			{
				anim[id].Update(dt);
			}
		}
	}

	void DrawEntities(int world_x, int world_y, sf::Sprite& spr, sf::RenderWindow& wnd)
	{

		std::vector<int> draw_list;

		for (int id = 0; id < MAX_ENTITIES; ++id)
		{
			if (IsInCurrentMap(world_x, world_y, pos_x[id], pos_y[id]) &&
				ent_type[id] != NONE &&
				ent_type[id] != GRASS && 
				!IsCollectible(ent_type[id]))
			{
				draw_list.push_back(id);
			}
		}
		
		std::sort(draw_list.begin(), draw_list.end(), [](int i, int j)
		{

			return pos_y[i] < pos_y[j];
		});
		for (int id = 0; id < MAX_ENTITIES; ++id)
		{
			if (
				IsInCurrentMap(world_x, world_y, pos_x[id], pos_y[id]) &&
				IsCollectible(ent_type[id]))
			{
				draw_list.push_back(id);
			}
		}

		for (size_t i = 0; i < draw_list.size(); ++i)
		{
			int id = draw_list[i];

			spr.setScale(2, 2);
			spr.setRotation(static_cast<float>(angle[id]));
			spr.setOrigin(0, 0);
			
			int x = pos_x[id];
			int y = pos_y[id];

			int tx = x / TILE_SIZE;
			int ty = y / TILE_SIZE;
			
			spr.setTextureRect(anim[id].CurrentFrame());

			spr.setColor(sf::Color::White);
			if (is_hitted[id])
			{
				int t = timer_hit[id] % 50;
				if (t > 25)
				{
					spr.setColor(sf::Color::Red);
				}
				else
				{
					spr.setColor(sf::Color::Yellow);
				}
			}

			if (IsInvulnerable(id))
			{
				int t = timer_invulnerable[id] % 50;
				if (t > 25)
				{
					spr.setColor(sf::Color::Red);
				}
				else
				{
					spr.setColor(sf::Color(255, 255, 255, 128));
				}
			}

			if (ent_state[id] == VANISHING)
			{
				int a = 255 - (int)(255 * (((float)ent_timer[id]) / ((float)VANISH_TIME)));

				
				if (a < 128) a = 128;
				if (a > 192) a = 255;

				spr.setColor(sf::Color(255, 255, 255, a));
			}

			if (ent_state[id] == DISSAPEAR)
			{
				int a;
				if (ent_timer[id] % COLLECTIBLE_BLINKING_TIME < COLLECTIBLE_BLINKING_TIME / 2)
				{
					a = 255 - (int)(255 * (((float)(ent_timer[id] % (COLLECTIBLE_BLINKING_TIME / 2)))  / ((float)COLLECTIBLE_BLINKING_TIME / 2)));
				}
				else
				{
					a = 255 + (int)(255 * (((float)(ent_timer[id] % (COLLECTIBLE_BLINKING_TIME / 2))) / ((float)COLLECTIBLE_BLINKING_TIME / 2)));
				}

				spr.setColor(sf::Color(255, 255, 255, a));

			}

			if (ent_type[id] == GRASS_CUT_PARTICLE)
			{
				spr.setColor(sf::Color(255, 255, 255, 180));
			}


			if (ent_type[id] == SMOKE_PARTICLE)
			{
				float factor = (Roll1d100() / 100) + 0.30f;
				spr.setScale(factor, factor);
				spr.setOrigin(8, 8);
				spr.setColor(sf::Color(255, 255, 255, 180));
			}


			spr.setPosition(x / 100.0f, y / 100.0f);
			spr.move(0, MARGIN_TOP_GUI);


			if (ent_type[id] == TRAINER_NPC_ATTACK2 && ent_state[id] == VANISHING)
			{
				spr.move(0, -(ent_timer[id] * TILE_SIZE/100 * 2) / (TRAINER_VANISHING_TIME));
				spr.setColor(sf::Color(255, 255, 255, 255 - (255*ent_timer[id]/ TRAINER_VANISHING_TIME)));
			}

			wnd.draw(spr);

			if (ent_type[id] == LINK && ent_state[id] == LEARNING_SKILL_SWORD)
			{
				spr.setTextureRect(Animation::AnimFrame(AnimationType::TRAINER_ACTIVATOR_COMBO_SWORD, ent_timer[id]));
				spr.move(TILE_SIZE*1.5f / 100, -TILE_SIZE * 0.25f / 100);
				wnd.draw(spr);
			}

			if (ent_type[id] == LINK && ent_state[id] == LEARNING_SKILL_ATTACK2)
			{
				spr.setTextureRect(Animation::AnimFrame(AnimationType::TRAINER_ACTIVATOR_COMBO_ATTACK2, ent_timer[id]));
				spr.move(TILE_SIZE*1.5f / 100, -TILE_SIZE*0.25f/100);
				wnd.draw(spr);
			}


			

#if _DEBUG
			/*
			static sf::RectangleShape hitbox;
			hitbox.setPosition(spr.getPosition());
			hitbox.setSize(sf::Vector2f(32, 32));
			hitbox.setOutlineColor(sf::Color::Red);
			hitbox.setOutlineThickness(1);
			hitbox.setFillColor(sf::Color::Transparent);
			wnd.draw(hitbox);
			*/
#endif

			//Esconder en xespa
			{
				int xespa_x = (pos_x[id] + TILE_SIZE / 2) / TILE_SIZE;
				int xespa_y = (pos_y[id] + TILE_SIZE) / TILE_SIZE;
				if (EntS::IsAliveEntity(ent_type[id]) && Tile_GetOnWorldMap(xespa_x, xespa_y) == TileType::GRASS)
				{
					spr.setScale(2, 2);
					spr.setPosition(pos_x[id] / 100.0f, pos_y[id] / 100.0f + 16);

					int cosa = std::abs(pos_x[id] * pos_y[id]) % TILE_SIZE;
					cosa = cosa / (TILE_SIZE / 2);

					spr.setTextureRect(sf::IntRect(1 * 16, 8 * 16 + cosa * 8, 16, 8));

					spr.setColor(sf::Color::White);

					spr.move(0, MARGIN_TOP_GUI);
					wnd.draw(spr);
				}
			}
			
		}

	}
}

void InitGUI()
{
	GUI_text.setFont(font);

	GUI_hp_draw = EntS::ent_hp[EntS::id_player];
	GUI_rupees = PlayerInfo::rupees;
	GUI_rupee_richer_timer = -1;
	GUI_hearts_dmg_timer = 0;
}

void UpdateGUI(int dt)
{	
	
	if (EntS::ent_hp[EntS::id_player] > GUI_hp_draw && !GUI_isPlayerHealing)
	{
		GUI_hp_draw++;
		GUI_isPlayerHealing = true;
		GUI_hearts_timer = 0;
		
	}
	else if (EntS::ent_hp[EntS::id_player] < GUI_hp_draw)
	{
		GUI_is_dmg = true;
		GUI_hp_draw = EntS::ent_hp[EntS::id_player];
	}


	if (GUI_isPlayerHealing)
	{
		GUI_hearts_timer += dt;
		if (GUI_hearts_timer >= GUI_HEART_HEAL_TIME)
		{
			GUI_isPlayerHealing = false;
		}

	}

	if (GUI_is_dmg)
	{
		GUI_hearts_dmg_timer += dt;
		if (GUI_hearts_dmg_timer >= GUI_HEART_DMG_TIME)
		{
			GUI_is_dmg = false;
			GUI_hearts_dmg_timer = 0;
		}
	}
	
	if (GUI_rupee_richer_timer < 0 && PlayerInfo::rupees > GUI_rupees)
	{
		GUI_rupee_richer_timer = 0;
	}

	if (GUI_rupee_richer_timer > -1)
	{

		GUI_rupee_richer_timer += dt;

		if (GUI_rupee_richer_timer >= GUI_RUPEE_RICHER_TIME)
		{
			GUI_rupee_richer_timer = -1;
			GUI_rupees++;
		}
	}
	
	
}


void DrawGUI(sf::RenderWindow& wnd, sf::Sprite& spr)
{
	sf::Text& text = GUI_text;

	sf::RectangleShape background(sf::Vector2f((float)WINDOW_WIDTH, (float)MARGIN_TOP_GUI));
	background.setPosition(0, 0);
	background.setFillColor(sf::Color::Black);
	wnd.draw(background);
	spr.setOrigin(0, 0);


	//HEARTS
	spr.setColor(sf::Color::White);
	spr.setRotation(0);
	spr.setScale(4, 4);

	int hp_link = GUI_hp_draw;
	int lastDmgHeart = GUI_hp_draw / 2;
	int lastHealHeart = GUI_hp_draw  % 2 != 0 ? GUI_hp_draw / 2 : (GUI_hp_draw - 1) / 2;

	int j = 0;

	for (int i = 0; i < LINK_MAX_HP / 2; ++i)
	{
		if (i < 10)
		{
			int x = ((i + 1) * 25) + (6 * i);
			spr.setPosition(x*1.0f, 25.0f);
		}
		else
		{
			int x = ((j + 1) * 25) + (6 * j);
			spr.setPosition(x*1.0f, 55.0f);
			j++;
		}

		if (hp_link >= 2)
		{
			spr.setTextureRect(sf::IntRect(2 * 16 + 0, 0, 8, 8));

		}
		else if (hp_link == 1)
		{
			spr.setTextureRect(sf::IntRect(2 * 16 + 8, 0, 8, 8));
		}
		else
		{
			spr.setTextureRect(sf::IntRect(16, 0, 8, 8));
		}


		hp_link -= 2;

		// Corazon parpadea y se agranda si hay daño
		if (GUI_is_dmg)
		{
			if (i + j == lastDmgHeart)
			{
				spr.setScale(6, 6);
				spr.setPosition(spr.getPosition().x - 6, spr.getPosition().y - 6);
				spr.setColor(sf::Color::Red);
			}
			else
			{
				spr.setOrigin(0, 0);
				spr.setScale(4, 4);
			}
		}
		else
		{
			spr.setColor(sf::Color::White);
		}

		//Corazon se agranda si se cura
		if (GUI_isPlayerHealing)
		{
			if (i + j == lastHealHeart)
			{
				float time = ((float)GUI_hearts_timer / (float)GUI_HEART_HEAL_TIME);
				spr.setScale(4 + 2 * time, 4 + 2 * time);
				spr.setPosition(spr.getPosition().x - 6 * time, spr.getPosition().y - 6 * time);
			}
			else
			{
				spr.setOrigin(0, 0);
				spr.setScale(4, 4);
			}
		}

		wnd.draw(spr);

	}

	wnd.draw(spr);

	//RUPEES

	float rupees_pos_x = WINDOW_WIDTH * 1.0f - WINDOW_WIDTH * 0.20f;
	float rupees_pos_y = 20.0f;
	float rupees_scale = 3.0f;

	spr.setTextureRect(sf::IntRect(4 * 16, 3 * 16, 16, 16));
	spr.setPosition(rupees_pos_x, rupees_pos_y);
	spr.setOrigin(0, 0);

	if (GUI_rupee_richer_timer > -1)
	{
		float time = ((float)GUI_rupee_richer_timer / (float)GUI_RUPEE_RICHER_TIME);

		float x_final = rupees_pos_x - 11.0f;
		float dx = (x_final - rupees_pos_x)*time;

		float y_final = 20.f - 15.0f;
		float dy = (y_final - rupees_pos_y)*time;

		float sc_final = 4.5f;
		float ds = (sc_final - 3.0f)*time;

		spr.setScale(rupees_scale + ds, rupees_scale + ds);
		spr.setPosition(rupees_pos_x + dx, rupees_pos_y + dy);
	}
	else
	{
		spr.setScale(rupees_scale, rupees_scale);
	}
	spr.setColor(sf::Color::White);
	spr.setOrigin(0, 0);

	wnd.draw(spr);


	
	std::string rupees_txt = std::to_string(GUI_rupees);
	std::string rupees_format = "";
	rupees_format.append(3 - rupees_txt.length(), '0').append(rupees_txt);

	text.setString(rupees_format);
	text.setCharacterSize(24);
	text.setPosition(rupees_pos_x + 36, 32);
	if (GUI_rupees < 50)
	{
		text.setFillColor(sf::Color::White);
	}
	else
	{
		text.setFillColor(sf::Color::Green);

	}
	
	wnd.draw(text);

	
	//DRAW KEY
	if (PlayerInfo::has_key)
	{
		spr.setTextureRect(sf::IntRect(9 * 16, 4 * 16, 16, 16));
		spr.setPosition(rupees_pos_x + 10, rupees_pos_y + (TILE_SIZE / 100 * 2));
		spr.setScale(2, 2);
		wnd.draw(spr);
	}
}

void GenerateHouseWood(int tx, int ty)
{
	Tile_SetOnWorldMap(tx, ty, TileType::ROOF_TL);
	Tile_SetOnWorldMap(tx + 1, ty, TileType::ROOF_T);
	Tile_SetOnWorldMap(tx + 2, ty, TileType::ROOF_TR);
	Tile_SetOnWorldMap(tx, ty + 1, TileType::ROOF_BL);
	Tile_SetOnWorldMap(tx + 1, ty + 1, TileType::ROOF_B);
	Tile_SetOnWorldMap(tx + 2, ty + 1, TileType::ROOF_BR);

	Tile_SetOnWorldMap(tx, ty + 2, TileType::HOUSE_WINDOW_WOOD);
	Tile_SetOnWorldMap(tx + 1, ty + 2, TileType::HOUSE_DOOR_WOOD);
	Tile_SetOnWorldMap(tx + 2, ty + 2, TileType::HOUSE_WINDOW_WOOD);
	
	
}

void GenerateHouseStone(int tx, int ty)
{
	Tile_SetOnWorldMap(tx, ty, TileType::ROOF_TL);
	Tile_SetOnWorldMap(tx + 1, ty, TileType::ROOF_T);
	Tile_SetOnWorldMap(tx + 2, ty, TileType::ROOF_TR);
	Tile_SetOnWorldMap(tx, ty + 1, TileType::ROOF_BL);
	Tile_SetOnWorldMap(tx + 1, ty + 1, TileType::ROOF_B);
	Tile_SetOnWorldMap(tx + 2, ty + 1, TileType::ROOF_BR);

	
	Tile_SetOnWorldMap(tx, ty + 2, TileType::HOUSE_WINDOW_STONE);
	Tile_SetOnWorldMap(tx + 1, ty + 2, TileType::HOUSE_DOOR_STONE);
	Tile_SetOnWorldMap(tx + 2, ty + 2, TileType::HOUSE_WINDOW_STONE);
}

void GenerateCaveEntrance(int tx, int ty)
{
	Tile_SetOnWorldMap(tx, ty, TileType::CAVE_TL);
	Tile_SetOnWorldMap(tx + 1, ty, TileType::CAVE_T);
	Tile_SetOnWorldMap(tx + 2, ty, TileType::CAVE_TR);
	Tile_SetOnWorldMap(tx, ty + 1, TileType::CAVE_BL);
	Tile_SetOnWorldMap(tx + 1, ty + 1, TileType::CAVE_DOOR_LOCKED);
	Tile_SetOnWorldMap(tx + 2, ty + 1, TileType::CAVE_BR);

}




void GenerateDojo(int tx_house, int ty_house, int tx_inside, int ty_inside)
{
	int mx = (tx_inside / MAP_SIZE_X) * MAP_SIZE_X;
	int my = (ty_inside / MAP_SIZE_Y) * MAP_SIZE_Y;

	GenerateHouseWood(tx_house, ty_house);
	SetTeleportLink(tx_house+1, ty_house+2, mx + MAP_SIZE_X / 2, my + MAP_SIZE_Y * 5/6 -1);
	
	//Clear Inside Map
	for (int j = 0; j < MAP_SIZE_Y; ++j)
	{
		for (int i = 0; i < MAP_SIZE_X; ++i)
		{
			world_map[my+j][mx+i].type = TileType::NONE;
		}
	}

	//Make Floors
	for (int j = MAP_SIZE_Y*1/6; j < MAP_SIZE_Y*5/6; ++j)
	{
		for (int i = MAP_SIZE_X*1/4; i <= MAP_SIZE_X*3/4; ++i)
		{
			world_map[my+j][mx+i].type = TileType::HOUSE_INSIDE_FLOOR;
		}
	}

	world_map[my + MAP_SIZE_Y * 5 / 6][mx + MAP_SIZE_X/2 -1].type = TileType::HOUSE_INSIDE_DOOR_LEFT;
	world_map[my + MAP_SIZE_Y * 5 / 6][mx + MAP_SIZE_X/2].type = TileType::HOUSE_INSIDE_DOOR_HOLE;
	world_map[my + MAP_SIZE_Y * 5 / 6][mx + MAP_SIZE_X/2 +1].type = TileType::HOUSE_INSIDE_DOOR_RIGHT;

	SetTeleportLink((mx + MAP_SIZE_X / 2), (my + MAP_SIZE_Y * 5 / 6), tx_house + 1, ty_house + 3);

	int tile_activator_x = (mx + MAP_SIZE_X / 2);
	int tile_activator_y = ((my + MAP_SIZE_Y * 2 / 6) + 4);

	int id_activator = EntS::SpawnEntity(EntS::EntityType::TRAINER_ACTIVATOR_ATTACK2, tile_activator_x*TILE_SIZE, tile_activator_y*TILE_SIZE);
	EntS::SpawnEntity(EntS::EntityType::TRAINER_NPC_ATTACK2, (mx + MAP_SIZE_X / 2)*TILE_SIZE, (tile_activator_y-2)*TILE_SIZE - TILE_SIZE/2, id_activator);
	Tile_SetOnWorldMap(tile_activator_x, tile_activator_y, TileType::TILE_SPECIAL);
	
}

bool TileTreeCanBePlaced(TileType type)
{
	return IsTilePassable(type) && 
		(type != TileType::PUZZLE_BUTTON) && 
		(type != TileType::PUZZLE_BUTTON_PRESSED);
}

void GenerateForestRoom(int w_x, int w_y)
{
	for (int j = 0; j < MAP_SIZE_Y; ++j)
	{
		for (int i = 0; i < MAP_SIZE_X; ++i)
		{
			int roll = rnd_1d100(rnd_gen);
			Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::CUT_GRASS);
			if (roll < 80)  Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::GRASS);
			if (roll == 21 && Roll1d100() < 60)  Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::ROCK);
			if (roll < 20)  Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::FIELD);
			if (roll < 15)  Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::SUPER_GRASS);
			if (roll < 10)  Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::FLOWER);
			if ((roll < 3) && (i > 0) && (j > 0) && (i < MAP_SIZE_X - 4) && (j < MAP_SIZE_Y - 4))
			{
				Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_TL);
			}
		}
	}

}


void GenerateBushLabyrinth(int w_x, int w_y, int start_x, int start_y, int end_x, int end_y, bool visited[MAP_SIZE_X][MAP_SIZE_Y])
{
	bool caminito[MAP_SIZE_X][MAP_SIZE_Y];
	int superset[MAP_SIZE_X][MAP_SIZE_Y];

	for (int i = 0; i < MAP_SIZE_X; ++i)
	{
		for (int j = 0; j < MAP_SIZE_Y; ++j)
		{
			caminito[i][j] = false;
			superset[i][j] = i * MAP_SIZE_Y + j;
		}
	}

	visited[end_x][end_y] = true;
	std::vector<int> to_visit_x;
	std::vector<int> to_visit_y;
	to_visit_x.push_back(start_x);
	to_visit_y.push_back(start_y);
	visited[start_x][start_y] = true;
	caminito[start_x][start_y] = true;
	while (to_visit_x.size() > 0)
	{
		int r = Roll1d100() % to_visit_x.size();

		int x = to_visit_x[r];
		to_visit_x.erase(to_visit_x.begin() + r);

		int y = to_visit_y[r];
		to_visit_y.erase(to_visit_y.begin() + r);

		//visited[x][y] = true;

		int offset_x[4] = { -1, 1, 0, 0 };
		int offset_y[4] = { 0, 0,-1, 1 };

		int num_caminitos_alrededor = 0;
		std::vector<int> caminitos_x;
		std::vector<int> caminitos_y;
		for (int i = 0; i < 4; ++i)
		{
			int xx = x + offset_x[i];
			int yy = y + offset_y[i];
			if (caminito[xx][yy])
			{
				caminitos_x.push_back(xx);
				caminitos_y.push_back(yy);
				num_caminitos_alrededor++;
			}
			if (!visited[xx][yy] && xx >= start_x && xx <= end_x)
			{
				to_visit_x.push_back(xx);
				to_visit_y.push_back(yy);
				visited[x][y] = true;
			}
		}

		bool make_tile_passable = false;


		if (num_caminitos_alrededor == 0)
		{
			superset[x][y] = x * MAP_SIZE_Y + y;
			make_tile_passable = true;
		}

		if (num_caminitos_alrededor == 1)
		{
			int k1 = superset[caminitos_x[0]][caminitos_y[0]];
			int km = superset[x][y];
			for (int i = 0; i < MAP_SIZE_X; ++i)
			{
				for (int j = 0; j < MAP_SIZE_Y; ++j)
				{
					if (superset[i][j] == km)
					{
						superset[i][j] = k1;
					}
				}
			}
			superset[x][y] = k1;
			make_tile_passable = true;
		}

		if (num_caminitos_alrededor == 2)
		{

			int k1 = superset[caminitos_x[0]][caminitos_y[0]];
			int k2 = superset[caminitos_x[1]][caminitos_y[1]];
			int km = superset[x][y];

			if (k1 != k2)
			{
				make_tile_passable = true;

				for (int i = 0; i < MAP_SIZE_X; ++i)
				{
					for (int j = 0; j < MAP_SIZE_Y; ++j)
					{
						if (superset[i][j] == k2 || superset[i][j] == km)
						{
							superset[i][j] = k1;
						}
					}
				}
			}

		}

		if (num_caminitos_alrededor == 3)
		{

			int k1 = superset[caminitos_x[0]][caminitos_y[0]];
			int k2 = superset[caminitos_x[1]][caminitos_y[1]];
			int k3 = superset[caminitos_x[2]][caminitos_y[2]];
			int km = superset[x][y];

			if (k1 != k2 && k1 != k3 && k2 != k3)
			{
				make_tile_passable = true;

				for (int i = 0; i < MAP_SIZE_X; ++i)
				{
					for (int j = 0; j < MAP_SIZE_Y; ++j)
					{
						if (superset[i][j] == k2 || superset[i][j] == km || superset[i][j] == k1)
						{
							superset[i][j] = k1;
						}
					}
				}
			}

		}

		if (make_tile_passable)
		{
			Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::CUT_GRASS);

			int roll = Roll1d100();
			if (roll < 85)
			{
				Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::FLOWER);
			}
			if (roll < 55)
			{
				Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::GRASS);
			}

			caminito[x][y] = true;
		}
	}


}

void MapGen_GenerateRoom_BushMaze(int w_x, int w_y)
{

	for (int j = 0; j < MAP_SIZE_Y; ++j)
	{
		for (int i = 0; i < MAP_SIZE_X; ++i)
		{
			Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::SUPER_GRASS);
		}
	}
	bool visited[MAP_SIZE_X][MAP_SIZE_Y];

	for (int i = 0; i < MAP_SIZE_X; ++i)
	{
		for (int j = 0; j < MAP_SIZE_Y; ++j)
		{
			visited[i][j] = false;
		}
	}

	for (int i = 0; i < MAP_SIZE_X / 2; ++i)
	{
		for (int j = 0; j < MAP_SIZE_Y; ++j)
		{
			visited[i][j] = false;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int x = i+1;
			int y = j + 1;

			Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::CUT_GRASS);

			if (j < 3)
			{
				int roll = Roll1d100();
				if (roll < 85)
				{
					Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::FLOWER);
				}
				if (roll < 55)
				{
					Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::GRASS);
				}
				visited[1 + i][1 + j] = true;
				//caminito[1 + i][1 + j] = true;
			}

			
		}
	}

	
	

	for (int i = 0; i < MAP_SIZE_X; ++i)
	{
		visited[i][0] = true;
		visited[i][MAP_SIZE_Y - 1] = true;
	}
	for (int j = 0; j < MAP_SIZE_Y; ++j)
	{
		visited[0][j] = true;
		visited[MAP_SIZE_X-1][j] = true;
	}


	int start_x = 0;
	int start_y = 6;

	int mid_x = MAP_SIZE_X / 4;
	int mid_y = MAP_SIZE_Y / 2 + Roll1d100() % (MAP_SIZE_Y / 2 - 3);

	int end_x = MAP_SIZE_X - 3;
	int end_y = 3;


	
	GenerateBushLabyrinth(w_x, w_y, start_x, start_y, mid_x-1, mid_y, visited);


	GenerateBushLabyrinth(w_x, w_y, mid_x, mid_y, end_x+1, end_y, visited);

	

	Tile_SetOnScreenMap(w_x, w_y, end_x-1, end_y-1, TileType::CUT_GRASS);
	Tile_SetOnScreenMap(w_x, w_y, end_x, end_y-1, TileType::SUPER_GRASS);
	Tile_SetOnScreenMap(w_x, w_y, end_x+1, end_y-1, TileType::CUT_GRASS);

	Tile_SetOnScreenMap(w_x, w_y, end_x-1, end_y, TileType::CUT_GRASS);
	Tile_SetOnScreenMap(w_x, w_y, end_x, end_y, TileType::TILE_SPECIAL);
	Tile_SetOnScreenMap(w_x, w_y, end_x+1, end_y, TileType::CUT_GRASS);

	Tile_SetOnScreenMap(w_x, w_y, end_x-1, end_y+1, TileType::CUT_GRASS);
	Tile_SetOnScreenMap(w_x, w_y, end_x, end_y+1, TileType::CUT_GRASS);
	Tile_SetOnScreenMap(w_x, w_y, end_x+1, end_y+1, TileType::CUT_GRASS);

	WorldMap::sword_tx = end_x;
	WorldMap::sword_ty = end_y;

}

void FurnishCaveRoom(int wx, int wy)
{
	for (int j = 0; j < MAP_SIZE_Y; ++j)
	{
		for (int i = 0; i < MAP_SIZE_X; ++i)
		{

			if (Tile_GetOnScreenMap(wx, wy, i, j) != TileType::NONE)
			{
				continue;
			}
			if (j == 0 && i == 0)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_TL_BR);
			}
			else if (j == 0 && i == MAP_SIZE_X - 1)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_TR_BL);
			}
			else if(j == MAP_SIZE_Y - 1 && i == 0)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_TR_BL);
			}
			else if(j == MAP_SIZE_Y - 1 && i == MAP_SIZE_X - 1)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_TL_BR);
			}
			else if (j == MAP_SIZE_Y - 1)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_B);
			}
			else if (i == MAP_SIZE_X- 1)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_R);
			}
			else if (j == 0)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_T);
			}
			else if (i == 0)
			{
				Tile_SetOnScreenMap(wx, wy, i, j, TileType::CAVE_WALL_L);
			}
		}	
	}
}

void GenerateDungeonRoom(int w_x, int w_y, int start_x, int start_y, int end_x, int end_y)
{
	int point_x = 0;
	int point_y = 0;
	for (int n = 0; n < 60; n++)
	{
		int next_w = Roll1d100() % 4 + 2;
		int next_h = Roll1d100() % 4 + 2;

		for (int i = 0; i < next_w; ++i)
		{
			for (int j = 0; j < next_h; ++j)
			{
				int x = point_x + i;
				int y = point_y + j;

				if (x < 1) x = 1;
				if (x > MAP_SIZE_X - 2) x = MAP_SIZE_X - 2;
				if (y < 1) y = 1;
				if (y > MAP_SIZE_Y - 2) y = MAP_SIZE_Y - 2;

				Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::CAVE_FLOOR);
			}
		}

		point_x = Roll1d100() % MAP_SIZE_X;
		point_y = Roll1d100() % MAP_SIZE_Y;
	}

	
	while (!CheckIsArrivableInMap(w_x, w_y, start_x, start_y, end_x, end_y))
	{
		int next_w = Roll1d100() % 3 + 2;
		int next_h = Roll1d100() % 3 + 2;

		for (int i = 0; i < next_w; ++i)
		{
			for (int j = 0; j < next_h; ++j)
			{
				int x = point_x + i;
				int y = point_y + j;

				if (x < 1) x = 1;
				if (x > MAP_SIZE_X - 2) x = MAP_SIZE_X - 2;
				if (y < 1) y = 1;
				if (y > MAP_SIZE_Y - 2) y = MAP_SIZE_Y - 2;

				Tile_SetOnScreenMap(w_x, w_y, x, y, TileType::CAVE_FLOOR);
			}
		}

		point_x = Roll1d100() % MAP_SIZE_X;
		point_y = Roll1d100() % MAP_SIZE_Y;
	}

	//SetTileOnWorldMap(end_x, end_y, TileType::TILE_SPECIAL);

	FurnishCaveRoom(w_x, w_y);

	for (int i = 0; i < 3; ++i)
	{
		int tx = w_x*TILE_SIZE*MAP_SIZE_X + (Roll1d100() % MAP_SIZE_X) * TILE_SIZE;
		int ty = w_y*TILE_SIZE*MAP_SIZE_Y + (Roll1d100() % MAP_SIZE_Y) * TILE_SIZE;


		EntS::SpawnEntity(EntS::EntityType::BAT, tx, ty);
	}
}

void GenerateWorld1Map()
{
	const int W1_SIZE_X = 3;
	const int W1_SIZE_Y = 4;
	const int W1_SIZE = W1_SIZE_X * W1_SIZE_Y;
	bool world1_connections[W1_SIZE_X][W1_SIZE_Y][4];
	bool visited[W1_SIZE_X][W1_SIZE_Y];
	for (int i = 0; i < W1_SIZE_X; ++i)
	{
		for (int j = 0; j < W1_SIZE_Y; ++j)
		{
			visited[i][j] = false;

			for (int d = 0; d < 4; ++d)
			{
				world1_connections[i][j][d] = false;
			}
		}
	}

	
	WorldMap::wx_sword_start = Roll1d100() % 2;
	WorldMap::wy_sword_start = Roll1d100() % 3;
	
	int r_start = WorldMap::wy_sword_start * W1_SIZE_X + WorldMap::wx_sword_start;

	visited[WorldMap::wx_sword_start][WorldMap::wy_sword_start] = true;
	std::vector<int> connected;
	connected.push_back(r_start);

	const int dx[4] = { 0, 0, -1, 1 };
	const int dy[4] = { -1, 1,  0, 0 };

	//Generate World 1 Passages
	for (int i = 0; i < W1_SIZE-1; ++i)
	{
		int r = connected[Roll1d100() % connected.size()];
		int rd = Roll1d100() % 4;
		int from_wx = r % W1_SIZE_X;
		int from_wy = r / W1_SIZE_X;
		int to_wx = from_wx + dx[rd];
		int to_wy = from_wy + dy[rd];

		int r_new = to_wy * W1_SIZE_X + to_wx;

		while ((to_wx < 0 || to_wx >= W1_SIZE_X || to_wy < 0 || to_wy >= W1_SIZE_Y) ||
			visited[to_wx][to_wy])
		{
			r = connected[Roll1d100() % connected.size()];
			rd = Roll1d100() % 4;
			from_wx = r % W1_SIZE_X;
			from_wy = r / W1_SIZE_X;
			to_wx = r % W1_SIZE_X + dx[rd];
			to_wy = r / W1_SIZE_X + dy[rd];
			r_new = to_wy * W1_SIZE_X + to_wx;
		}

		world1_connections[from_wx][from_wy][rd] = true;
		world1_connections[to_wx][to_wy][ReverseDir((Direction)rd)] = true;
		connected.push_back(r_new);
		visited[to_wx][to_wy] = true;
	}

	/*
	//World1-River passages
	for (int i = 0; i < (W1_SIZE_Y-1); ++i)
	{
		int r = Roll1d100() % W1_SIZE_Y;;
		int from_wx = 1;
		int from_wy = r;
		int to_wx = 2;
		int to_wy = from_wy;
		world1_connections[from_wx][from_wy][Direction::RIGHT] = true;
		world1_connections[to_wx][to_wy][Direction::LEFT] = true;
	}
	*/

	//Full relleno y rebordes
	for (int w_y = 0; w_y < WORLD_MAP_SIZE_Y; w_y++)
	{
		for (int w_x = 0; w_x < WORLD_MAP_SIZE_X; w_x++)
		{
			if (w_x == WorldMap::wx_sword_start && w_y == WorldMap::wy_sword_start)
			{
				MapGen_GenerateRoom_BushMaze(w_x, w_y);
			}
			else
			{
				GenerateForestRoom(w_x, w_y);
			}

			bool* apply_openwall = &world1_connections[w_x][w_y][0];

			//Apply Rebordesitos
			for (int j = 0; j < MAP_SIZE_Y; ++j)
			{
				for (int i = 0; i < MAP_SIZE_X; ++i)
				{
					//PARTE DE ARRIBA
					if (
						(j%MAP_SIZE_Y == 0) && (w_x != 2 || w_y == 0))
					{
						if (i % 2 == 1) Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_BL);
						else Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_BR);

						if (apply_openwall[Direction::UP] && (w_y > 0) && (i%MAP_SIZE_X == MAP_SIZE_X / 2 || i % MAP_SIZE_X == (MAP_SIZE_X / 2 - 1)))
						{
							Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::CUT_GRASS);
							Tile_SetOnScreenMap(w_x, w_y, i, j+1, TileType::SUPER_GRASS);
						}
					}

					//PARTE DE IZQUIERDA
					else if (
						i%MAP_SIZE_X == 0)
					{
						if (j % 2 == 0) Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_BR);
						else Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_TR);

						if (apply_openwall[Direction::LEFT] && (w_x > 0) && (j%MAP_SIZE_X == MAP_SIZE_Y / 2 || j % MAP_SIZE_X == (MAP_SIZE_Y / 2 + 1)))
						{
							Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::CUT_GRASS);
							Tile_SetOnScreenMap(w_x, w_y, i+1, j, TileType::SUPER_GRASS);
						}
					}

					//PARTE DE ABAJO
					else if (
						(j%MAP_SIZE_Y == MAP_SIZE_Y - 1 && (w_x != 2 || w_y == WORLD_MAP_SIZE_Y-1)))
					{
						if (i % 2 == 0) Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_TR);
						else Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_TL);

						if (apply_openwall[Direction::DOWN] && (w_y < WORLD_MAP_SIZE_Y - 1) && (i == MAP_SIZE_X / 2 || i == (MAP_SIZE_X / 2 - 1)))
						{
							Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::CUT_GRASS);
							Tile_SetOnScreenMap(w_x, w_y, i, j - 1, TileType::SUPER_GRASS);
						}
					}

					//PARTE DERECHA
					else if (
						 (i%MAP_SIZE_X == MAP_SIZE_X - 1))
					{
						if (j % 2 == 1) Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_TL);
						else Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::TREE_BL);

						if (apply_openwall[Direction::RIGHT] && (w_x < WORLD_MAP_SIZE_X - 1) && (j%MAP_SIZE_X == MAP_SIZE_Y / 2 || j % MAP_SIZE_X == (MAP_SIZE_Y / 2 + 1)))
						{
							Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::CUT_GRASS);
							Tile_SetOnScreenMap(w_x, w_y, i-1, j, TileType::SUPER_GRASS);
						}
					}
				}
			}	
		}

	}
		
	//Generate River
	int start_river_x = 2*MAP_SIZE_X + MAP_SIZE_X/2 -2;
	int offset_river_x = 0;
	int len_river_x = 6;
	int next_river_turn_x = 2 + Roll1d100()%2;
	for (int wy = 0; wy < WORLD_MAP_SIZE_Y*MAP_SIZE_Y; wy++)
	{
		for (int wx = start_river_x+offset_river_x; wx < start_river_x+offset_river_x + len_river_x; wx++)
		{

			Tile_SetOnWorldMap(wx, wy, TileType::WATER);

		}

		next_river_turn_x--;
		if (next_river_turn_x == 0)
		{
			int roll = Roll1d100();
			if (roll < 40)
			{
				offset_river_x--;
			}
			if (roll > 60)
			{
				offset_river_x++;
			}

			next_river_turn_x = 2;
		}
	}
	//Laguito final
	for (int wy = 0; wy < MAP_SIZE_Y*1/3 +2; wy++)
	{
		int l = 0;
		int r = 0;
		if (wy > 0)
		{
			int l = Roll1d100() % 2;
			int r = Roll1d100() % 2;
		}
		for (int wx = (2 * MAP_SIZE_X) + wy * 3 / 2 - l; wx < (3 * MAP_SIZE_X)  - wy * 3 / 2 +r; wx++)
		{
			Tile_SetOnWorldMap(wx, MAP_SIZE_Y*(WORLD_MAP_SIZE_Y - 1) + MAP_SIZE_Y - wy, TileType::WATER);
		}
	}


	//Relleno arboles
	for (int w_y = 0; w_y < WORLD_MAP_SIZE_Y; w_y++)
	{
		for (int w_x = 0; w_x < WORLD_MAP_SIZE_X; w_x++)
		{
			for (int j = 1; j < MAP_SIZE_Y - 3; ++j)
			{
				for (int i = 1; i < MAP_SIZE_X - 3; ++i)
				{
					if (Tile_GetOnScreenMap(w_x, w_y, i, j) == TileType::TREE_TL)
					{
						TileType t2 = Tile_GetOnScreenMap(w_x, w_y, i + 1, j);
						TileType t3 = Tile_GetOnScreenMap(w_x, w_y, i, j + 1);
						TileType t4 = Tile_GetOnScreenMap(w_x, w_y, i + 1, j + 1);

						if (TileTreeCanBePlaced(t2) && TileTreeCanBePlaced(t3) && TileTreeCanBePlaced(t4))
						{
							Tile_SetOnScreenMap(w_x, w_y, i + 1, j, TileType::TREE_TR);
							Tile_SetOnScreenMap(w_x, w_y, i, j + 1, TileType::TREE_BL);
							Tile_SetOnScreenMap(w_x, w_y, i + 1, j + 1, TileType::TREE_BR);
						}
						else
						{
							Tile_SetOnScreenMap(w_x, w_y, i, j, TileType::GRASS);
						}
					}
				}
			}
		}
	}
}


void PopulateWorld1Map()
{
	EntS::ResetEntities();

	EntS::id_player = EntS::SpawnEntity(EntS::EntityType::LINK, 
		WorldMap::wx_sword_start*MAP_SIZE_X*TILE_SIZE + TILE_SIZE * 3, 
		WorldMap::wy_sword_start*MAP_SIZE_Y*TILE_SIZE + TILE_SIZE * 3);
	//EntitySystem::SpawnEntity(EntitySystem::EntityType::FADA, 1000, 1000);
	//EntitySystem::SpawnEntity(EntitySystem::EntityType::BLOB, TILE_SIZE * 2, TILE_SIZE * 2);

	

	for (int w_y = 0; w_y < WORLD_MAP_SIZE_Y; w_y++)
	{
		for (int w_x = 0; w_x < WORLD_MAP_SIZE_X; w_x++)
		{
			if (w_x == WorldMap::wx_sword_start && w_y == WorldMap::wy_sword_start) continue;

			for (int i = 0; i < MAP_SIZE_X; ++i)
			{
				for (int j = 0; j < MAP_SIZE_Y; ++j)
				{
					if (Tile_GetOnScreenMap(w_x, w_y, i, j) == TileType::GRASS)
					{
						if (Roll1d100() == 1)
						{
							EntS::SpawnEntity(EntS::EntityType::BLOB, w_x*TILE_SIZE*MAP_SIZE_X + i * TILE_SIZE, w_y*TILE_SIZE*MAP_SIZE_Y + j * TILE_SIZE);
						}
						//EntitySystem::SpawnEntity(EntitySystem::EntityType::GRASS, w_x*TILE_SIZE*MAP_SIZE_X + i*TILE_SIZE, w_y*TILE_SIZE*MAP_SIZE_Y + j*TILE_SIZE);
					}
				}
			}
		}
	}
		
	//EntitySystem::SpawnEntity(EntitySystem::EntityType::BAT, 10 * TILE_SIZE, 10 * TILE_SIZE);

	//EntitySystem::SpawnEntity(EntitySystem::EntityType::SPARRING, 10 * TILE_SIZE, 10 * TILE_SIZE);
}

void SelectTileSprite(sf::Sprite& spr_tile, TileType type, int timer_variant)
{

	if (type == TileType::FIELD_TL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 0 * 16, 16, 16));
	}
	if (type == TileType::FIELD_T)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 0 * 16, 16, 16));
	}
	if (type == TileType::FIELD_TR)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 0 * 16, 16, 16));
	}
	if (type == TileType::FIELD_L)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 1 * 16, 16, 16));
	}
	if (type == TileType::FIELD)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 1 * 16, 16, 16));
	}
	if (type == TileType::FIELD_R)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 1 * 16, 16, 16));
	}
	if (type == TileType::FIELD_BL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 2 * 16, 16, 16));
	}
	if (type == TileType::FIELD_B)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 2 * 16, 16, 16));
	}
	if (type == TileType::FIELD_BR)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 2 * 16, 16, 16));
	}

	if (type == TileType::CUT_GRASS)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 4 * 16, 16, 16));
	}
	if (type == TileType::GRASS)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 4 * 16, 16, 16));
	}
	if (type == TileType::SUPER_GRASS)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 4 * 16, 16, 16));
	}
	if (type == TileType::ROCK)
	{
		spr_tile.setTextureRect(sf::IntRect(3 * 16, 4 * 16, 16, 16));
	}
	if (type == TileType::FLOWER)
	{
		int frame = (timer_variant % 2000) / 500;
		spr_tile.setTextureRect(sf::IntRect(frame * 16, 3 * 16, 16, 16));
	}
	if (type == TileType::WATER)
	{
		int frame = (timer_variant % 2000) / 500;
		spr_tile.setTextureRect(sf::IntRect(frame * 16, 5 * 16, 16, 16));
	}
	if (type == TileType::TREE_TL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 6 * 16, 16, 16));
	}
	if (type == TileType::TREE_TR)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 6 * 16, 16, 16));
	}
	if (type == TileType::TREE_BL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 7 * 16, 16, 16));
	}
	if (type == TileType::TREE_BR)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 7 * 16, 16, 16));
	}

	/////////////////ROOF///////////////////////

	if (type == TileType::ROOF_TL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 8 * 16, 16, 16));
	}
	if (type == TileType::ROOF_T)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 8 * 16, 16, 16));
	}
	if (type == TileType::ROOF_TR)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 8 * 16, 16, 16));
	}
	if (type == TileType::ROOF_BL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 9 * 16, 16, 16));
	}
	if (type == TileType::ROOF_B)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 9 * 16, 16, 16));
	}
	if (type == TileType::ROOF_BR)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 9 * 16, 16, 16));
	}


	//////////// HOUSE ///////////
	if (type == TileType::HOUSE_WINDOW_STONE)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 10 * 16, 16, 16));
	}
	if (type == TileType::HOUSE_WINDOW_WOOD)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 10 * 16, 16, 16));
	}
	if (type == TileType::HOUSE_DOOR_STONE)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 10 * 16, 16, 16));
	}
	if (type == TileType::HOUSE_DOOR_WOOD)
	{
		spr_tile.setTextureRect(sf::IntRect(3 * 16, 10 * 16, 16, 16));
	}

	if (type == TileType::HOUSE_INSIDE_FLOOR)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 12 * 16, 16, 16));
	}

	if (type == TileType::HOUSE_INSIDE_DOOR_LEFT)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 14 * 16, 16, 16));
	}
	if (type == TileType::HOUSE_INSIDE_DOOR_HOLE)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 14 * 16, 16, 16));
	}
	if (type == TileType::HOUSE_INSIDE_DOOR_RIGHT)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 14 * 16, 16, 16));
	}

	//////////// CAVE ///////////
	if (type == TileType::CAVE_TL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 15 * 16, 16, 16));
	}
	if (type == TileType::CAVE_T)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 15 * 16, 16, 16));
	}
	if (type == TileType::CAVE_TR)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 15 * 16, 16, 16));
	}
	if (type == TileType::CAVE_BL)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 16 * 16, 16, 16));
	}

	// CAVE WALLS
	if (type == TileType::CAVE_WALL_TL)
	{
		spr_tile.setTextureRect(sf::IntRect(3 * 16, 2 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_T)
	{
		spr_tile.setTextureRect(sf::IntRect(4 * 16, 2 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_TR)
	{
		spr_tile.setTextureRect(sf::IntRect(5 * 16, 2 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_L)
	{
		spr_tile.setTextureRect(sf::IntRect(5 * 16, 1 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_R)
	{
		spr_tile.setTextureRect(sf::IntRect(3 * 16, 1 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_BL)
	{
		spr_tile.setTextureRect(sf::IntRect(3 * 16, 0 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_B)
	{
		spr_tile.setTextureRect(sf::IntRect(4 * 16, 0 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_BR)
	{
		spr_tile.setTextureRect(sf::IntRect(5 * 16, 0 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_TL_BR)
	{
		spr_tile.setTextureRect(sf::IntRect(6 * 16, 0 * 16, 16, 16));
	}
	if (type == TileType::CAVE_WALL_TR_BL)
	{
		spr_tile.setTextureRect(sf::IntRect(6 * 16, 1 * 16, 16, 16));

	}

	//CAVE ASSETS
	if (type == TileType::CAVE_DOOR)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 16 * 16, 16, 16));
	}
	if (type == TileType::CAVE_DOOR_LOCKED)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 17 * 16, 16, 16));
	}

	if (type == TileType::PUZZLE_BUTTON)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 18 * 16, 16, 16));
	}
	if (type == TileType::PUZZLE_BUTTON_PRESSED)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 18 * 16, 16, 16));
	}

	if (type == TileType::CAVE_BR)
	{
		spr_tile.setTextureRect(sf::IntRect(2 * 16, 16 * 16, 16, 16));
	}

	if (type == TileType::CAVE_FLOOR)
	{
		spr_tile.setTextureRect(sf::IntRect(0 * 16, 17 * 16, 16, 16));
	}
	if (type == TileType::CAVE_STAIRS)
	{
		spr_tile.setTextureRect(sf::IntRect(1 * 16, 17 * 16, 16, 16));
	}

	if (type == TileType::TILE_SPECIAL)
	{
		spr_tile.setTextureRect(sf::IntRect(3 * 16, 11 * 16, 16, 16));
	}
}

void DrawMap(int world_x, int world_y, sf::RenderWindow& wnd, sf::Sprite spr_tile, int time_general)
{
	spr_tile.setScale(2, 2);

	sf::View cam = wnd.getView();

	int tx_left = (world_x -1) * MAP_SIZE_X;
	int tx_right = (world_x +2) * MAP_SIZE_X;
	int ty_up = (world_y -1) * MAP_SIZE_Y;
	int ty_down = (world_y + 2) * MAP_SIZE_Y;

#if _DEBUG
	if (free_cam_view_on)
	{
		tx_left = free_cam_x/32 - MAP_SIZE_X * 2;
		tx_right = tx_left + MAP_SIZE_X * 3;

		ty_up = free_cam_y / 32 - MAP_SIZE_Y * 2;
		ty_down = ty_up + MAP_SIZE_Y * 3;
	}
#endif

	for (int j = ty_up; j < ty_down; ++j)
	{
		for (int i = tx_left; i < tx_right; ++i)
		{
			if (!IsTileInBounds(i, j)) continue;

			TileType type = Tile_GetOnWorldMap(i, j);

			if (type == TileType::NONE) continue;

			spr_tile.setPosition(i * 32.0f, j * 32.0f);

			SelectTileSprite(spr_tile, type, time_general);

			spr_tile.move(0, MARGIN_TOP_GUI);
			wnd.draw(spr_tile);

#if _DEBUG
			/*
			static sf::RectangleShape hitbox;
			hitbox.setPosition(spr_tile.getPosition());
			hitbox.setSize(sf::Vector2f(32, 32));
			hitbox.setOutlineColor(sf::Color::Red);
			hitbox.setOutlineThickness(1);
			hitbox.setFillColor(sf::Color::Transparent);
			if (!IsTilePassable(i, j))
			{
				wnd.draw(hitbox);
			}
			*/
#endif
		}
	}

}

void DrawImguiCosas()
{

	ImGui::Begin("Debug");
	/*
	for (int i = 0; i < 4; ++i)
	{
		if (EntitySystem::ent_type[i] == EntitySystem::NONE) continue;

		std::string title = "Entity " + std::to_string(i);
		if (ImGui::CollapsingHeader(title.c_str()))
		{
			//std::string anim = "Anim " + std::to_string(i);
			//if (ImGui::CollapsingHeader(anim.c_str()))
			{
				std::string info = "Timer - " + std::to_string(EntitySystem::anim[i].anim_timer);
				ImGui::Text(info.c_str());
			}
			
		}
	}
	*/

	/*
	const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO", "PPPP", "QQQQQQQQQQ", "RRR", "SSSS" };
	static const char* current_item = NULL;

	if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < EntitySystem::EntityType::COUNT; n++)
		{
			bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(items[n], is_selected))
				current_item = items[n];
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				
		}
		ImGui::EndCombo();
	}
	*/
	if (ImGui::CollapsingHeader("Cheats"))
	{

		if (ImGui::Button("+1 HP"))
		{
			EntS::ent_hp[EntS::id_player]++;
		}
		if (ImGui::Button("Spawn Blob"))
		{
			EntS::SpawnEntity(EntS::EntityType::BLOB, EntS::pos_x[EntS::id_player] + TILE_SIZE, EntS::pos_y[EntS::id_player] + TILE_SIZE);
		}
		if (ImGui::Button("Spawn Bat"))
		{
			EntS::SpawnEntity(EntS::EntityType::BAT, EntS::pos_x[EntS::id_player] + TILE_SIZE, EntS::pos_y[EntS::id_player] + TILE_SIZE);
		}
		if (ImGui::Button("Get Sword"))
		{
			PlayerInfo::sword_unlocked = true;
		}
		if (ImGui::Button("Get Key"))
		{
			PlayerInfo::has_key = true;
		}
		if (ImGui::Button("Get 2nd Attack"))
		{
			PlayerInfo::attack2_unlocked = true;
		}
	}
	ImGui::End();
}


sf::Sprite spr_tile;
sf::Sprite sprite;


void LoadGame(sf::RenderWindow& window)
{
	tex_tileset.loadFromFile("data/tileset.png");
	tex_mex.loadFromFile("data/spritesheet.png");
	font.loadFromFile("data/PressStart2P.ttf");

	spr_tile.setTexture(tex_tileset);

	sprite.setTexture(tex_mex);
	sprite.setTextureRect(sf::IntRect(16, 16, 16, 16));
	
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	input_state.RemapInput();
}



int cave_room_wx[5];
int cave_room_wy[5];
Direction cave_room_next_dir[5];
void GenerateCaveRoomConnections()
{
	int dx[4] = {  0, 0, -1, 1};
	int dy[4] = { -1, 1,  0, 0};

	bool visited[5][5];
	for (int i = 0; i < 25; ++i)
	{
		visited[i / 5][i % 5] = false;
	}
	
	for (int i = 1; i < 5; ++i)
	{
		int x = cave_room_wx[i-1];
		int y = cave_room_wy[i-1];
		visited[x][y] = true;

		int r = Roll1d100() % 4;
		int next_x = x + dx[r];
		int next_y = y + dy[r];

		int rooms = 0;
		while ((next_x < 0 || next_x > 2 || next_y < 0 && next_y > 3) ||
				visited[next_x][next_y])
		{
			r = Roll1d100() % 4;
			next_x = x + dx[r];
			next_y = y + dy[r];
			rooms++;
			if (rooms >= 4)
			{
				cave_room_wx[4] = -1;
				return;
			}
		}
		cave_room_next_dir[i - 1] = (Direction)r;

		cave_room_wx[i] = next_x;
		cave_room_wy[i] = next_y;
	}

}

void GenerateShop(int wx, int wy)
{
	int shop_tx = 2 - Roll1d100() % (MAP_SIZE_X - 4);
	int shop_ty = 2 - Roll1d100() % (MAP_SIZE_Y - 4);

	//...

}

void ResetGameMap()
{
	for (int w_y = 0; w_y < WORLD_MAP_SIZE_Y; w_y++)
	{
		for (int w_x = 0; w_x < WORLD_MAP_SIZE_X; w_x++)
		{
			//Apply Rebordesitos
			for (int j = 0; j < MAP_SIZE_Y; ++j)
			{
				for (int i = 0; i < MAP_SIZE_X; ++i)
				{
					world_map[w_y*MAP_SIZE_Y + j][w_x*MAP_SIZE_X + i].ResetTile();
				}
			}
		}
	}
}

void GenerateGameMap()
{
	GenerateWorld1Map();
	PopulateWorld1Map();

	//Sword
	EntS::SpawnEntity(EntS::EntityType::TRAINER_ACTIVATOR_SWORD, 
		WorldMap::wx_sword_start*MAP_SIZE_X*TILE_SIZE + WorldMap::sword_tx*TILE_SIZE, 
		WorldMap::wy_sword_start*MAP_SIZE_Y*TILE_SIZE + WorldMap::sword_ty*TILE_SIZE);


	//Dojo
	int dojo_interior_tx = 1 * WORLD_MAP_SIZE_X * MAP_SIZE_X + 1 * MAP_SIZE_X / 3;
	int dojo_interior_ty = 0 * WORLD_MAP_SIZE_Y * MAP_SIZE_Y + 1 * MAP_SIZE_Y / 3;
	GenerateDojo(3*MAP_SIZE_X -8, 2, dojo_interior_tx, dojo_interior_ty);


	int shop_wx = 1;
	int shop_wy = 1;
	GenerateShop(shop_wx, shop_wy);

	do
	{
		WorldMap::wx_cave_room_entrance = Roll1d100() % 2;
		WorldMap::wy_cave_room_entrance = Roll1d100() % 3;
	} 
	while (WorldMap::wx_cave_room_entrance == WorldMap::wx_sword_start &&
		WorldMap::wy_cave_room_entrance == WorldMap::wy_sword_start);
	

	cave_room_wx[0] = WorldMap::wx_cave_room_entrance;
	cave_room_wy[0] = WorldMap::wy_cave_room_entrance;

	cave_room_wx[4] = -1;
	while (cave_room_wx[4] != 2)
	{
		GenerateCaveRoomConnections();
	}

	//CaveKeyPuzzle
	int cavekey_pzl_wx = Roll1d100() % 2;
	int cavekey_pzl_wy = Roll1d100() % 4;
	while ( 
			((cavekey_pzl_wx == WorldMap::wx_sword_start) && (cavekey_pzl_wy == WorldMap::wy_sword_start)) ||
			(cavekey_pzl_wx == cave_room_wx[0] && cavekey_pzl_wy == cave_room_wy[0])
		)
	{
		cavekey_pzl_wx = Roll1d100() % 2;
		cavekey_pzl_wy = Roll1d100() % 4;
	}

	int key_tx = MAP_SIZE_X/2;
	int key_ty = MAP_SIZE_Y/2;

	int key_x = ((cavekey_pzl_wx * MAP_SIZE_X) + (key_tx))*TILE_SIZE;
	int key_y = ((cavekey_pzl_wy * MAP_SIZE_Y) + (key_ty))*TILE_SIZE;

	int id_pzl_cavekey = EntS::SpawnEntity(EntS::EntityType::PUZZLE_CAVEKEY, key_x, key_y);
	Tile_SetOnWorldMap(key_x/TILE_SIZE, key_y / TILE_SIZE, TileType::TILE_SPECIAL);


	{
		int x = ((cavekey_pzl_wx * MAP_SIZE_X + 2) + (Roll1d100() % (MAP_SIZE_X / 2 - 4)))*TILE_SIZE;
		int y = ((cavekey_pzl_wy * MAP_SIZE_Y + 2) + (Roll1d100() % (MAP_SIZE_Y / 2 - 4)))*TILE_SIZE;
		EntS::SpawnEntity(EntS::EntityType::PUZZLE_CAVEKEY_BUTTON, x, y, id_pzl_cavekey);
		Tile_SetOnWorldMap(x / TILE_SIZE, y / TILE_SIZE, TileType::PUZZLE_BUTTON);
	}
	{
		int x = ((cavekey_pzl_wx * MAP_SIZE_X + MAP_SIZE_X / 2 + 2) + (Roll1d100() % (MAP_SIZE_X / 2 - 4)))*TILE_SIZE;
		int y = ((cavekey_pzl_wy * MAP_SIZE_Y + 2) + (Roll1d100() % (MAP_SIZE_Y / 2 - 4)))*TILE_SIZE;
		EntS::SpawnEntity(EntS::EntityType::PUZZLE_CAVEKEY_BUTTON, x, y, id_pzl_cavekey);
		Tile_SetOnWorldMap(x / TILE_SIZE, y / TILE_SIZE, TileType::PUZZLE_BUTTON);
	}
	{
		int x = ((cavekey_pzl_wx * MAP_SIZE_X + MAP_SIZE_X / 2 + 2) + (Roll1d100() % (MAP_SIZE_X / 2 - 4)))*TILE_SIZE;
		int y = ((cavekey_pzl_wy * MAP_SIZE_Y + MAP_SIZE_Y / 2 + 2) + (Roll1d100() % (MAP_SIZE_Y / 2 - 4)))*TILE_SIZE;
		EntS::SpawnEntity(EntS::EntityType::PUZZLE_CAVEKEY_BUTTON, x, y, id_pzl_cavekey);
		Tile_SetOnWorldMap(x / TILE_SIZE, y / TILE_SIZE, TileType::PUZZLE_BUTTON);
	}
	{
		int x = ((cavekey_pzl_wx * MAP_SIZE_X + 2) + (Roll1d100() % (MAP_SIZE_X / 2 - 4)))*TILE_SIZE;
		int y = ((cavekey_pzl_wy * MAP_SIZE_Y + MAP_SIZE_Y / 2 + 2) + (Roll1d100() % (MAP_SIZE_Y / 2 - 4)))*TILE_SIZE;
		EntS::SpawnEntity(EntS::EntityType::PUZZLE_CAVEKEY_BUTTON, x, y, id_pzl_cavekey);
		Tile_SetOnWorldMap(x / TILE_SIZE, y / TILE_SIZE, TileType::PUZZLE_BUTTON);
	}

	//Cave
	int cave_interior_wx[4] = 
	{ 
		0 * WORLD_MAP_SIZE_X + cave_room_wx[0],
		0 * WORLD_MAP_SIZE_X + cave_room_wx[1],
		0 * WORLD_MAP_SIZE_X + cave_room_wx[2],
		0 * WORLD_MAP_SIZE_X + cave_room_wx[3]
	};
	int cave_interior_wy[4] = 
	{ 
		2 * WORLD_MAP_SIZE_Y + cave_room_wy[0],
		2 * WORLD_MAP_SIZE_Y + cave_room_wy[1],
		2 * WORLD_MAP_SIZE_Y + cave_room_wy[2],
		2 * WORLD_MAP_SIZE_Y + cave_room_wy[3]
	};
	int cave_entrance_wx = cave_room_wx[0];
	int cave_entrance_wy = cave_room_wy[0];

	int cave_entrance_tx = cave_entrance_wx*MAP_SIZE_X + 2 + Roll1d100()%(MAP_SIZE_X - 4);
	int cave_entrance_ty = cave_entrance_wy*MAP_SIZE_Y + 2 + Roll1d100()%(MAP_SIZE_Y - 5);

	GenerateCaveEntrance(cave_entrance_tx, cave_entrance_ty);
	

	for (int i = 0; i < 4; ++i)
	{
		for (int yy = 0; yy < MAP_SIZE_Y; ++yy)
		{
			for (int xx = 0; xx < MAP_SIZE_X; ++xx)
			{
				Tile_SetOnScreenMap(cave_interior_wx[i], cave_interior_wy[i], xx, yy, TileType::NONE);
			}
		}
		
		int interior_entrance_x = -1;
		int interior_entrance_y = -1;

		int end_x = MAP_SIZE_X - 2;
		int end_y = MAP_SIZE_Y / 2;

		int cave_interior_cornerupleft_tx = cave_interior_wx[i] * MAP_SIZE_X;
		int cave_interior_cornerupleft_ty = cave_interior_wy[i] * MAP_SIZE_Y;

		if (i == 0)
		{
			interior_entrance_x = MAP_SIZE_X/2;
			interior_entrance_y = MAP_SIZE_Y/2;
		}
		if (i == 3)
		{
			end_x = MAP_SIZE_X * 3 / 4 + Roll1d100() % (MAP_SIZE_X * 1 / 5);
			end_y = MAP_SIZE_Y * 1 / 3 + Roll1d100() % (MAP_SIZE_Y * 3 / 4);
		}
		if (i >= 1)
		{
			Direction dir_prev = cave_room_next_dir[i-1];
			if (dir_prev == Direction::UP)
			{
				interior_entrance_x = MAP_SIZE_X / 2;
				interior_entrance_y = MAP_SIZE_Y - 2;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x,
					cave_interior_cornerupleft_ty + interior_entrance_y +1,
					TileType::CAVE_FLOOR);
				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x,
					cave_interior_cornerupleft_ty + interior_entrance_y,
					TileType::CAVE_FLOOR);
			}
			if (dir_prev == Direction::DOWN)
			{
				interior_entrance_x = MAP_SIZE_X / 2;
				interior_entrance_y = 1;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x,
					cave_interior_cornerupleft_ty + interior_entrance_y -1,
					TileType::CAVE_FLOOR);
				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x,
					cave_interior_cornerupleft_ty + interior_entrance_y,
					TileType::CAVE_FLOOR);
			}
			if (dir_prev == Direction::LEFT)
			{
				interior_entrance_x = MAP_SIZE_X - 2;
				interior_entrance_y = MAP_SIZE_Y / 2;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x + 1,
					cave_interior_cornerupleft_ty + interior_entrance_y,
					TileType::CAVE_FLOOR);
				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x,
					cave_interior_cornerupleft_ty + interior_entrance_y,
					TileType::CAVE_FLOOR);
			}
			if (dir_prev == Direction::RIGHT)
			{
				interior_entrance_x = 1;
				interior_entrance_y = MAP_SIZE_Y / 2;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x - 1,
					cave_interior_cornerupleft_ty + interior_entrance_y,
					TileType::CAVE_FLOOR);
				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + interior_entrance_x,
					cave_interior_cornerupleft_ty + interior_entrance_y,
					TileType::CAVE_FLOOR);
			}
		}
		{
			Direction dir = cave_room_next_dir[i];
			if (dir == Direction::UP)
			{
				end_x = MAP_SIZE_X / 2;
				end_y = 1;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + end_x,
					cave_interior_cornerupleft_ty + end_y - 1,
					TileType::CAVE_FLOOR);
			}
			if (dir == Direction::DOWN)
			{
				end_x = MAP_SIZE_X / 2;
				end_y = MAP_SIZE_Y - 2;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + end_x,
					cave_interior_cornerupleft_ty + end_y + 1,
					TileType::CAVE_FLOOR);
			}
			if (dir == Direction::LEFT)
			{
				end_x = 1;
				end_y = MAP_SIZE_Y / 2;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + end_x - 1,
					cave_interior_cornerupleft_ty + end_y,
					TileType::CAVE_FLOOR);
			}
			if (dir == Direction::RIGHT)
			{
				end_x = MAP_SIZE_X - 2;
				end_y = MAP_SIZE_Y / 2;

				Tile_SetOnWorldMap(
					cave_interior_cornerupleft_tx + end_x + 1,
					cave_interior_cornerupleft_ty + end_y,
					TileType::CAVE_FLOOR);
			}
		}

		GenerateDungeonRoom(cave_interior_wx[i], cave_interior_wy[i], interior_entrance_x, interior_entrance_y, end_x, end_y);

		if (i == 0)
		{
			SetTeleportLink(cave_entrance_tx + 1, cave_entrance_ty + 1, cave_interior_cornerupleft_tx + interior_entrance_x, cave_interior_cornerupleft_ty + interior_entrance_y);

			SetTeleportLink(cave_interior_cornerupleft_tx + interior_entrance_x, cave_interior_cornerupleft_ty + interior_entrance_y - 1, cave_entrance_tx + 1, cave_entrance_ty + 2);

			int stairs_tx = cave_interior_cornerupleft_tx + interior_entrance_x;
			int stairs_ty = cave_interior_cornerupleft_ty + interior_entrance_y - 1;
			Tile_SetOnWorldMap(stairs_tx, stairs_ty, TileType::CAVE_STAIRS);
			Tile_SetOnWorldMap(stairs_tx+1, stairs_ty, TileType::CAVE_FLOOR);
			Tile_SetOnWorldMap(stairs_tx-1, stairs_ty, TileType::CAVE_FLOOR);
			Tile_SetOnWorldMap(stairs_tx, stairs_ty+1, TileType::CAVE_FLOOR);
			Tile_SetOnWorldMap(stairs_tx, stairs_ty-1, TileType::CAVE_FLOOR);
		}

		if (i == 3)
		{
			//SetTeleportLink(cave_entrance_tx + 1, cave_entrance_ty + 1, cave_interior_cornerupleft_tx + interior_entrance_x, cave_interior_cornerupleft_ty + interior_entrance_y);

			SetTeleportLink(cave_interior_cornerupleft_tx + end_x, cave_interior_cornerupleft_ty + end_y,
				(cave_interior_wx[i]%WORLD_MAP_SIZE_X)*MAP_SIZE_X + end_x, (cave_interior_wx[i] % WORLD_MAP_SIZE_Y)*MAP_SIZE_Y + end_y);
			Tile_SetOnWorldMap(cave_interior_cornerupleft_tx + end_x, cave_interior_cornerupleft_ty + end_y, TileType::CAVE_STAIRS);
		}
	}
	
}


enum CameraState
{
	CAMERA_GAME,
	MAP_TRANSITION_UP,
	MAP_TRANSITION_DOWN,
	MAP_TRANSITION_LEFT,
	MAP_TRANSITION_RIGHT,
	HOUSE_TRANSITION
};
CameraState cam_state = CAMERA_GAME;
int cam_timer = 0;
int cam_transition_final_tx = 0;
int cam_transition_final_ty = 0;
int cam_current_worldmap_x = 0;
int cam_current_worldmap_y = 0;

void UpdateCamera()
{

}

int seed = 0;
void GenerateNewRandomSeed()
{
	seed = std::time(nullptr);
	rnd_gen = std::default_random_engine(seed);
	std::cout << "seed: " << seed << std::endl;
}

int main()
{
	GenerateNewRandomSeed();

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Selda 2079");
	LoadGame(window);

	sf::View free_cam_view(sf::FloatRect(0, 0, WINDOW_WIDTH*1.5f, WINDOW_HEIGHT*1.5f));

	sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(view);

	GenerateGameMap();
	cam_current_worldmap_x = EntS::pos_x[EntS::id_player] / TILE_SIZE / MAP_SIZE_X;
	cam_current_worldmap_y = EntS::pos_y[EntS::id_player] / TILE_SIZE / MAP_SIZE_Y;

	InitGUI();

	sf::Clock deltaClock;
	sf::Clock clock;
	sf::Clock clk_general;

	while (window.isOpen()) 
	{
		int time_general = clk_general.getElapsedTime().asMilliseconds();
		int dt = clock.getElapsedTime().asMilliseconds();
		clock.restart();

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
		ImGui::SFML::Update(window, deltaClock.restart());

		const int CAM_TRANSITION_TIME = 500;

		int player_x = EntS::pos_x[EntS::id_player];
		int player_y = EntS::pos_y[EntS::id_player];

		int cam_x = cam_current_worldmap_x * MAP_SIZE_X*TILE_SIZE / 100 + TILE_SIZE * MAP_SIZE_X / 200;
		int cam_y = cam_current_worldmap_y * MAP_SIZE_Y*TILE_SIZE / 100 + WINDOW_HEIGHT / 2;

		switch (cam_state)
		{
			case CameraState::CAMERA_GAME:
			{
				EntS::UpdateEntities(dt);
				UpdateGUI(dt);

				int tile_x = (player_x + TILE_SIZE / 2) / TILE_SIZE;
				int tile_y = (player_y + TILE_SIZE / 2) / TILE_SIZE;

				if (player_y < 0 + cam_current_worldmap_y * MAP_SIZE_Y*TILE_SIZE && cam_current_worldmap_y > 0)
				{
					cam_state = CameraState::MAP_TRANSITION_UP;
					cam_timer = CAM_TRANSITION_TIME;
					cam_current_worldmap_y--;
				}
				if (player_y > (cam_current_worldmap_y + 1)*MAP_SIZE_Y*TILE_SIZE)
				{
					cam_state = CameraState::MAP_TRANSITION_DOWN;
					cam_timer = CAM_TRANSITION_TIME;
					cam_current_worldmap_y++;
				}
				if (player_x < 0 + cam_current_worldmap_x * MAP_SIZE_X*TILE_SIZE && cam_current_worldmap_x > 0)
				{
					cam_state = CameraState::MAP_TRANSITION_LEFT;
					cam_timer = CAM_TRANSITION_TIME;
					cam_current_worldmap_x--;
				}
				if (player_x > (cam_current_worldmap_x + 1)*MAP_SIZE_X*TILE_SIZE)
				{
					cam_state = CameraState::MAP_TRANSITION_RIGHT;
					cam_timer = CAM_TRANSITION_TIME;
					cam_current_worldmap_x++;
				}

				if (IsTeleportLink(tile_x, tile_y))
				{
					cam_state = CameraState::HOUSE_TRANSITION;

					cam_timer = 0;

					int tp_x = world_map[tile_y][tile_x].tp_x;
					int tp_y = world_map[tile_y][tile_x].tp_y;

					cam_transition_final_tx = tp_x;
					cam_transition_final_ty = tp_y;
				}

			} break;

			case CameraState::HOUSE_TRANSITION:
			{
				cam_timer += dt;

				if (cam_timer > CAM_TRANSITION_TIME/2)
				{
					EntS::pos_x[EntS::id_player] = cam_transition_final_tx * TILE_SIZE;
					EntS::pos_y[EntS::id_player] = cam_transition_final_ty * TILE_SIZE;

					cam_current_worldmap_x = cam_transition_final_tx / MAP_SIZE_X;
					cam_current_worldmap_y = cam_transition_final_ty / MAP_SIZE_Y;
				}
				if (cam_timer > CAM_TRANSITION_TIME)
				{
					cam_state = CameraState::CAMERA_GAME;
					EntS::ent_state[EntS::id_player] = PlayerState::IDLE;
				}
			} break;

			case CameraState::MAP_TRANSITION_UP:
			{
				cam_timer -= dt;
				cam_y += ((MAP_SIZE_Y*TILE_SIZE / 100) *cam_timer) / CAM_TRANSITION_TIME;
				if (cam_timer < 0)
				{
					cam_y = cam_current_worldmap_y * MAP_SIZE_Y*TILE_SIZE / 100 + WINDOW_HEIGHT / 2;
					cam_state = CameraState::CAMERA_GAME;
					EntS::ent_state[EntS::id_player] = PlayerState::IDLE;
				}
			} break;

			case CameraState::MAP_TRANSITION_DOWN:
			{
				cam_timer -= dt;
				cam_y -= ((MAP_SIZE_Y*TILE_SIZE / 100) *cam_timer) / CAM_TRANSITION_TIME;
				if (cam_timer < 0)
				{
					cam_y = cam_current_worldmap_y * MAP_SIZE_Y*TILE_SIZE / 100 + WINDOW_HEIGHT / 2;
					cam_state = CameraState::CAMERA_GAME;
					EntS::ent_state[EntS::id_player] = PlayerState::IDLE;
				}
			} break;

			case CameraState::MAP_TRANSITION_LEFT:
			{
				cam_timer -= dt;
				cam_x += ((MAP_SIZE_X*TILE_SIZE / 100) *cam_timer) / CAM_TRANSITION_TIME;
				if (cam_timer < 0)
				{
					cam_x = cam_current_worldmap_x * MAP_SIZE_X*TILE_SIZE / 100 + TILE_SIZE * MAP_SIZE_X / 200;
					cam_state = CameraState::CAMERA_GAME;
					EntS::ent_state[EntS::id_player] = PlayerState::IDLE;
				}
			} break;

			case CameraState::MAP_TRANSITION_RIGHT:
			{
				cam_timer -= dt;
				cam_x -= ((MAP_SIZE_X*TILE_SIZE / 100) *cam_timer) / CAM_TRANSITION_TIME;
				if (cam_timer < 0)
				{
					cam_x = cam_current_worldmap_x * MAP_SIZE_X*TILE_SIZE / 100 + TILE_SIZE * MAP_SIZE_X / 200;
					cam_state = CameraState::CAMERA_GAME;
					EntS::ent_state[EntS::id_player] = PlayerState::IDLE;
				}
			} break;
		}

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))
		{
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))
		{
		}

		view.setCenter(cam_x, cam_y);

		window.setView(view);

#if _DEBUG
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))
		{
			//free_cam_view_on = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))
		{
			//free_cam_view_on = false;
		}
		if (free_cam_view_on)
		{
			if (input_state.IsPressed(GameKeys::CAM_LEFT))
			{
				free_cam_x -= dt;
			}
			if (input_state.IsPressed(GameKeys::CAM_RIGHT))
			{
				free_cam_x += dt;
			}
			if (input_state.IsPressed(GameKeys::CAM_UP))
			{
				free_cam_y -= dt;
			}
			if (input_state.IsPressed(GameKeys::CAM_DOWN))
			{
				free_cam_y += dt;
			}
			//free_cam_view.setCenter(free_cam_x, free_cam_y);
			//window.setView(free_cam_view);
		}
#endif	

		//if (EntitySystem::ent_state[EntitySystem::id_player] == PlayerState::DEAD)
		{
			if (input_state.IsJustPressed(GameKeys::START))
			{
				GenerateNewRandomSeed();
				PlayerInfo::Reset();
				ResetGameMap();
				GenerateGameMap();
				cam_current_worldmap_x = EntS::pos_x[EntS::id_player] / TILE_SIZE / MAP_SIZE_X;
				cam_current_worldmap_y = EntS::pos_y[EntS::id_player] / TILE_SIZE / MAP_SIZE_Y;
				InitGUI();
			}
		}


		//DrawImguiCosas();

		window.clear();

		//view.setViewport(sf::FloatRect(0, 0.25f, 1, 0.75f));
		//window.setView(view);

		DrawMap(cam_current_worldmap_x, cam_current_worldmap_y, window, spr_tile, time_general);
		EntS::DrawEntities(cam_current_worldmap_x, cam_current_worldmap_y, sprite, window);

		window.setView(window.getDefaultView());

		if (cam_state == CameraState::HOUSE_TRANSITION)
		{
			sf::RectangleShape rect_fade;

			rect_fade.setFillColor(sf::Color::Transparent);
			rect_fade.setOutlineColor(sf::Color::Black);
			
			int player_x = EntS::pos_x[EntS::id_player];
			int player_y = EntS::pos_y[EntS::id_player];

			rect_fade.setSize(sf::Vector2f(MAP_SIZE_X*TILE_SIZE/100, MAP_SIZE_Y*TILE_SIZE/100));
			rect_fade.setPosition(0, MARGIN_TOP_GUI);

			const int magic_9 = 9;

			if (cam_timer < CAM_TRANSITION_TIME / 2)
			{
				rect_fade.setOutlineThickness(-(magic_9*TILE_SIZE / 100)*(1.0f*cam_timer / (CAM_TRANSITION_TIME*0.5f)));
			}
			else
			{
				rect_fade.setOutlineThickness(-(magic_9*TILE_SIZE / 100)*(1.0f - 1.0f*(cam_timer - CAM_TRANSITION_TIME*0.5f) / (CAM_TRANSITION_TIME*0.5f)));
			}


			window.draw(rect_fade);
		}

		

		//view.setViewport(sf::FloatRect(0, 0, 1, 1));
		//window.setView(view);

		
		DrawGUI(window, sprite);


		/*
		float center_x = EntitySystem::pos_x[EntitySystem::id_player]/100;
		if (center_x - view.getSize().x/2  < 0) center_x = view.getSize().x/2;
		if (center_x + view.getSize().x/2 > TILE_SIZE*MAP_SIZE_X/2) center_x = TILE_SIZE * MAP_SIZE_X - view.getSize().x / 2;
		float center_y = EntitySystem::pos_y[EntitySystem::id_player] / 100;
		if (center_y - view.getSize().y / 2 < 0) center_y = view.getSize().y / 2;
		if (center_y + view.getSize().y / 2 > MAP_SIZE_Y*TILE_SIZE) center_y = MAP_SIZE_Y * TILE_SIZE;
		view.setCenter(center_x, center_y);		
		*/

		

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}
