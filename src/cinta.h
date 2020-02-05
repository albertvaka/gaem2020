#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Cinta : Entity, EntS<Cinta>
{

	Cinta(vec position, EntityDirection direction) {
		pos = position;
		anim.Ensure(AnimationType::BELT_RIGHT);
		dir = direction;
	}

};
