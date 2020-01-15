#pragma once

#include "game_data.h"
#include "mates.h"

#include "entity.h"
#include "super_factorio.h"

namespace EntS
{
	std::vector< std::vector<Entity*> > all_entities;

	void ResetEntities()
	{
		all_entities.resize(static_cast<int>(EntityType::COUNT));

		for (auto &v : all_entities)
		{
			v.clear();
		}
	}

	int SpawnEntity(EntityType type, Mates::xy)
	{
		Entity* ent = EntS::SuperFactorio(type);
		ent->type = type;
		ent->anim.Reset();
		all_entities[static_cast<int>(type)].push_back(ent);
		return ent->id;
	}
	

	bool Collision(Mates::xy a, Mates::xy b)
	{
		int COLLISION_SIZE = 1600;
		//rectangle colision
		return 
			(a.x < b.x + COLLISION_SIZE && a.x + COLLISION_SIZE > b.x &&
			 a.y < b.y + COLLISION_SIZE && a.y + COLLISION_SIZE > b.y);
	}

	void UpdateCollisions(int dt)
	{
		for (auto &vi :all_entities)
		{
			for (Entity* e1 :vi)
			{
				for (auto &vj : all_entities)
				{
					for (Entity* e2 : vj)
					{
						if ((e1->id != e2->id) && Collision(e1->pos, e2->pos))
						{
							e1->OnCollision(e2);
						}
					}
				}
			}
		}
	}

	void UpdateEntities(int dt)
	{
		UpdateCollisions(dt);

		for (auto &v : all_entities)
		{
			for (Entity* e : v)
			{
				e->Update(dt);
				e->anim.Update(dt);
			}
		}
	}

	void DrawEntities(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		std::vector< Entity* > draw_list;

		for (auto &v : all_entities)
		{
			for (Entity* e : v)
			{
				draw_list.push_back(e);
			}
		}

		std::sort(draw_list.begin(), draw_list.end(), [](Entity* a, Entity* b)
		{
			return a->pos.y < b->pos.y;
		});

		for (int i = 0; i < draw_list.size(); ++i)
		{
			draw_list[i]->Draw(spr);
			wnd.draw(spr);
		}

	}
}