#pragma once

#include "vec.h"
#include "entity.h"
#include "selfregister.h"

struct PowerUp : SelfRegister<PowerUp>
{
	vec from;
	vec to;
	bool inner;
	RotableBounds bbounds;

	RotableBounds bounds() {
		return bbounds;
	}

	PowerUp(const vec& from, const vec& to, bool inner);
	void Draw() const;
};

