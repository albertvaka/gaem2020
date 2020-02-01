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
	RIGHT,
	NONE
};

struct Entity : public EntS<Entity>
{
	EntityState state;
	vec pos;
	vec speed;
	int timer = 0;
	Animation anim;
	bool alive = true;
	int inCinta[4] = { 0,0,0,0 };
	Entity* parent = NULL;
	EntityDirection dir;

	virtual void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{

	}
	virtual void Draw(sf::VertexArray& vao)
	{

	}

	void SetSpeedWithCinta()
	{
		sf::Vector2f newSpeed(0.f, 0.f);
		speed.x += inCinta[static_cast<int>(EntityDirection::RIGHT)] * 0.01f;
		speed.x -= inCinta[static_cast<int>(EntityDirection::LEFT)] * 0.01f;
		speed.y -= inCinta[static_cast<int>(EntityDirection::UP)] * 0.01f;
		speed.y += inCinta[static_cast<int>(EntityDirection::DOWN)] * 0.01f;
		//speed = newSpeed;
		for (int i = 0; i < 4; i++) inCinta[i] = 0;
	}
	bool InCinta()
	{
		return inCinta[0] + inCinta[1] + inCinta[2] + inCinta[3];
	}

};
