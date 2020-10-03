#pragma once

#include "vec.h"
#include "entity.h"
#include "selfregister.h"

struct PowerUp : BoxEntity, SelfRegister<PowerUp>
{
	PowerUp(float x, float y) : BoxEntity(vec(x-10,y-8), vec(10,6)) { }
	void Update(float dt) override { };
	void Draw() const override;
};

