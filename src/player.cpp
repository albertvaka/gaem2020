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

constexpr const float kAccel = 150.f; // in pixels/second^2
constexpr const float kBrake = 140.f; 
constexpr const float kFriction = 40.f; // brake force when not accelerating

constexpr const float kMaxSpeed = 300.f; // in pixels/second

const float spriteScale = 1.5f;

const float kRadius = 8.f;

Player::Player(const vec& position, float angle)
	: CircleEntity(position, kRadius)
	, anim(AnimLib::GOOMBA)
	, angle(angle)
{
	int top = Rand::roll(10);
	int topX = top % 6;
	int topY = top / 6;
	spriteTop = {topX * 32.f, topY * 32.f, 32, 32};

	int bottom = Rand::roll(10);
	int bottomX = top % 6;
	int bottomY = top / 6;
	spriteBottom = { bottomX * 32.f, bottomY * 32.f, 32, 32 };
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
	Window::DrawPrimitive::Line(pos, pos + (vel * 0.2), 2, { 255,255,0,255 });
	
	Window::Draw(Assets::spritesheet, pos)
		.withRect(spriteBottom)
		.withScale(spriteScale)
		.withRotationDegs(angle+90)
		.withOrigin(16, 16);

	Window::Draw(Assets::spritesheet, pos)
		.withRect(spriteTop)
		.withScale(spriteScale)
		.withRotationDegs(angle + 90)
		.withOrigin(16, 16);

	if (Debug::Draw) {
		pos.Debuggerino();
		DrawBounds();
	}

}
