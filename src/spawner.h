#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "vector.h"

struct Spawner : public Entity, public EntS<Spawner>
{

	const int INTERVAL = 3000;
	bool empty = true;
	int timer = INTERVAL;
	Spawner(vec position) {
		pos = position;
	}

	void Update(int dt)
	{
		timer += dt;
		if (timer > INTERVAL) {
			if (empty) {
				timer -= INTERVAL;
				spawn();
			}
		}
		empty = true;
	}

	void spawn() {
		new Cadaver(pos);
		
	}

};

struct Despawner : public Entity, public EntS<Despawner>
{
	Despawner(vec position) {
		pos = position;
	}

};