#pragma once

#include "entity.h"
#include "entity_example.h"

namespace EntS
{
	std::vector<Entity*> factorio;

	Entity* SuperFactorio(EntityType t)
	{
		Entity* e;
		switch (t)
		{
			case EntS::EntityType::ENTITY_EXAMPLE:
			{
				e = new EntityExample();
			} break;

			default:
			{
				//assert(false);
			} break;
		}
		
		factorio.push_back(e);
		return e;
	}
}
