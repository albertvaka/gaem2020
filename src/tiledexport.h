#pragma once

#include <array>

#include "vec.h"
#include "bounds.h"
#include "SDL_gpu.h"

struct TiledEntities
{
	static const std::array<vec, 1401> obstacle;
	static const vec spawn;
	static const std::array<vec, 28> enemy_spawn;
	
};

struct TiledAreas
{
	
};

struct TiledPolygons
{
	static const std::array<vec, 40> outter;
	static const std::array<vec, 41> inner;
	
};