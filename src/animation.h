#pragma once

#include <SFML/Graphics.hpp>


enum AnimationType
{
	NONE,
	ANIM_EXAMPLE,
	ANIM_EXAMPLE_COLLIDING
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
			100
		},
	}
};


struct Animation
{
	AnimationType anim_type;
	int anim_timer;
	int current_frame;

	Animation() {
		Reset();
	}

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
				current_frame = 0;
			}
		}
	}

	void Reset()
	{
		anim_timer = 0;
		current_frame = 0;
	}

	void Ensure(AnimationType type)
	{
		if (anim_type != type)
		{
			anim_type = type;
			Reset();
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
