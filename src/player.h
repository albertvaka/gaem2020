#pragma once

#include "entity.h"
#include "animation2.h"
#include "anim_lib.h"
#include "partsys.h"
#include "singleinstance.h"


struct Player : CircleEntity, SingleInstance<Player>
{

	const float kMaxSpeed = 500.f; // in pixels/second
	const float kAccel = 200.f; // in pixels/second^2
	const float kBrake = 600.f;
	const float kDrag = 40.f; // brake force when not accelerating

	const float kMaxAngularSpeed = 120.f; // in degrees/second
	const float kAngularAccel = 200.f; // in degrees/second^2
	const float kAngularDrag = 600.f; // brake force when not turning

	Animation2 anim;
	float angle = 0.0f;
	float speed = 0.0f;
	float angularSpeed = 0.0f;
	GPU_Rect spriteBottom;
	GPU_Rect spriteTop;
	float attack_timer = 0.f;

	Player(const vec& position, float angle);

	void Move(float dt);
	void Update(float dt) override;
	void Draw() const override;
};
