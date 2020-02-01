#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Pared : public Entity, public EntS<Pared>
{

	Pared(vec position) {
		pos = position;
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		spr.setOrigin(0, 0);
		float x = pos.x / 100.0f;
		float y = pos.y / 100.0f;
		spr.setPosition(x, y);
<<<<<<< HEAD
		spr.setTextureRect(sf::IntRect(100, 100, 16, 16));
		
		window.draw(spr);
=======
		spr.setTextureRect(sf::IntRect(112, 112, 16, 16));
>>>>>>> deprecated map (before born)
	}


};