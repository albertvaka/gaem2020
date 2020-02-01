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
	EntityDirection prevCintaDirection = EntityDirection::NONE;
	EntityDirection currCintaDirection = EntityDirection::NONE;
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
		if (currCintaDirection != EntityDirection::NONE)
		{
			speed.x += (EntityDirection::RIGHT == currCintaDirection) * 0.015f;
			speed.x -= (EntityDirection::LEFT == currCintaDirection) * 0.015f;
			speed.y -= (EntityDirection::UP == currCintaDirection) * 0.015f;
			speed.y += (EntityDirection::DOWN == currCintaDirection) * 0.015f;
		}
		
		//speed = newSpeed;
		prevCintaDirection = currCintaDirection;
		currCintaDirection = EntityDirection::NONE;
	}


};
