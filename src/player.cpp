#include "player.h"

#include "animation2.h"
#include "anim_lib.h"
#include "rand.h"
#include "partsys.h"
#include "mates.h"
#include "camera.h"
#include "collide.h"
#include "input.h"
#include "fxmanager.h"
#include "powerup.h"
#include "assets.h"

constexpr const float kTurnRate = 100.f; // in degrees/second

constexpr const float kAccel = 70.f; // in pixels/second^2
constexpr const float kBrake = 70.f; 
constexpr const float kFriction = 20.f; // brake force when not accelerating

constexpr const float kMaxSpeed = 140.f; // in pixels/second

const float kRadius = 8.f;

Player::Player(const vec& position, float angle)
	: CircleEntity(position, kRadius)
	, anim(AnimLib::GOOMBA)
	, angle(angle)
{
}

void Player::Move(float dt) 
{

	if (Input::IsPressed(0, GameKeys::LEFT)) {
		angle -= kTurnRate * dt;
	}
	if (Input::IsPressed(0, GameKeys::RIGHT)) {
		angle += kTurnRate * dt;
	}

	if (angle > 360) angle -= 360;
	else if (angle < 0) angle += 360;

	vec heading = vec::FromAngleDegs(angle);

	if (Input::IsPressed(0, GameKeys::UP)) {
		speed += kAccel * dt;
	}
	else if (Input::IsPressed(0, GameKeys::DOWN)) {
		speed -= kBrake * dt;
	}
	else {
		speed -= kFriction * dt;
	}
	Mates::Clamp(speed, 0, kMaxSpeed);

	vel = heading * speed;

	pos += vel * dt;
}


void Player::Update(float dt)
{
	anim.Update(dt);

	Move(dt);

	for (PowerUp* e : SelfRegister<PowerUp>::GetAll()) {
		if (Collide(this, e)) {
			e->alive = false;
			FxManager::StartScreenshakePreset(FxManager::ScreenShakePreset::Electroshok);
		}
	}

}

void Player::Draw() const
{
	const GPU_Rect& rect = anim.GetCurrentRect();
	Window::Draw(Assets::spritesheet, pos)
		.withRect(rect)
		.withOrigin(rect.w/2, rect.h/2);
	
	if (Debug::Draw) {
		pos.Debuggerino();
		DrawBounds();
	}

	Window::DrawPrimitive::Line(pos, pos + vel, 2, { 255,255,0,255 });
}
