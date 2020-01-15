#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"

struct EntityExampleSmall : public Entity, public EntS<EntityExampleSmall*>
{
	EntityExampleSmall()
	{
		anim.Ensure(AnimationType::ANIM_EXAMPLE);
		state = EntityState::MOVING;

		float angle = Random::rollf(360);

		pos.x = Random::roll(GameData::WINDOW_WIDTH * 99);
		pos.y = Random::roll(GameData::WINDOW_HEIGHT * 99);

		speed.x = cosf(Mates::DegsToRads(angle)) * (10 + Random::roll(80));
		speed.y = sinf(Mates::DegsToRads(angle)) * (10 + Random::roll(80));
	}

	void MoveEntityExample(int dt)
	{
		pos.x += speed.x * dt;
		pos.y += speed.y * dt;

		if (pos.x < 0 && speed.x < 0)
		{
			speed.x = -speed.x;
			pos.x = 0;
		}
		if (pos.x > GameData::WINDOW_WIDTH * 100 && speed.x > 0)
		{
			speed.x = -speed.x;
			pos.x = GameData::WINDOW_WIDTH * 100;
		}
		if (pos.y < 0 && speed.y < 0)
		{
			speed.y = -speed.y;
			pos.y = 0;
		}
		if (pos.y > GameData::WINDOW_HEIGHT * 100 && speed.y > 0)
		{
			speed.y = -speed.y;
			pos.y = GameData::WINDOW_HEIGHT * 100;
		}
	}


	void Update(int dt)
	{
		switch (state)
		{
		case EntityState::MOVING:
		{
			anim.Ensure(AnimationType::ANIM_EXAMPLE);
			MoveEntityExample(dt);
		} break;
		case EntityState::COLLIDED:
		{
			anim.Ensure(AnimationType::ANIM_EXAMPLE_COLLIDING);
			timer += dt;
			if (timer > 200)
			{
				state = EntityState::MOVING;
			}
			MoveEntityExample(dt);
		} break;
		}
	}

	void Draw(sf::Sprite& spr)
	{
		spr.setScale(0.5f, 0.5f);
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

