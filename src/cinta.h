#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"

struct Cinta : public SortedDrawable, public EntS<Cinta>
{
	const float push_speed = 0.01f;

	bool dbg_has_collided = false;

	Cinta(vec position, EntityDirection direction) 
	{
		pos = position + vec(8,8);
		anim.Ensure(AnimationType::BELT_RIGHT);
		state = EntityState::MOVING;
		dir = direction;
		size = vec(16, 16);
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd)
	{

		dbg_DrawBBox(wnd, dbg_has_collided? sf::Color::Green : sf::Color::Red);

		dbg_has_collided = false;
	}

	void Update(float dt)
	{

	}
	void Draw(sf::VertexArray &vertexArray)
	{
		/*
		float x = pos.x / 100.0f;
		float y = pos.y / 100.0f;
		sf::Vector2f posStartInSpritesheet(100.f, 100.f);
		sf::Vector2f sizeSprite(16.f, 16.f);
		//sf::Vector2f sizeSprite(64.f, 64.f);
		sf::Vector2u scale(4, 4);
		vertexArray.append(sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(posStartInSpritesheet.x, posStartInSpritesheet.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x + sizeSprite.x*scale.x, y), sf::Vector2f(posStartInSpritesheet.x + sizeSprite.x, posStartInSpritesheet.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x + sizeSprite.x*scale.x, y + sizeSprite.y*scale.y), sf::Vector2f(posStartInSpritesheet.x + sizeSprite.x, posStartInSpritesheet.y + sizeSprite.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x, y + sizeSprite.y*scale.y), sf::Vector2f(posStartInSpritesheet.x, posStartInSpritesheet.y + sizeSprite.y)));

		*/

	}

};

struct Cintable : public SortedDrawable, public EntS<Cintable>
{
	vec cinta_speed;
	EntityDirection cinta_dir;

	static void collision_entity_cinta(Cintable *ent, Cinta* cinta)
	{
		EntityDirection cdir = cinta->dir;

		if (ent->cinta_dir == EntityDirection::NONE)
		{
			ent->cinta_dir = cdir;
		}

		{
			ent->cinta_speed.x += (EntityDirection::RIGHT == cdir) * cinta->push_speed;
			ent->cinta_speed.x -= (EntityDirection::LEFT == cdir) * cinta->push_speed;
			ent->cinta_speed.y -= (EntityDirection::UP == cdir) * cinta->push_speed;
			ent->cinta_speed.y += (EntityDirection::DOWN == cdir) * cinta->push_speed;

			Mates::ClampMax(ent->cinta_speed.x, cinta->push_speed);
			Mates::ClampMin(ent->cinta_speed.x, -cinta->push_speed);

			Mates::ClampMax(ent->cinta_speed.y, cinta->push_speed);
			Mates::ClampMin(ent->cinta_speed.y, -cinta->push_speed);
		}

		cinta->dbg_has_collided = true;

	}


	void Draw(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		dbg_DrawBBox(wnd);
	}
};
