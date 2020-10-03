#pragma once

#include "entity.h"
#include "animation2.h"
#include "anim_lib.h"
#include "partsys.h"
#include "singleinstance.h"

struct Player : CircleEntity, SingleInstance<Player>
{
	Animation2 anim;
	float angle = 0;

	Player(const vec& position, float angle);

	void Update(float dt) override;
	void Draw() const override;
};
