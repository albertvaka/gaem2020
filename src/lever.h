#pragma once

#include "entity.h"


struct Lever : public SortedDrawable, public EntS<Lever>
{
	bool canPull = false;
	bool engineIsFinished = false;

	Lever(vec position)
	{
		pos.x = position.x - 16;
		pos.y = position.y - 42;
	}

	void Update(int dt)
	{
		
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		spr.setScale(0.75f, 0.75f);
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(sf::IntRect(16, 112, 16, 16));
		wnd.draw(spr);
		spr.setScale(1.f, 1.f);
	}
};

