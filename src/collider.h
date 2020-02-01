#pragma once

#include "selfregister.h"
#include "player.h"
#include "cadaver.h"
#include "mesa.h"
#include "cinta.h"
#include "spawner.h"
#include <functional>

bool Collision(Entity* entity_a, Entity* entity_b)
{

	float COLLISION_SIZE = 16;

	vec a = entity_a->pos;
	vec b = entity_b->pos;

	//rectangle colision
	return
		(a.x < b.x + COLLISION_SIZE && a.x + COLLISION_SIZE > b.x &&
			a.y < b.y + COLLISION_SIZE && a.y + COLLISION_SIZE > b.y);
}

template <typename T, typename U, typename Z, typename Y>
void collide(const std::vector<T*>& setA, const std::vector<U*>& setB, void (*callback)(Y*, Z*)) 
{
	size_t sa = setA.size();
	for (size_t i = 0; i < sa; ++i)
	{
		T* a = setA[i];
		size_t sb = setB.size();
		for (size_t j = 0; j < sb; ++j)
		{
			U* b = setB[j];
			if ((void*)a == (void*)b) continue;
			if (Collision(a, b)) 
			{
				callback(a, b);
			}
		}
	}
}

void collision_player_extremity(Player* player, Extremity* extremity) {
	if (!player->isCarrying && !extremity->isCarried) {
		player->extremity = extremity;
		extremity->isCarriable = true;
	}
}

void collision_player_cadaver(Player* player, Cadaver* cadaver) {
	if (!player->isCarrying && !cadaver->isCarried) {
		player->cadaver = cadaver;
		cadaver->isCarriable = true;
	}
}

void collision_player_mesa(Player* player, Mesa* mesa) {
	if (player->cadaver != NULL)
	{
		mesa->canLet = true;
		mesa->cadaver = player->cadaver;
		mesa->currentPlayer = player->player;
		player->mesa = mesa;


	}
}

void collision_entity_cinta(Entity* ent, Cinta* cinta) {

	if (ent->prevCintaDirection == cinta->dir || ent->prevCintaDirection == EntityDirection::NONE) {
		ent->currCintaDirection = cinta->dir;
	}

}

void collision_cadaver_spawner(Cadaver* ent, Spawner* spawner) {

	spawner->empty = false;

}

void UpdateCollisions(int dt) 
{

	for (Player * player : EntS<Player>::getAll())
	{
		if (!player->isCarrying) {
			player->extremity = NULL;
			player->cadaver = NULL;
			player->mesa = NULL;
		}
	}

	for (Extremity * extremity : EntS<Extremity>::getAll())
	{
		extremity->isCarriable = false;
	}

	for (Cadaver * cadaver : EntS<Cadaver>::getAll())
	{
		cadaver->isCarriable = false;
	}

	for (Mesa * mesa : EntS<Mesa>::getAll())
	{
		mesa->canLet = false;
		mesa->currentPlayer = -1;
	}

	// If A collides with B, call collision_callback
	collide(EntS<Player>::getAll(), EntS<Extremity>::getAll(), collision_player_extremity);
	collide(EntS<Player>::getAll(), EntS<Cadaver>::getAll(), collision_player_cadaver);
	collide(EntS<Player>::getAll(), EntS<Mesa>::getAll(), collision_player_mesa);
	collide(EntS<Player>::getAll(), EntS<Cinta>::getAll(), collision_entity_cinta);
	collide(EntS<Cadaver>::getAll(), EntS<Cinta>::getAll(), collision_entity_cinta);
	collide(EntS<Cadaver>::getAll(), EntS<Spawner>::getAll(), collision_cadaver_spawner);


}
