#pragma once

#include "game_data.h"
#include "mates.h"

#include "input.h"
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

//#if _DEBUG
	Camera::MoveCameraWithArrows(50, dt / 1000.f);
	Camera::ChangeZoomWithPlusAndMinus(0.5f, dt / 1000.f);
//#endif

	EntS<Entity>::deleteNotAlive();
}

void DrawEntities(sf::Sprite& spr, sf::RenderWindow& window)
{
	window.clear();

	for (EntityExample* e : EntS<EntityExample>::getAll())
	{
		e->Draw(spr);
		window.draw(spr);
	}

	for (EntityExampleSmall* e : EntS<EntityExampleSmall>::getAll())
	{
		e->Draw(spr);
		window.draw(spr);
	}
}
