#include "player.h"

#include "animation2.h"
#include "anim_lib.h"
#include "rand.h"
#include "partsys.h"
#include "camera.h"
#include "collide.h"
#include "input.h"
#include "fxmanager.h"
#include "powerup.h"
#include "assets.h"

const float kMaxTurnRateRads = Angles::DegsToRads(90.f);
const float kRadius = 8.f;

Player::Player(const vec& position, float angle)
	: CircleEntity(position, kRadius)
	, anim(AnimLib::GOOMBA)
	, angle(angle)
{
}

void Player::Update(float dt)
{
	anim.Update(dt);

	vec heading = vel.Normalized();

	if (Input::IsPressed(0, GameKeys::LEFT)) {
		vel.x -= 400 * dt;
	}
	if (Input::IsPressed(0, GameKeys::RIGHT)) {
		vel.x += 400 * dt;
	}
	if (Input::IsPressed(0, GameKeys::UP)) {
		vel.y -= 400 * dt;
	}
	if (Input::IsPressed(0, GameKeys::DOWN)) {
		vel.y += 400 * dt;
	}

	vel *= 0.95f;

	for (PowerUp* e : SelfRegister<PowerUp>::GetAll()) {
		if (Collide(this, e)) {
			e->alive = false;
			FxManager::StartScreenshakePreset(FxManager::ScreenShakePreset::Electroshok);
		}
	}
	
	pos += vel * dt;
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
}
