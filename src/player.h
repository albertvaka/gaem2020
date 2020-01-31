#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"

#include "input.h"
struct Player : public Entity, public EntS<Player>
{

	int player;
	Player()
	{
		static int player_count;
		player = player_count++;

		anim.Ensure(AnimationType::ANIM_EXAMPLE);
		state = EntityState::MOVING;

		pos.x = Random::roll(GameData::WINDOW_WIDTH * 99);
		pos.y = Random::roll(GameData::WINDOW_HEIGHT * 99);
		speed.x = 0;
		speed.y = 0;
	}

	void Move(int dt)
	{
		float threshold = 50;
		auto anal = GamePad::AnalogStick::Left.get(player);
		if (anal.x > threshold || Keyboard::IsKeyPressed(GameKeys::RIGHT)) {
			speed.x = 50;
		} else if (anal.x < -threshold || Keyboard::IsKeyPressed(GameKeys::LEFT)) {
			speed.x = -50;
		} else {
			speed.x = 0;
		}
		if (anal.y > threshold || Keyboard::IsKeyPressed(GameKeys::UP)) {
			speed.y = 50;
		} else if (anal.y < -threshold || Keyboard::IsKeyPressed(GameKeys::DOWN)) {
			speed.y = -50;
		} else {
			speed.y = 0;
		}
		pos.x += speed.x * dt;
		pos.y += speed.y * dt;

	}


	void Update(int dt)
	{
		Move(dt);
		switch (state)
		{
			case EntityState::MOVING:
			{
				anim.Ensure(AnimationType::ANIM_EXAMPLE);
			} break;
		}
	}

	void Draw(sf::Sprite& spr)
	{
		spr.setScale(1.0f, 1.0f);
		spr.setOrigin(0, 0);

		float x = pos.x / 100.0f;
		float y = pos.y / 100.0f;
		spr.setPosition(x, y);

		spr.setOrigin(8, 8);

		spr.setTextureRect(anim.CurrentFrame());
		spr.setColor(sf::Color::White);

		//if (ent_type[id] == EntityType::ENTITY_EXAMPLE &&
			//	ent_state[id] == EntityState::COLLIDED)
		{
			//float sc = timer[id]/200.f;
			//spr.setScale(1.0f + sc*0.2f, 1.0f + sc * 0.2f);
		}
	}

};

