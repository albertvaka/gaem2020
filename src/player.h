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

		anim.Ensure(AnimationType::PLAYER_IDLE_DOWN);
		state = EntityState::MOVING;

		pos.x = Random::roll(GameData::WINDOW_WIDTH * 99);
		pos.y = Random::roll(GameData::WINDOW_HEIGHT * 99);
		speed.x = 0;
		speed.y = 0;
	}

	void Move(int dt)
	{
		float threshold = 50;
		sf::Vector2f anal = GamePad::AnalogStick::Left.get(player);

		if (anal.y > threshold || Keyboard::IsKeyPressed(GameKeys::UP))
		{
			dir = EntityDirection::UP;
			speed.y = 50;
		}
		else if (anal.y < -threshold || Keyboard::IsKeyPressed(GameKeys::DOWN))
		{
			dir = EntityDirection::DOWN;
			speed.y = -50;
		}
		else
		{
			speed.y = 0;
		}

		if (anal.x > threshold || Keyboard::IsKeyPressed(GameKeys::RIGHT)) 
		{
			dir = EntityDirection::RIGHT;
			speed.x = 50;
		} 
		else if (anal.x < -threshold || Keyboard::IsKeyPressed(GameKeys::LEFT)) 
		{
			dir = EntityDirection::RIGHT;
			speed.x = -50;
		} 
		else 
		{
			speed.x = 0;
		}

		pos.x += speed.x * dt;
		pos.y += speed.y * dt;
	}


	void Update(int dt)
	{
		Move(dt);
		switch (state)
		{
			case EntityState::IDLE:
			{

				if (dir == EntityDirection::UP)
				{
					anim.Ensure(AnimationType::PLAYER_IDLE_UP);
				}
				if (dir == EntityDirection::DOWN)
				{
					anim.Ensure(AnimationType::PLAYER_IDLE_DOWN);
				}
				if (dir == EntityDirection::LEFT)
				{
					anim.Ensure(AnimationType::PLAYER_IDLE_LEFT);
				}
				if (dir == EntityDirection::RIGHT)
				{
					anim.Ensure(AnimationType::PLAYER_IDLE_RIGHT);
				}

			} break;

			case EntityState::MOVING:
			{
				if (dir == EntityDirection::UP)
				{
					anim.Ensure(AnimationType::PLAYER_WALKING_UP);
				}
				if (dir == EntityDirection::DOWN)
				{
					anim.Ensure(AnimationType::PLAYER_WALKING_DOWN);
				}
				if (dir == EntityDirection::LEFT)
				{
					anim.Ensure(AnimationType::PLAYER_WALKING_LEFT);
				}
				if (dir == EntityDirection::RIGHT)
				{
					anim.Ensure(AnimationType::PLAYER_WALKING_RIGHT);
				}
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

