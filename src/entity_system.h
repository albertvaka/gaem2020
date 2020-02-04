#pragma once

#include "game_data.h"
#include "mates.h"

#include "input.h"
#include "entity.h"
#include "collider.h"

#include "player.h"
#include "cadaver.h"
#include "cinta.h"
#include "cleaner.h"
#include "spawner.h"
#include "lever.h"
#include "mesa.h"

void UpdateEntities(int dt)
{
	//Collisions are handled in collider.h
	UpdateCollisions(dt);



	for (Entity* e : EntS<Entity>::getAll())
	{
		e->Update(dt);
		if (e->anim.anim_type != AnimationType::NADA) {
			e->anim.Update(dt);
		}
	}

	for (Taca* e : EntS<Taca>::getAll())
	{
		e->Update(dt);
	}

	for (TextMolest* e : EntS<TextMolest>::getAll())
	{
		e->Update(dt);
	}

	int num_tacs = EntS<Taca>::getAll().size();
	int num_rumbs = EntS<Cleaner>::getAll().size();
	if (num_tacs/(num_rumbs + 1) > 1300 && num_rumbs < 3) {
		int spawners_count = EntS<CleanerSpawner>::getAll().size();

		int sp = Random::roll(0, spawners_count-1);

		EntS<CleanerSpawner>::getAll()[sp]->TreuElGos();
	}

	//if (EntS<Taca>::getAll().size() > )



	EntS<Taca>::deleteNotAlive();
	EntS<Entity>::deleteNotAlive();
}

void DrawEntities(sf::Sprite& spr, sf::RenderWindow& window)
{

	for (Taca* e : EntS<Taca>::getAll())
	{
		e->Draw(spr, window);
	}

	EntS<SortedDrawable>::sort([](SortedDrawable* a, SortedDrawable* b)
	{
		return a->pos.y < b->pos.y;
	});

	for (SortedDrawable* e : EntS<SortedDrawable>::getAll())
	{
		e->Draw(spr, window);
	}

	for (TextMolest* e : EntS<TextMolest>::getAll())
	{
		e->Draw(spr, window);
	}


}
/*
void DrawEntities(sf::Texture& texture, sf::RenderWindow& window)
{
	window.clear(sf::Color(100, 100, 200));

	sf::VertexArray vao(sf::Quads);
	EntS<Entity>::sort([](Entity* a, Entity* b) {
		return a->pos.y < b->pos.y;
	});

	for (SortedDrawable* e : EntS<SortedDrawable>::getAll())
	{
		e->Draw(vao);
	}



	window.draw(vao,&texture);

	// define the position of the triangle's points



	// define the color of the triangle's points


	// no texture coordinates here, we'll see that later


}
*/
