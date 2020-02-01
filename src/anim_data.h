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
			100,100,200,100,
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
			100,200,100,
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
};
