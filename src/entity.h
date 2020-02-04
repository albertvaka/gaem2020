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


struct Entity : EntS<Entity>
{
	EntityState state;
	vec pos;
	vec speed;
	vec size = vec(16, 16);
	int timer = 0;
	Animation anim;
	bool alive = true;
	//Entity* parent = NULL;
	EntityDirection dir = EntityDirection::DOWN;
};

struct SortedDrawable : Entity, EntS<SortedDrawable> {
	virtual void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{

	}
	virtual void Draw(sf::VertexArray& vao)
	{

	}
};

struct Cintable : EntS<Cintable> {
	EntityDirection prevCintaDirection = EntityDirection::NONE;
	EntityDirection currCintaDirection = EntityDirection::NONE;

	virtual vec positionPlz() = 0;
	//virtual vec sizePlz() = 0;

	void SetSpeedWithCinta(vec& speed)
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
