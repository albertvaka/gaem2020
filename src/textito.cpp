#include "shot.h"

#include "anim_lib.h"
#include "camera.h"
#include "collide.h"
#include "assets.h"
#include "fxmanager.h"
#include "player.h"
#include "textito.h"
#include "text.h"

const float kUpGoingSpeed = 300.0f;
const float kAliveTime = 2.0f;

void Textito::Update(float dt)
{
	pos += kUpGoingSpeed * dt * dir;
	timer += dt;

	if (timer > kAliveTime) {
		alive = false;
		return;
	}

}

void Textito::Draw() const
{
	Player* p = Player::instance();
	float angle = p->angle + 90;

	//screenText.SetOutlineColor(BLANCO) <- WTF NO ME FUNCIONA ESTO¿?

	vec realPos = pos;
	realPos.x += sin((double)timer*2.0f*M_PI * 3.0f) * 10.0f;

	float t = timer / kAliveTime;

	Window::Draw(screenText, realPos)
		.withScale(0.5f - (0.5f - 0.2f) * t)
		.withRotationDegs(angle)
		.withColor(192, 32, 32, (Uint8)(255 - (32*(t))));
}
