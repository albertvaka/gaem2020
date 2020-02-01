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
	vec pos;
	vec speed;
	int timer = 0;
	Animation anim;
	bool alive = true;
	Entity* parent = NULL;
	EntityDirection dir;

	virtual void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{

	}
	virtual void Draw(sf::VertexArray& vao)
	{

	}

};
