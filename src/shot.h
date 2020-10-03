#pragma once

#include "entity.h"
#include "selfregister.h"

constexpr const float kFireShotRadius = 2.f;

struct Shot : CircleEntity, SelfRegister<Shot>
{
	Shot(const vec& pos, const vec& vel)
		: CircleEntity(pos, kFireShotRadius, vel)
	{
	}

	void Update(float dt);

	void Draw() const;
};
