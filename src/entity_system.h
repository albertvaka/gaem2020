#pragma once

#include "game_data.h"
#include "mates.h"

#include "input.h"
#include "entity.h"
#include "collider.h"

#include "player.h"
#include "cadaver.h"
#include "cinta.h"
#include "spawner.h"

void UpdateEntities(int dt)
{
	//Collisions are handled in collider.h
	UpdateCollisions(dt);

	for (Player* e : EntS<Player>::getAll())
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





	EntS<Entity>::deleteNotAlive();
}

void DrawEntities(sf::Sprite& spr, sf::RenderWindow& window)
{



	EntS<Entity>::sort([](Entity* a, Entity* b) {
		return a->pos.y < b->pos.y;
	});

	for (Entity* e : EntS<Entity>::getAll())
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

	for (Entity* e : EntS<Entity>::getAll())
	{
		e->Draw(vao);
	}


	window.draw(vao,&texture);

	// define the position of the triangle's points



	// define the color of the triangle's points


	// no texture coordinates here, we'll see that later


}
