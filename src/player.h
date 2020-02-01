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

		//TODO
		if (Keyboard::IsKeyPressed(GameKeys::ACTION)) { }

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

		vec newPos= pos + speed * dt;
		Mates::xy tilePos = PosToTile(pos);
		Mates::xy tileNewPos = PosToTile(newPos);

		std::cout << tilePos.x << "," << tilePos.y << std::endl;
		std::cout << tileNewPos.x << "," << tileNewPos.y << std::endl << std::endl;

		if (passable[tilePos.x][tileNewPos.y]) {
			pos.y = newPos.y;
		}
		if (passable[tileNewPos.x][tilePos.y]) {
			pos.x = newPos.x;
		}

		for (Player* p : EntS<Player>::getAll()) {
			if (p == this) continue;
		}
	}

	static Mates::xy PosToTile(vec pos) {
		return { int(((pos.x / 400.f) + 8) / 16), int(((pos.y / 400.f) + 8) / 16) };
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

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		spr.setOrigin(0, 0);

		float x = pos.x / 100.0f;
		float y = pos.y / 100.0f;
		spr.setPosition(x, y);

		//spr.setOrigin(8, 8);

		spr.setTextureRect(anim.CurrentFrame());
		spr.setColor(sf::Color::White);

		window.draw(spr);
	}

};

