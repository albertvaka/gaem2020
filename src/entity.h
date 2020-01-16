#pragma once

#include "mates.h"
#include "selfregister.h"

enum class EntityState
{
	MOVING,
	COLLIDED
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
};
