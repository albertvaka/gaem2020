#pragma once

#include <vector>
#include "vec.h"
#include "selfregister.h"
#include "entity.h"
#include "window.h"
#include "mates.h"
#include "rand.h"

struct EnemyDoor : BoxEntity, SelfRegister<EnemyDoor>
{
	bool collide = false;
	vec speed;
	EnemyDoor() : BoxEntity(vec(16,16)) {
		float angle = Rand::rollf(360);
		speed.x = cosf(Mates::DegsToRads(angle)) * (10 + Rand::roll(80));
		speed.y = sinf(Mates::DegsToRads(angle)) * (10 + Rand::roll(80));

		pos.x = Rand::roll(Window::GAME_WIDTH );
		pos.y = Rand::roll(Window::GAME_HEIGHT);
	}

	void Update(float dt) {
		pos.x += speed.x * dt;
		pos.y += speed.y * dt;

		if (pos.x < 0 && speed.x < 0)
		{
			speed.x = -speed.x;
			pos.x = 0;
		}
		if (pos.x > Window::GAME_WIDTH && speed.x > 0)
		{
			speed.x = -speed.x;
			pos.x = Window::GAME_WIDTH;
		}
		if (pos.y < 0 && speed.y < 0)
		{
			speed.y = -speed.y;
			pos.y = 0;
		}
		if (pos.y > Window::GAME_HEIGHT && speed.y > 0)
		{
			speed.y = -speed.y;
			pos.y = Window::GAME_HEIGHT;
		}
	}
	void Draw() const {

		Window::Draw(Assets::hospitalTexture, pos).withRect(0, 16, 16, 16);
		if (collide)
		{
			Window::Draw(Assets::hospitalTexture, pos).withRect(0, 16, 16, 16).withColor(255,0,0);
		}
	}

};

