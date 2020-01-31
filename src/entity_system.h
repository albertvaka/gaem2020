#pragma once

#include "game_data.h"
#include "mates.h"

#include "input.h"
#include "entity.h"
#include "collider.h"

#include "persona.h"

void UpdateEntities(int dt)
{
	//Collisions are handled in collider.h
	UpdateCollisions(dt);

	//for (EntityExample* e : EntS<EntityExample>::getAll())
	//{
	//	e->Update(dt);
	//	e->anim.Update(dt);
	//}

	//for (EntityExampleSmall* e : EntS<EntityExampleSmall>::getAll())
	//{
	//	e->Update(dt);
	//	e->anim.Update(dt);
	//}

	for (Persona* e : EntS<Persona>::getAll())
	{
		e->Update(dt);
		//e->anim.Update(dt);
	}

//#if _DEBUG
	Camera::MoveCameraWithArrows(50, dt / 1000.f);
	Camera::ChangeZoomWithPlusAndMinus(0.5f, dt / 1000.f);
//#endif

	if (Mouse::IsJustPressed()) {
		Entity* a = new EntityExample();
		a->pos.x = Mouse::GetPositionInWorld().x*100;
		a->pos.y = Mouse::GetPositionInWorld().y * 100;
	}

	EntS<Entity>::deleteNotAlive();
}

void DrawEntities(sf::Sprite& spr, sf::RenderWindow& window)
{
	window.clear();

	/*for (EntityExample* e : EntS<EntityExample>::getAll())
	{
		e->Draw(spr);
		window.draw(spr);
	}

	for (EntityExampleSmall* e : EntS<EntityExampleSmall>::getAll())
	{
		e->Draw(spr);
		window.draw(spr);
	}*/

	for (Persona* e : EntS<Persona>::getAll())
	{
		e->DrawRightLeg(spr);
		window.draw(spr);

		e->DrawLeftLeg(spr);
		window.draw(spr);

		e->DrawRightArm(spr);
		window.draw(spr);

		e->DrawLeftArm(spr);
		window.draw(spr);

		e->DrawHead(spr);
		window.draw(spr);

		e->DrawBody(spr);
		window.draw(spr);

	}
}
