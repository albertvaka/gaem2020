#pragma once

#include "vec.h"
#include "entity.h"
#include "selfregister.h"

struct Wall : SelfRegister<Wall>
{
	vec from;
	vec to;
	bool inner;
	RotableBounds bbounds;

	RotableBounds bounds() {
		return bbounds;
	}

	Wall(const vec& from, const vec& to, bool inner);
	void Update(float dt);
	void Draw() const;

	void JustCollided();

	float timerLastCol = -1.0f;
};
