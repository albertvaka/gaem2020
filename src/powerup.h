#pragma once

#include "vec.h"
#include "entity.h"
#include "selfregister.h"

struct PowerUp : CircleEntity, SelfRegister<PowerUp>
{
	PowerUp(const vec& p) : CircleEntity(p, 13/2.f) { }
	void Update(float dt) override { };
	void Draw() const override;
};

