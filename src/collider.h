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


template <typename T, typename U, typename Z, typename Y>
void collide(const std::vector<T*>& setA, const std::vector<U*>& setB, void (*callback)(Y*, Z*)) 
{
	auto sa = setA.size();
	for (int i = 0; i < sa; ++i) 
	{
		T* a = setA[i];
		auto sb = setB.size();
		for (int j = i+1; j < sb; ++j) 
		{
			U* b = setB[j];
			if ((void*)a == (void*)b) continue;
			if (Collision(a, b)) 
			{
				callback(a, b);
			}
		}
	}
}

void rebota(Entity* a, Entity* b)
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

void GrandePeque_collision(EntityExample* grande, EntityExampleSmall* peque) 
{
	peque->alive = false;
}

void UpdateCollisions(int dt) 
{
	// If EntityExample collides with EntityExample, call entityExample_collision_callback
	collide(EntS<EntityExample>::getAll(), EntS<EntityExample>::getAll(), rebota);
	collide(EntS<EntityExampleSmall>::getAll(), EntS<EntityExampleSmall>::getAll(), rebota);
	collide(EntS<EntityExample>::getAll(), EntS<EntityExampleSmall>::getAll(), GrandePeque_collision);
}
