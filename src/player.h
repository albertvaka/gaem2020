#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


#include "input.h"

#include "cadaver.h"

struct Player : public Entity, public EntS<Player>
{

	int player;
	bool isCarrying;
	Extremity* extremity;
	Cadaver* cadaver;

	Player(int id, vec position)
	{
		player = id;

		isCarrying = false;

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
		if (Keyboard::IsKeyPressed(GameKeys::ACTION) && !isCarrying) 
		{
			if (extremity != NULL && cadaver == NULL)
			{
				isCarrying = true;
				extremity->isCarried = true;
				extremity->pos.x = pos.x;
				extremity->pos.y = pos.y;

			}
			else if (extremity == NULL && cadaver != NULL)
			{
				isCarrying = true;
				cadaver->isCarried = true;
				cadaver->pos.x = pos.x;
				cadaver->pos.y = pos.y;
			}
		}
		else if (Keyboard::IsKeyPressed(GameKeys::ACTION) && isCarrying)
		{
			if (extremity != NULL) {
				extremity->isCarried = false;
				extremity = NULL;
			}
			if (cadaver != NULL) {
				cadaver->isCarried = false;
				cadaver = NULL;
			}
		}

		//Player 0 can move with keyboard
		if (player == 0) 
		{
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


		speed = anal * 0.003f;
		
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
		else 
		{
			state = EntityState::IDLE;
		}

		auto oldPos = pos;
		bool moved = tryMove(dt);

		if (moved) 
		{
			for (Player* p : EntS<Player>::getAll()) 
			{
				if (p == this) continue;
				if (Collide(p->bounds(),this->bounds())) 
				{
					pos = oldPos;
					break;
				}
			}
		}
	}

	bool tryMove(int dt) 
	{
		bool moved = false;

		vec newPos = pos + speed * dt;
		
		int dd = 8 * 4 * 0.8;

		Mates::xy TL_x = PosToTile(vec(newPos.x, pos.y) + vec(-dd, -dd));
		Mates::xy TR_x = PosToTile(vec(newPos.x, pos.y) + vec(dd, -dd));
		Mates::xy BL_x = PosToTile(vec(newPos.x, pos.y) + vec(-dd, dd));
		Mates::xy BR_x = PosToTile(vec(newPos.x, pos.y) + vec(dd, dd));

		Mates::xy TL_y = PosToTile(vec(pos.x, newPos.y) + vec(-dd, -dd));
		Mates::xy TR_y = PosToTile(vec(pos.x, newPos.y) + vec(dd, -dd));
		Mates::xy BL_y = PosToTile(vec(pos.x, newPos.y) + vec(-dd, dd));
		Mates::xy BR_y = PosToTile(vec(pos.x, newPos.y) + vec(dd, dd));

		//Right
		if (speed.x > 0)
		{
			if (passable[TR_x.x][TR_x.y] && passable[BR_x.x][BR_x.y])
			{
				pos.x = newPos.x;
				moved = true;
			}
		}

		//Left
		if (speed.x < 0)
		{
			if (passable[TL_x.x][TL_x.y] && passable[BL_x.x][BL_x.y])
			{
				pos.x = newPos.x;
				moved = true;
			}
		}

		//Down
		if (speed.y > 0)
		{
			if (passable[BL_y.x][BL_y.y] && passable[BR_y.x][BR_y.y])
			{
				pos.y = newPos.y;
				moved = true;
			}
		}

		//Up
		if (speed.y < 0)
		{
			if (passable[TL_y.x][TL_y.y] && passable[TR_y.x][TR_y.y])
			{
				pos.y = newPos.y;
				moved = true;
			}
		}


		return moved;

	}

	static Mates::xy PosToTile(vec pos) 
	{
		return 
		{ 
			int(((pos.x / 4.f) + 8) / 16), 
			int(((pos.y / 4.f) + 8) / 16) 
		};
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

	Bounds bounds() {

		return Bounds(pos.x, pos.y, 16 * 4, 16*4);
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		spr.setOrigin(0, 0);

		auto a = spr.getScale();
		spr.setScale(5, 5);
		spr.setPosition(pos.x-8, pos.y - 18);
		
		//spr.setOrigin(8, 8);

		spr.setTextureRect(anim.CurrentFrame());
		spr.setColor(sf::Color::White);

		window.draw(spr);
		spr.setScale(a);

		bounds().Draw(window);
	}
};

