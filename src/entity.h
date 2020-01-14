#pragma once

#include "mates.h"

namespace EntS
{
	static int __GetNewID()
	{
		static int id = 0;
		return id++;
	}

	enum EntityType
	{
		NONE = 0,
		ENTITY_EXAMPLE,
		COUNT
	};

	enum EntityState
	{
		MOVING,
		COLLIDED
	};

	struct Entity
	{
		int id;
		EntityType type;
		EntityState state;
		Mates::xy pos;
		Mates::xy speed;
		int timer;
		Animation anim;

		Entity()
		{
			id = __GetNewID();
		}

		virtual void Update(int dt) = 0;
		virtual void Draw(sf::Sprite& spr) = 0;
		virtual void OnCollision(Entity* other_ent) = 0;
	};

}
