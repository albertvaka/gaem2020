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

	for (Player* e : EntS<Player>::getAll())
	{
		e->Update(dt);
		e->anim.Update(dt);
		e->actionButton.Update(dt);
	}
	for (Cleaner* e : EntS<Cleaner>::getAll())
	{
		e->Update(dt);
		e->anim.Update(dt);
	}
	for (Cadaver* e : EntS<Cadaver>::getAll())
	{
		e->Update(dt);
		//e->anim.Update(dt);
	}

	for (Cinta* e : EntS<Cinta>::getAll())
	{

		e->anim.Update(dt);
	}

	for (Spawner* e : EntS<Spawner>::getAll())
	{
		e->Update(dt);
	}

	for (Mesa* e : EntS<Mesa>::getAll())
	{
		e->Update(dt);
		e->anim.Update(dt);
	}
	for (Collector* e : EntS<Collector>::getAll())
	{
		e->Update(dt);
		e->anim.Update(dt);
	}

	for (Lever * e : EntS<Lever>::getAll())
	{
		e->Update(dt);
	}

	for (Taca* e : EntS<Taca>::getAll())
	{
		e->Update(dt);
	}

	EntS<Taca>::deleteNotAlive();
	EntS<Entity>::deleteNotAlive();
}

void DrawEntities(sf::Sprite& spr, sf::RenderWindow& window)
{

	for (Taca* e : EntS<Taca>::getAll())
	{
		e->Draw(spr, window);
	}

	EntS<SortedDrawable>::sort([](SortedDrawable* a, SortedDrawable* b) {
		return a->pos.y < b->pos.y;
	});

	for (SortedDrawable* e : EntS<SortedDrawable>::getAll())
	{
		e->Draw(spr, window);
	}

}
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
