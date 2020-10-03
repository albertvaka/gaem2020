#include "powerup.h"

#include "mates.h"
#include "assets.h"
#include "window.h"
#include "rand.h"
#include "assets.h"
#include "anim_lib.h"

extern float mainClock;

void PowerUp::Draw() const
{
	float y = 1.5f * sin(mainClock*2);

	Window::Draw(Assets::spritesheet, pos.x, pos.y - y)
		.withOrigin(8, 8)
		.withRect(AnimLib::POWERUP);

	if (Debug::Draw) {
		bounds().Draw();
	}
}
