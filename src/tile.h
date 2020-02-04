#pragma once

#include "mates.h"
#include "vector.h"


static Mates::xy PosToTile(vec pos)
{
	return
	{
		int((pos.x) / 16),
		int((pos.y) / 16)
	};
}