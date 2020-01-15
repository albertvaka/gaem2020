#pragma once

#include "selfregister.h"
#include "entity.h"
#include <functional>
#include "entity_example.h"

bool Collision(Entity* entity_a, Entity* entity_b)
{
	int COLLISION_SIZE = 1600;

	Mates::xy a = entity_a->pos;
	Mates::xy b = entity_b->pos;

	//rectangle colision
	return
		(a.x < b.x + COLLISION_SIZE && a.x + COLLISION_SIZE > b.x &&
			a.y < b.y + COLLISION_SIZE && a.y + COLLISION_SIZE > b.y);
}


template <typename T, typename U>
void collide(const std::vector<T*>& setA, const std::vector<U*>& setB, void (*callback)(T*, U*)) 
{
	for (int i = 0; i < setA.size(); ++i) 
	{
		T* a = setA[i];
		for (int j = i+1; j < setB.size(); ++j) 
		{
			U* b = setB[j];
			if (a == b) continue;
			if (Collision(a, b)) 
			{
				callback(a, b);
			}
		}
	}
}

//FIXME: this should be a lambda, but doesn't work yet
//FIXME: this should be a lambda, but doesn't work yet
void CollisionableEntity_collision_callback(CollisionableEntity* a, CollisionableEntity* b)
{
	if (a->state != EntityState::COLLIDED)
	{
		a->state = EntityState::COLLIDED;
		a->timer = 0;
		a->speed.x = -a->speed.x;
		a->speed.y = -a->speed.y;
	}

	if (b->state != EntityState::COLLIDED) 
	{
		b->state = EntityState::COLLIDED;
		b->timer = 0;
		b->speed.x = -b->speed.x;
		b->speed.y = -b->speed.y;
	}
}

void UpdateCollisions(int dt) 
{
	// If EntityExample collides with EntityExample, call entityExample_collision_callback
	collide(EntS<CollisionableEntity*>::getAll(), EntS<CollisionableEntity*>::getAll(), CollisionableEntity_collision_callback);
}
