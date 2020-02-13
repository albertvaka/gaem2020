#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Cinta : Entity, EntS<Cinta>
{

	Cinta(vec position, EntityDirection direction) {
		pos = position+vec(8,8);
		anim.Ensure(AnimationType::BELT_RIGHT);
		dir = direction;
	}

};
