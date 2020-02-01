#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"

#include "input.h"
struct Player : public Entity, public EntS<Player>
{

	int player;
	Player(int id, vec position)
	{
		player = id;

		anim.Ensure(AnimationType::PLAYER_IDLE_DOWN);
		state = EntityState::MOVING;

		pos = position;
		speed.x = 0;
		speed.y = 0;
	}

	void Move(int dt)
	{
		float threshold = 50;
		sf::Vector2f anal = vec(GamePad::AnalogStick::Left.get(player, 30));

		//Player 0 can move with keyboard
		if (player == 0) {
			if (Keyboard::IsKeyPressed(GameKeys::UP))
			{
				anal.y = -100;
			}
			else if (Keyboard::IsKeyPressed(GameKeys::DOWN))
			{
				anal.y = 100;
			}
			if (Keyboard::IsKeyPressed(GameKeys::RIGHT))
			{
				anal.x = 100;

			}
			else if (Keyboard::IsKeyPressed(GameKeys::LEFT))
			{
				anal.x = -100;
			}
		}

		speed = anal * 0.3f;
		
		if (anal.x > 70)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::RIGHT;
		}
		else if (anal.x < -70)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::LEFT;
		} else if (anal.y > 70)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::DOWN;
		}
		else if (anal.y < -70)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::UP;
		}
		else {
			state = EntityState::IDLE;
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
		spr.setOrigin(0, 0);

		float x = pos.x / 100.0f;
		float y = pos.y / 100.0f;
		spr.setPosition(x, y);

		//spr.setOrigin(8, 8);

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

