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

	vec a = entity_a->pos - vec(sz_a / 2);
	vec b = entity_b->pos - vec(sz_b / 2);

	//rectangle colision
	return	(a.x < (b.x + sz_b.x)) &&
			((a.x + sz_a.x) > b.x) &&
			(a.y < (b.y + sz_b.y)) &&
			((a.y + sz_a.y) > b.y);
}

bool Collision(Cintable* entity_a, Cinta* entity_b)
{
	vec sz_a = entity_a->sizePlz();
	vec sz_b = entity_b->size;

	vec a = entity_a->positionPlz() - vec(sz_a / 2);
	vec b = entity_b->pos - vec(sz_b / 2);

	//rectangle colision
	return	(a.x < (b.x + sz_b.x)) &&
			((a.x + sz_a.x) > b.x) &&
			(a.y < (b.y + sz_b.y)) &&
			((a.y + sz_a.y) > b.y);
}

bool Collision(Cintable* entity_a, Cleaner* entity_b)
{
	vec sz_a = entity_a->sizePlz();
	vec sz_b = entity_b->size;

	vec a = entity_a->positionPlz() - vec(sz_a / 2);
	vec b = entity_b->pos - vec(sz_b / 2);

	//rectangle colision
	return	(a.x < (b.x + sz_b.x)) &&
			((a.x + sz_a.x) > b.x) &&
			(a.y < (b.y + sz_b.y)) &&
			((a.y + sz_a.y) > b.y);
}

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

void collision_player_extremity(Player* player, Extremity* extremity) {
	if (!player->isCarrying && !extremity->isCarried && !extremity->isLet) {
		player->extremity = extremity;
	}
}

void collision_player_cadaver(Player* player, Cadaver* cadaver) {
	if (!player->isCarrying && !cadaver->isCarried && !cadaver->isLet) {
		player->cadaver = cadaver;
	}
}

void collision_player_mesa(Player* player, Mesa* mesa) {
	player->mesa = mesa;
}

void collision_player_collector(Player* player, Collector* coll) {
	player->collector = coll;
}

void collision_player_lever(Player* player, Lever* lever) {
	player->lever = lever;
	lever->player = player;
}

void collision_entity_cinta(Cintable *ent, Cinta* cinta) {

	if (ent->prevCintaDirection == cinta->dir || ent->prevCintaDirection == EntityDirection::NONE) {
		ent->currCintaDirection = cinta->dir;
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

void collision_clean_taques(Taca* t, Cleaner* c)
{
	c->Absorbed();
	t->AbsorbByRoomba(c);
}

void collision_stop_cleaner(Player* _, Cleaner* c)
{
	c->speed.x = 0;
	c->speed.y = 0;

	c->pos = c->oldPos;
	c->stuck = true;

}

void coll_ent_doorsensor(Entity* _, DoorSensor* ds)
{
	ds->activated = true;
}

void coll_bullet_cadaver(Bullet* b, Cadaver* c) {
	if (c->isLet || c->isCarried) {
		return;
	}
	c->alive = false;
	b->explode = true;
	b->pos = c->pos;
	for (int i = 0; i < 100; i++) {
		c->SpawnBlood();
	}
}

void UpdateCollisions(int dt)
{
	for (Player* player : EntS<Player>::getAll())
	{
		if (!player->isCarrying) {
			player->cadaver = NULL;
		}
		if (!player->isCarrying) {
			player->extremity = NULL;
		}
		player->collector = NULL;
		player->mesa = NULL;
		player->lever = NULL;
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
	collide(EntS<Cintable>::getAll(), EntS<Cinta>::getAll(), collision_entity_cinta);
	collide(EntS<Cadaver>::getAll(), EntS<Detector>::getAll(), collision_cadaver_spawner);
	collide(EntS<Cadaver>::getAll(), EntS<Despawner>::getAll(), collision_cadaver_despawner);
	collide(EntS<Extremity>::getAll(), EntS<Despawner>::getAll(), collision_entity_despawner);
	collide(EntS<Cleaner>::getAll(), EntS<Despawner>::getAll(), collision_entity_despawner);
	collide(EntS<Player>::getAll(), EntS<DoorSensor>::getAll(), coll_ent_doorsensor);
	collide(EntS<Cleaner>::getAll(), EntS<DoorSensor>::getAll(), coll_ent_doorsensor);
	collide(EntS<Bullet>::getAll(), EntS<Cadaver>::getAll(), coll_bullet_cadaver);
}
