#include "shot.h"

#include "anim_lib.h"
#include "camera.h"
#include "collide.h"
#include "assets.h"
#include "fxmanager.h"
#include "player.h"

void Shot::Update(float dt)
{
	pos += vel * dt;
	
	if (!Camera::GetBounds().Contains(pos)) {
		alive = false;
		return;
	}

}

void Shot::Draw() const
{
	Window::Draw(Assets::spritesheet, pos)
		.withRect(AnimLib::POWERUP)
		.withScale(0.5f)
		.withOrigin(AnimLib::POWERUP.w / 2, AnimLib::POWERUP.h / 2);

	if (Debug::Draw) {
		DrawBounds();
	}
}
