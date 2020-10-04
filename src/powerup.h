#pragma once

#include "vec.h"
#include "entity.h"
#include "selfregister.h"

struct PowerUp : SelfRegister<PowerUp>
{
	//bool alive = true;
	bool inner;
	RotableBounds bbounds;

	RotableBounds bounds() {
		return bbounds;
	}

	PowerUp(const vec& from, const vec& prev, bool inner);
	void Draw() const;
};

