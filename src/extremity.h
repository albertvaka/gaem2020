#pragma once

#include "entity.h"
#include "entity_system.h"



struct Extremity : public Entity, EntS<Extremity> 
{


	enum BodyColor {
		NONE = 0,
		WHITE,
		BLACK,
		YELLOW,
		GREEN,
		BLUE,
		RED,
		SIZE
	};

	int color;
	int anim;

	Extremity(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}

	Extremity() { }
};