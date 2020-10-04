#pragma once

#include "vec.h"
#include "entity.h"
#include "selfregister.h"

struct StartLine : SelfRegister<StartLine>
{
	RotableBounds bbounds;

	RotableBounds bounds() { return bbounds; }

	StartLine(const Bounds& start) : bbounds(start) { }
	void Update(float dt);
	void Draw() const;

	void PlayerCollided();

	std::string GetTimelapText() const;
	std::string GetBestlapText() const;
	bool HasBestLap() const;

	bool playerCollidedForFirstTime = false;
	bool playerColliding = false;
	float timelapTimer = 0.0f;
	float bestlapTimer = -1.0f;

private:
	std::string FormatTimelapText(float t) const;
};

