#pragma once
#include <SFML/Graphics.hpp>

struct AnimationData
{
	int frames;
	sf::IntRect rect[16];
	int timer[16];
};

enum AnimationType
{
	PLAYER_WALKING_DOWN,
	PLAYER_WALKING_UP,
	PLAYER_WALKING_RIGHT,
	PLAYER_WALKING_LEFT,
	PLAYER_IDLE_DOWN,
	PLAYER_IDLE_UP,
	PLAYER_IDLE_RIGHT,
	PLAYER_IDLE_LEFT,
	DOCTOR_WALKING_DOWN,
	DOCTOR_WALKING_UP,
	DOCTOR_WALKING_RIGHT,
	DOCTOR_WALKING_LEFT,
	DOCTOR_IDLE_DOWN,
	DOCTOR_IDLE_UP,
	DOCTOR_IDLE_RIGHT,
	DOCTOR_IDLE_LEFT,
	BELT_RIGHT,
	BUTTON_A_PRESS,
	NADA,
	POKEMON,
	PLAGUEDOC_IDLE_DOWN,
	PLAGUEDOC_IDLE_UP,
	PLAGUEDOC_IDLE_LEFT,
	PLAGUEDOC_IDLE_RIGHT,
	PLAGUEDOC_WALKING_LEFT,
	PLAGUEDOC_WALKING_RIGHT,
	PLAGUEDOC_WALKING_UP,
	PLAGUE_DOC_WALKING_DOWN,
	COOLGUY_IDLE_DOWN,
	COOLGUY_IDLE_UP,
	COOLGUY_IDLE_LEFT,
	COOLGUY_IDLE_RIGHT,
	COOLGUY_WALKING_DOWN,
	COOLGUY_WALKING_UP,
	COOLGUY_WALKING_LEFT,
	COOLGUY_WALKING_RIGHT,
};

AnimationData anim_lib[] =
{
	//PLAYER_WALKING_DOWN
	{
		4,
		{
			{3,18,10,14},
			{3,1,10,15},
			{3,34,10,14},
			{3,1,10,15},
		},
		{
			100,100,100,100,
		},
	},
	//PLAYER_WALKING_UP
	{
		4,
		{
			{19,18,10,14},
			{20,1,8,15},
			{19,34,10,14},
			{20,1,8,15},
		},
		{
			100,100,100,100,
		},
	},
	//PLAYER_WALKING_RIGHT
	{
		3,
		{
			{36,18,9,14},
			{36,33,10,15},
			{36,1,9,15},
		},
		{
			100,100,100,
		},
	},
	//PLAYER_WALKING_LEFT
	{
		3,
		{
			{52,18,9,14},
			{51,33,10,15},
			{52,1,9,15},
		},
		{
			100,100,100,
		},
	},
	//PLAYER_IDLE_DOWN
	{
		1,
		{
			{3,1,10,15},
		},
		{
			100,
		},
	},
	//PLAYER_IDLE_UP
	{
		1,
		{
			{20,1,8,15},
		},
		{
			100,
		},
	},
	//PLAYER_IDLE_RIGHT
	{
		1,
		{
			{36,1,9,15},
		},
		{
			100,
		},
	},
	//PLAYER_IDLE_LEFT
	{
		1,
		{
			{52,1,9,15},
		},
		{
			100,
		},
	},
	//DOCTOR_WALKING_DOWN
	{
		4,
		{
			{67,17,10,15},
			{67,0,10,16},
			{68,33,9,15},
			{67,0,10,16},
		},
		{
			100,100,100,100,
		},
	},
	//DOCTOR_WALKING_UP
	{
		4,
		{
			{83,17,9,15},
			{83,0,10,16},
			{84,33,9,15},
			{83,0,10,16},
		},
		{
			100,100,100,100,
		},
	},
	//DOCTOR_WALKING_RIGHT
	{
		3,
		{
			{100,17,9,15},
			{100,33,10,15},
			{100,0,9,16},
		},
		{
			100,100,100,
		},
	},
	//DOCTOR_WALKING_LEFT
	{
		3,
		{
			{116,17,9,15},
			{115,33,10,15},
			{116,0,9,16},
		},
		{
			100,100,100,
		},
	},
	//DOCTOR_IDLE_DOWN
	{
		1,
		{
			{67,0,10,16},
		},
		{
			100,
		},
	},
	//DOCTOR_IDLE_UP
	{
		1,
		{
			{83,0,10,16},
		},
		{
			1,
		},
	},
	//DOCTOR_IDLE_RIGHT
	{
		1,
		{
			{100,0,9,16},
		},
		{
			100,
		},
	},
	//DOCTOR_IDLE_LEFT
	{
		1,
		{
			{116,0,9,16},
		},
		{
			100,
		},
	},
	//BELT_RIGHT
	{
		4,
		{
			{0,48,16,16},
			{16,48,16,16},
			{32,48,16,16},
			{48,48,16,16},
		},
		{
			200,200,200,200,
		},
	},
	//BUTTON_A_PRESS
	{
		2,
		{
			{0,112,8,8},
			{8,112,8,8},
		},
		{
			500,250,
		},
	},
	//NADA
	{
		1,
		{
			{1,1,1,1},
		},
		{
			1,
		},
	},
	//POKEMON
	{
		12,
		{
			{96,48,30,32},
			{126,48,30,32},
			{156,48,30,32},
			{186,48,30,32},
			{96,80,30,32},
			{126,80,30,32},
			{156,80,30,32},
			{186,80,30,32},
			{96,112,30,32},
			{126,112,30,32},
			{156,112,30,32},
			{186,112,30,32},
		},
		{
			100,100,100,100,100,100,100,100,100,100,100,100,
		},
	},
	//PLAGUEDOC_IDLE_DOWN
	{
		1,
		{
			{131,1,10,15},
		},
		{
			100,
		},
	},
	//PLAGUEDOC_IDLE_UP
	{
		1,
		{
			{147,1,10,15},
		},
		{
			100,
		},
	},
	//PLAGUEDOC_IDLE_LEFT
	{
		1,
		{
			{179,1,11,15},
		},
		{
			100,
		},
	},
	//PLAGUEDOC_IDLE_RIGHT
	{
		1,
		{
			{163,1,11,15},
		},
		{
			100,
		},
	},
	//PLAGUEDOC_WALKING_LEFT
	{
		3,
		{
			{179,1,11,15},
			{179,17,11,15},
			{178,33,11,15},
		},
		{
			100,100,100,
		},
	},
	//PLAGUEDOC_WALKING_RIGHT
	{
		3,
		{
			{163,1,11,15},
			{163,17,11,15},
			{164,33,11,15},
		},
		{
			100,100,100,
		},
	},
	//PLAGUEDOC_WALKING_UP
	{
		4,
		{
			{147,18,10,14},
			{147,1,10,15},
			{147,34,10,14},
			{147,1,10,15},
		},
		{
			100,100,100,100,
		},
	},
	//PLAGUE_DOC_WALKING_DOWN
	{
		4,
		{
			{131,18,10,14},
			{131,1,10,15},
			{131,34,10,14},
			{131,1,10,15},
		},
		{
			100,100,100,100,
		},
	},
	//COOLGUY_IDLE_DOWN
	{
		1,
		{
			{195,1,10,15},
		},
		{
			100,
		},
	},
	//COOLGUY_IDLE_UP
	{
		1,
		{
			{211,1,10,15},
		},
		{
			100,
		},
	},
	//COOLGUY_IDLE_LEFT
	{
		1,
		{
			{243,1,9,15},
		},
		{
			100,
		},
	},
	//COOLGUY_IDLE_RIGHT
	{
		1,
		{
			{228,1,9,15},
		},
		{
			100,
		},
	},
	//COOLGUY_WALKING_DOWN
	{
		4,
		{
			{195,18,9,14},
			{195,1,10,15},
			{196,34,9,14},
			{195,1,10,15},
		},
		{
			100,100,100,0,
		},
	},
	//COOLGUY_WALKING_UP
	{
		4,
		{
			{211,18,9,14},
			{211,1,10,15},
			{212,34,9,14},
			{211,1,10,15},
		},
		{
			100,100,100,100,
		},
	},
	//COOLGUY_WALKING_LEFT
	{
		3,
		{
			{243,18,9,14},
			{242,33,10,15},
			{243,1,9,15},
		},
		{
			100,100,100,
		},
	},
	//COOLGUY_WALKING_RIGHT
	{
		3,
		{
			{228,18,9,14},
			{228,33,10,15},
			{228,1,9,15},
		},
		{
			100,100,100,
		},
	},
};
