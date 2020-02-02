#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "player.h"

#include "input.h"

#include "cadaver.h"
#include "mesa.h"

struct Cleaner : public SortedDrawable, public EntS<Cleaner>
{

	AnimationType animForCleaner(AnimationType anim) {
		int animint = int(anim);
		int diff = int(AnimationType::DOCTOR_WALKING_DOWN) - int(AnimationType::PLAYER_WALKING_DOWN);
		return AnimationType(animint + diff * 0);
	}
	
	Animation actionButton;

	float decisionCounter = 1000.f;
	Cleaner(vec position)
	{


		anim.Ensure(animForCleaner(AnimationType::PLAYER_IDLE_DOWN));
		actionButton.Ensure(AnimationType::BUTTON_A_PRESS);

		state = EntityState::MOVING;

		pos = position;
		speed.x = 0;
		speed.y = 0;
	}
	
	void Move(int dt)
	{
		
		decisionCounter -= dt;
		if (decisionCounter < 0) {
			decisionCounter = 1000.f;
			int newdir = Random::roll(1);
			switch (newdir)
			{
			case 0:
				speed.x = 0.05;
				break;
			case 1:
				speed.x = -0.05;
				break;
			}
			newdir = Random::roll(1);
			switch (newdir)
			{
			case 0:
				speed.y = 0.05;
				break;
			case 1:
				speed.y = -0.05;
				break;
			}
			if (speed.x > 0)
			{
				state = EntityState::MOVING;
				dir = EntityDirection::RIGHT;
			}
			else if (speed.x < 0)
			{
				state = EntityState::MOVING;
				dir = EntityDirection::LEFT;

			}
			else if (speed.y > 0)
			{
				state = EntityState::MOVING;
				dir = EntityDirection::DOWN;
			}
			else if (speed.y < 0)
			{
				state = EntityState::MOVING;
				dir = EntityDirection::UP;
			}
			else
			{
				state = EntityState::IDLE;
			}
		}
		auto oldPos = pos;

		

		bool moved = tryMove(dt/4.f) && tryMove(dt / 4.f) && tryMove(dt / 4.f) && tryMove(dt / 4.f);


		if (moved) 
		{
			for (Cleaner* p : EntS<Cleaner>::getAll())
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
			if (passableCleaner[TR_x.x][TR_x.y] && passableCleaner[BR_x.x][BR_x.y])
			{
				pos.x = newPos.x;
				moved = true;
			}
		}

		//Left
		if (speed.x < 0)
		{
			if (passableCleaner[TL_x.x][TL_x.y] && passableCleaner[BL_x.x][BL_x.y])
			{
				pos.x = newPos.x;
				moved = true;
			}
		}

		//Down
		if (speed.y > 0)
		{
			if (passableCleaner[BL_y.x][BL_y.y] && passableCleaner[BR_y.x][BR_y.y])
			{
				pos.y = newPos.y;
				moved = true;
			}
		}

		//Up
		if (speed.y < 0)
		{
			if (passableCleaner[TL_y.x][TL_y.y] && passableCleaner[TR_y.x][TR_y.y])
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

		

		switch (state)
		{
			case EntityState::IDLE:
			{

				if (dir == EntityDirection::UP)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_IDLE_UP));
				}
				if (dir == EntityDirection::DOWN)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_IDLE_DOWN));
				}
				if (dir == EntityDirection::LEFT)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_IDLE_LEFT));
				}
				if (dir == EntityDirection::RIGHT)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_IDLE_RIGHT));
				}

			} break;

			case EntityState::MOVING:
			{
				if (dir == EntityDirection::UP)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_WALKING_UP));
				}
				if (dir == EntityDirection::DOWN)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_WALKING_DOWN));
				}
				if (dir == EntityDirection::LEFT)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_WALKING_LEFT));
				}
				if (dir == EntityDirection::RIGHT)
				{
					anim.Ensure(animForCleaner(AnimationType::PLAYER_WALKING_RIGHT));
				}
			} break;
		}
	}

	Bounds bounds() {

		return Bounds(pos.x + (16 - boundingBoxSize)/2, pos.y + (16 - boundingBoxSize)/2, boundingBoxSize, boundingBoxSize);
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		//bounds().Draw(window);

		auto a = spr.getScale();
		spr.setScale(1.25, 1.25);
		spr.setPosition(pos.x + 1.5f, pos.y - 4.f);
		
		spr.setTextureRect(anim.CurrentFrame());

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

