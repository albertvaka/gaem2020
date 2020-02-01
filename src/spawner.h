#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "vector.h"

struct Spawner : public Entity, public EntS<Spawner>
{

	const int INTERVAL = 3000;

	int timer = 0;
	Spawner(vec position) {
		pos = position;
	}

	void Update(int dt)
	{
		timer += dt;
		if (timer > INTERVAL) {
			timer -= INTERVAL;
			spawn();
		}
	}

	void spawn() {

		new Cadaver(pos);
	}

};