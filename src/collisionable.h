#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"

struct CollisionableEntity : public Entity, public EntS<CollisionableEntity>
{
	CollisionableEntity()
	{
	}
};

