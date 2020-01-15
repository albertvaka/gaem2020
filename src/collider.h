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


void muere(EntityExampleSmall* b) 
{
	//no ta echo
}

//FIXME: this should be a lambda, but doesn't work yet
void GrandeGrande_collision(EntityExample* a, EntityExample* b)
{
	rebota(a, b);
}

void PequePeque_collision(EntityExampleSmall* a, EntityExampleSmall* b)
{
	rebota(a, b);
}

void GrandePeque_collision(EntityExample* a, EntityExampleSmall* b) 
{
	muere(b);
}

void UpdateCollisions(int dt) 
{
	// If EntityExample collides with EntityExample, call entityExample_collision_callback
	collide(EntS<EntityExample*>::getAll(), EntS<EntityExample*>::getAll(), GrandeGrande_collision);
	collide(EntS<EntityExampleSmall*>::getAll(), EntS<EntityExampleSmall*>::getAll(), PequePeque_collision);
	collide(EntS<EntityExample*>::getAll(), EntS<EntityExampleSmall*>::getAll(), GrandePeque_collision);
}
