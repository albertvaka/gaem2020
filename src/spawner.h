#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "vector.h"

struct CadaverSpawner : public Entity, public EntS<CadaverSpawner>
{
	const int INTERVAL = 3000;
	bool empty = true;
	int timer = INTERVAL;

	CadaverSpawner(vec position) 
	{
		pos = position;
	}

	void Update(int dt)
	{
		timer += dt;
		if (timer > INTERVAL) 
		{
			if (empty) 
			{
				timer = 0;
				//spawn();
			}
		}
		empty = true;
	}

	void spawn() 
	{
		new Cadaver(pos + vec(8, 8));
	}
};

struct Detector : public Entity, public EntS<Detector>
{
	CadaverSpawner* spawner;
	Detector(vec position, CadaverSpawner *s) {
		pos = position;
		spawner = s;
	}
	void Update(int dt)
	{

	}

};
struct Despawner : public Entity, public EntS<Despawner>
{
	Despawner(vec position) {
		pos = position;
	}

};