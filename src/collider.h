#pragma once

#include "selfregister.h"
#include "player.h"
#include "cadaver.h"
#include "mesa.h"
#include "cinta.h"
#include "spawner.h"
#include "popupText.h"
#include "lever.h"
#include <functional>
#include "door.h"
#include "cleaner.h"

bool Collision(Entity* entity_a, Entity* entity_b)
{
	vec sz_a = entity_a->size;
	vec sz_b = entity_b->size;

	vec a = entity_a->pos;
	vec b = entity_b->pos;

	//rectangle colision
	return	(a.x < (b.x + sz_b.x)) && 
			((a.x + sz_a.x) > b.x) &&
			(a.y < (b.y + sz_b.y)) && 
			((a.y + sz_a.y) > b.y);
}

bool CollisionCorners(Entity* entity_a, Entity* entity_b)
{
	vec sz_a = entity_a->size;
	vec sz_b = entity_b->size;

	vec a = entity_a->pos;
	vec b = entity_b->pos;

	//rectangle colision

	vec p[4] =
	{
		vec(a.x - sz_a.x / 2, a.y - sz_a.x / 2),
		vec(a.x - sz_a.x / 2, a.y + sz_a.x / 2),
		vec(a.x + sz_a.x / 2, a.y - sz_a.x / 2),
		vec(a.x + sz_a.x / 2, a.y + sz_a.x / 2)
	};

	for (int i = 0; i < 4; ++i)
	{
		bool inside =
			(p[i].x >= (b.x - sz_b.x / 2)) &&
			(p[i].x <= b.x + sz_b.x / 2) &&
			(p[i].y >= b.y - sz_b.y / 2) &&
			(p[i].y <= b.y + sz_b.y / 2);

		if (inside) return true;
	}
	
	return false;
}
/*
bool Collision(Cintable* entity_a, Cinta* entity_b)
{
	float COLLISION_SIZE = 16;

	vec a = entity_a->positionPlz();
	vec b = entity_b->pos;

	//rectangle colision
	return
		(a.x < b.x + 16 && a.x + COLLISION_SIZE > b.x &&
			a.y < b.y + 16 && a.y + COLLISION_SIZE > b.y);
}

bool Collision(Cintable* entity_a, Cleaner* entity_b)
{

	float COLLISION_SIZE = 16;

	vec a = entity_a->positionPlz();
	vec b = entity_b->pos;

	//rectangle colision
	return
		(a.x < b.x + 16 && a.x + COLLISION_SIZE > b.x &&
			a.y < b.y + 16 && a.y + COLLISION_SIZE > b.y);
}
*/
template <typename S, typename E, typename X, typename Y>
void collide(const std::vector<S*>& setA, const std::vector<E*>& setB, void (*callback)(X*, Y*)) 
{
	size_t sa = setA.size();
	for (size_t i = 0; i < sa; ++i)
	{
		S* a = setA[i];
		size_t sb = setB.size();
		for (size_t j = 0; j < sb; ++j)
		{
			E* b = setB[j];
			if ((void*)a == (void*)b) continue;
			if (Collision(a, b)) 
			{
				callback(a, b);
			}
		}
	}
}

template <typename S, typename E, typename X, typename Y>
void collide_corners_vs_box(const std::vector<S*>& v_box_with_corners, const std::vector<E*>& v_boxes, void(*callback)(X*, Y*))
{
	size_t sa = v_box_with_corners.size();
	for (size_t i = 0; i < sa; ++i)
	{
		S* a = v_box_with_corners[i];
		size_t sb = v_boxes.size();
		for (size_t j = 0; j < sb; ++j)
		{
			E* b = v_boxes[j];
			if ((void*)a == (void*)b) continue;


			if (CollisionCorners(a, b))
			{
				callback(a, b);
			}


		}
	}
}

void collision_player_extremity(Player* player, Extremity* extremity) {
	if (!player->isCarrying && !extremity->isCarried && !extremity->isLet) {
		player->extremity = extremity;
		player->isExtremityCarriable = true;
	}
}

void collision_player_cadaver(Player* player, Cadaver* cadaver) {
	if (!player->isCarrying && !cadaver->isCarried) {
		player->cadaver = cadaver;
		player->isCadaverCarriable = true;
	}
}

void collision_player_mesa(Player* player, Mesa* mesa) {
	if (player->cadaver != NULL)
	{
		mesa->canLet = true;
		mesa->cadaver = player->cadaver;
		mesa->currentPlayer = player;
		player->mesa = mesa;
	}
}

void collision_player_collector(Player* player, Collector* coll) {
	if (player->collector == NULL)
	{
		coll->currentPlayer = player;
		player->collector = coll;
	}
}

void collision_player_lever(Player* player, Lever* lever) {
	if (lever->canPull)
	{
		player->isLeverPullable = true;
		player->lever = lever;
	}
}


void collision_cadaver_spawner(Cadaver* ent, Detector* detector) {
	if (detector->spawner)
	{
		detector->spawner->empty = false;
	}
	

}

void collision_entity_despawner(Entity* e, Despawner* _) {
	e->alive = false;
}

void collision_cadaver_despawner(Cadaver* e, Despawner* _) 
{
	if (e->alive) 
	{
		if(e->IsOk())
		{
			new TextMolest(vec(GameData::WINDOW_WIDTH/2, GameData::WINDOW_HEIGHT/2), TextMolest::GOOD);
			countGoods += 1;
		}
		else 
		{
			new TextMolest(vec(GameData::WINDOW_WIDTH / 2, GameData::WINDOW_HEIGHT / 2), TextMolest::BAD);
			countBads += 1;
		}
	}
	e->alive = false;
	
}

void collision_clean_taques(Taca* t, Cleaner* c) {
	t->alive = false;
}

void collision_stop_cleaner(Player* _, Cleaner* c) {
	c->speed.x = 0;
	c->speed.y = 0;

	c->pos = c->oldPos;
	c->stuck = true;

}

void coll_ent_doorsensor(Entity* _, DoorSensor* ds)
{
	ds->activated = true;
}


void UpdateCollisions(int dt) 
{

	for (Player * player : EntS<Player>::getAll())
	{
		player->collector = NULL;
		if (!player->isCarrying) 
		{
			player->extremity = NULL;
			player->cadaver = NULL;
			player->mesa = NULL;
			player->lever = NULL;

			player->isCadaverCarriable = false;
			player->isExtremityCarriable = false;
			player->isLeverPullable = false;

		}
	}

	for (Mesa * mesa : EntS<Mesa>::getAll())
	{
		mesa->canLet = false;
		mesa->currentPlayer =  nullptr;
	}

	for (Collector* mesa : EntS<Collector>::getAll())
	{
		mesa->currentPlayer = nullptr;
	}

	// If A collides with B, call collision_callback
	collide(EntS<Taca>::getAll(), EntS<Cleaner>::getAll(), collision_clean_taques);
	collide(EntS<Player>::getAll(), EntS<Cleaner>::getAll(), collision_stop_cleaner);
	collide(EntS<Player>::getAll(), EntS<Extremity>::getAll(), collision_player_extremity);
	collide(EntS<Player>::getAll(), EntS<Cadaver>::getAll(), collision_player_cadaver);
	collide(EntS<Player>::getAll(), EntS<Mesa>::getAll(), collision_player_mesa);
	collide(EntS<Player>::getAll(), EntS<Lever>::getAll(), collision_player_lever);
	collide(EntS<Player>::getAll(), EntS<Collector>::getAll(), collision_player_collector);
	//collide(EntS<Player>::getAll(), EntS<Cinta>::getAll(), collision_entity_cinta);

	
	for (Cintable* c : EntS<Cintable>::getAll())
	{
		c->cinta_speed = vec(0, 0);
	}
	collide_corners_vs_box(EntS<Cintable>::getAll(), EntS<Cinta>::getAll(), &Cintable::collision_entity_cinta);

	collide(EntS<Cadaver>::getAll(), EntS<Detector>::getAll(), collision_cadaver_spawner);
	collide(EntS<Cadaver>::getAll(), EntS<Despawner>::getAll(), collision_cadaver_despawner);
	collide(EntS<Cleaner>::getAll(), EntS<Despawner>::getAll(), collision_entity_despawner);

	collide(EntS<Player>::getAll(), EntS<DoorSensor>::getAll(), coll_ent_doorsensor);
	collide(EntS<Cleaner>::getAll(), EntS<DoorSensor>::getAll(), coll_ent_doorsensor);


}
