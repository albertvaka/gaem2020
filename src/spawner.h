#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "vector.h"

struct Spawner : Entity, EntS<Spawner>
{

	const int INTERVAL = 6000;
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
				timer = 0;
				spawn();
			}
		}
		empty = true;
	}

	void spawn() {
		new Cadaver(pos);
		
	}

};
struct Detector : Entity, EntS<Detector>
{
	Spawner* spawner;
	Detector(vec position, Spawner *s) {
		pos = position;
		spawner = s;
	}
	void Update(int dt)
	{

	}

};
struct Despawner : Entity, EntS<Despawner>
{
	Despawner(vec position) {
		pos = position;
	}

};