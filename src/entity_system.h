#pragma once

#include "game_data.h"
#include "mates.h"

#include "entity.h"
#include "collider.h"

void UpdateEntities(int dt)
{
	//Collisions are handled in collider.h
	UpdateCollisions(dt);

	for (EntityExample* e : EntS<EntityExample>::getAll())
	{
		e->Update(dt);
		e->anim.Update(dt);
	}

	for (EntityExampleSmall* e : EntS<EntityExampleSmall>::getAll())
	{
		e->Update(dt);
		e->anim.Update(dt);
	}

	EntS<Entity>::deleteNotAlive();
}

void DrawEntities(sf::Sprite& spr, sf::RenderWindow& wnd)
{

	for (EntityExample* e : EntS<EntityExample>::getAll())
	{
		e->Draw(spr);
		wnd.draw(spr);
	}

	for (EntityExampleSmall* e : EntS<EntityExampleSmall>::getAll())
	{
		e->Draw(spr);
		wnd.draw(spr);
	}
}
