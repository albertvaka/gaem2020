#pragma once
#include <SFML/Graphics.hpp>

struct AnimationData
{
	int frames;
	sf::IntRect rect[16];
	int timer[16];
};

#if FALSE
AnimationData anim_lib[] =
{
	//NONE
	{
		1,
		{
			{0, 0, 0, 0},
		},
		0
	},
	//ANIM_EXAMPLE
	{   1,
		{
			{2 * 16, 3 * 16, 16, 16},
		},
		{
			100
		},
	},
	//ANIM_EXAMPLE_COLLIDING
	{   1,
		{
			{3 * 16, 3 * 16, 16, 16},
		},
		{
			100, 100, 100,
		},
	}
};
#endif

struct Animation
{
	int anim_timer;
	int frame_current;
	AnimationData* data;

	void Update(int dt)
	{
		anim_timer += dt;

		if (anim_timer > data->timer[frame_current])
		{
			anim_timer = anim_timer - data->timer[frame_current];
			
			frame_current++;
			if (frame_current >= data->frames)
			{
				frame_current = 0;
			}
		}
	}

	void Reset()
	{
		anim_timer = 0;
		frame_current = 0;
	}

	sf::IntRect CurrentFrame()
	{
		AnimationData* anim_data = data;
		return anim_data->rect[frame_current];
	}
};