#pragma once

#include "vec.h"
#include "entity.h"
#include "selfregister.h"

struct StartLine : BoxEntity, SelfRegister<StartLine>
{
	StartLine(const vec& p) : BoxEntity(p, {20, 220}) { }
	void Update(float dt) override;
	void Draw() const override;

	void PlayerCollided();

	std::string GetTimelapText() const;
	std::string GetBestlapText() const;
	bool HasBestLap() const;

	bool playerColliding = true;
	float timelapTimer = 0.0f;
	float bestlapTimer = -1.0f;

private:
	std::string FormatTimelapText(float t) const;
};

