#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


#include "input.h"

#include "cadaver.h"

struct Player : public Entity, public EntS<Player>
{

	AnimationType animForPlayer(AnimationType anim) {
		int animint = int(anim);
		int diff = int(AnimationType::DOCTOR_WALKING_DOWN) - int(AnimationType::PLAYER_WALKING_DOWN);
		return AnimationType(animint+diff*player);
	}

	int player;
	bool isCarrying;
	Extremity* extremity;
	Cadaver* cadaver;

	Player(int id, vec position)
	{
		player = id;

		isCarrying = false;

		anim.Ensure(animForPlayer(AnimationType::PLAYER_IDLE_DOWN));
		state = EntityState::MOVING;

		pos = position;
		speed.x = 0;
		speed.y = 0;
	}

	void Move(int dt)
	{
		float deadZone = 20;
		sf::Vector2f anal = vec(GamePad::AnalogStick::Left.get(player, deadZone));

		//TODO
		if (Keyboard::IsKeyJustPressed(GameKeys::ACTION) || GamePad::IsButtonJustPressed(player, GamePad::Button::A) && !isCarrying) 
		{
			if (extremity != NULL)
			{
				isCarrying = true;
				extremity->isCarried = true;
				extremity->pos.x = pos.x;
				extremity->pos.y = pos.y;
			}
			else if (cadaver != NULL)
			{
				isCarrying = true;
				cadaver->carryCadaver(pos.x, pos.y, player);
			}
		}
		else if (Keyboard::IsKeyJustPressed(GameKeys::ACTION) || GamePad::IsButtonJustPressed(player, GamePad::Button::A) && isCarrying)
		{
			if (extremity != NULL) {
				isCarrying = false;
				extremity->isCarried = false;
				extremity = NULL;
			}
			if (cadaver != NULL) {
				isCarrying = false;
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


		speed = anal * 0.0015f;
		
		if (anal.x > deadZone)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::RIGHT;
		}
		else if (anal.x < -deadZone)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::LEFT;
		} else if (anal.y > deadZone)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::DOWN;
		}
		else if (anal.y < -deadZone)
		{
			state = EntityState::MOVING;
			dir = EntityDirection::UP;
		}
		else 
		{
			state = EntityState::IDLE;
		}

		auto oldPos = pos;
		bool moved = tryMove(dt/4.f) && tryMove(dt / 4.f) && tryMove(dt / 4.f) && tryMove(dt / 4.f);

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

	float boundingBoxSize = 10.f;
	bool tryMove(float dt)
	{
		bool moved = false;

		vec newPos = pos + speed * dt;
		
		float dd = boundingBoxSize/2;

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
			int((pos.x + 8) / 16), 
			int((pos.y + 8) / 16) 
		};
	}

	void Update(int dt)
	{
		Move(dt);

		if (isCarrying)
		{
			if (extremity != NULL) 
			{
				extremity->carryExtremity(pos.x, pos.y);
			}
			if (cadaver != NULL) 
			{
				cadaver->carryCadaver(pos.x, pos.y, player);
			}
		}

		switch (state)
		{
			case EntityState::IDLE:
			{

				if (dir == EntityDirection::UP)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_IDLE_UP));
				}
				if (dir == EntityDirection::DOWN)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_IDLE_DOWN));
				}
				if (dir == EntityDirection::LEFT)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_IDLE_LEFT));
				}
				if (dir == EntityDirection::RIGHT)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_IDLE_RIGHT));
				}

			} break;

			case EntityState::MOVING:
			{
				if (dir == EntityDirection::UP)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_WALKING_UP));
				}
				if (dir == EntityDirection::DOWN)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_WALKING_DOWN));
				}
				if (dir == EntityDirection::LEFT)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_WALKING_LEFT));
				}
				if (dir == EntityDirection::RIGHT)
				{
					anim.Ensure(animForPlayer(AnimationType::PLAYER_WALKING_RIGHT));
				}
			} break;
		}
	}

	Bounds bounds() {

		return Bounds(pos.x + (16 - boundingBoxSize)/2, pos.y + (16 - boundingBoxSize)/2, boundingBoxSize, boundingBoxSize);
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		bounds().Draw(window);

		spr.setOrigin(0, 0);

		auto a = spr.getScale();
		spr.setScale(1.25, 1.25);
		spr.setPosition(pos.x + 1.5f, pos.y - 4.f);
		
		//spr.setOrigin(8, 8);

		spr.setTextureRect(anim.CurrentFrame());
		spr.setColor(sf::Color::White);

		window.draw(spr);
		spr.setScale(a);

	}


	void Draw(sf::VertexArray &vertexArray)
	{
		float x = pos.x / 100.0f;
		float y = pos.y / 100.0f;
		x = x - 8;
		y = y - 18;
		sf::IntRect rect = anim.CurrentFrame();
		sf::Vector2u posStartInSpritesheet(rect.left,rect.top);
		sf::Vector2u sizeSprite(rect.width,rect.height);
		sf::Vector2u scale(5, 5);
		
		vertexArray.append(sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(posStartInSpritesheet.x, posStartInSpritesheet.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x + sizeSprite.x*scale.x, y), sf::Vector2f(posStartInSpritesheet.x + sizeSprite.x, posStartInSpritesheet.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x + sizeSprite.x*scale.x, y + sizeSprite.y*scale.y), sf::Vector2f(posStartInSpritesheet.x + sizeSprite.x, posStartInSpritesheet.y + sizeSprite.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x, y + sizeSprite.y*scale.y), sf::Vector2f(posStartInSpritesheet.x, posStartInSpritesheet.y + sizeSprite.y)));
		
		
		
		//window.draw(spr);
	}

};

