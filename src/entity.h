#pragma once

#include "mates.h"
#include "selfregister.h"
#include "animation.h"

enum class EntityState
{
	IDLE,
	MOVING,
};

enum class EntityDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Entity : public EntS<Entity>
{
	EntityState state;
	Mates::xy pos;
	Mates::xy speed;
	int timer = 0;
	Animation anim;
	bool alive = true;
	Entity* parent = NULL;
	EntityDirection dir;
};
