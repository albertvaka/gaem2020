#pragma once

#include "entity.h"

struct Lever : SortedDrawable, EntS<Lever>
{
	bool canPull = false;
	bool engineIsFinished = false;


	bool is_pushed_down = false;

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

		//Cablesitos
		spr.setTextureRect(sf::IntRect(0, 11 * 16, 16, 16));
		spr.setPosition(pos.x - 1.5f,  pos.y + 10);
		wnd.draw(spr);
		spr.setTextureRect(sf::IntRect(16, 11 * 16, 16, 16));
		spr.setPosition(pos.x + 14.5f, pos.y + 10);
		wnd.draw(spr);
				
		//Button Lever
		spr.setScale(0.75f, 0.75f);
		spr.setPosition(pos.x, pos.y);

		spr.setTextureRect(sf::IntRect(16, 112, 16, 16));

		if (is_pushed_down)
		{
			spr.setTextureRect(sf::IntRect(16 + 16, 112, 16, 16));
		}

		wnd.draw(spr);
		spr.setScale(1.f, 1.f);

	}

};

