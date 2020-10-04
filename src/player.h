#pragma once

#include "entity.h"
#include "animation2.h"
#include "anim_lib.h"
#include "partsys.h"
#include "singleinstance.h"


struct Player : SingleInstance<Player>
{
	RotableBounds bbounds;

	const float kMaxSpeed = 600.f; // in pixels/second
	const float kAccel = 220.f; // in pixels/second^2
	const float kBrake = 1600.f;
	const float kDrag = 40.f; // brake force when not accelerating

	const float kMaxAngularSpeed = 180.f; // in degrees/second
	const float kAngularAccel = 360.f; // in degrees/second^2
	const float kAngularDrag = 600.f; // brake force when not turning

	Animation2 anim;
	vec pos;
	vec vel;
	float angle = 0.0f;
	float speed = 0.0f;
	float angularSpeed = 0.0f;
	GPU_Rect spriteBottom;
	GPU_Rect spriteTop;
	float attack_timer = 0.f;

	Player(const vec& position, float angle);

	void Move(float dt);
	void Update(float dt);
	void Draw() const;

	bool is_derraping = false;
	float angle_before_derraping = 0.0f;
	float timer_derraping = 0.0f;
};
