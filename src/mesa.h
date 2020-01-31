#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Mesa : public Entity, public EntS<Mesa>
{

	Mesa() {

	}

	void Update(int dt) { }


	void Draw(sf::Sprite& spr)
	{
		spr.setTextureRect(sf::IntRect(100, 100, 8, 8));
	}


};