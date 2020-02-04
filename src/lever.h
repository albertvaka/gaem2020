#pragma once

#include "entity.h"

struct Player;

struct Lever : SortedDrawable, EntS<Lever>
{

	const int LEVER_MAX_COUNTER = 2000;
	int leverCounter = 0;

	bool isFinished = false;
	bool isReady = false;

	Player* player = nullptr;

	bool is_pushed_down = false;

	Lever(vec position)
	{
		pos = position;
	}

	void Push() {
		leverCounter += 250;
		is_pushed_down = !is_pushed_down;
	}

	void Update(int dt)
	{
		if (!player)
		{
			is_pushed_down = false;
		}
		if (leverCounter >= LEVER_MAX_COUNTER)
		{
			isFinished = true;
			leverCounter = 0;
		}
		if (leverCounter > 0)
		{
			leverCounter -= dt;
			if (leverCounter < 0) {
				leverCounter = 0;
				is_pushed_down = false;
			}
		}
		// Reset collision
		player = nullptr;
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		//Bounds(pos.x - 1, pos.y - 1, 2, 2).Draw(wnd);

		//Cablesitos
		spr.setTextureRect(sf::IntRect(0, 11 * 16, 16, 16));
		spr.setPosition(pos.x - 1.5f, pos.y + 10);
		wnd.draw(spr);
		spr.setTextureRect(sf::IntRect(16, 11 * 16, 16, 16));
		spr.setPosition(pos.x + 14.5f, pos.y + 10);
		wnd.draw(spr);

		//Button Lever
		spr.setScale(0.75f, 0.75f);
		spr.setPosition(pos.x, pos.y);


		if (isReady && int(mainClock.getElapsedTime().asSeconds()) % 2){
			spr.setTextureRect(sf::IntRect(16 * 3, 112, 16, 16));
		}
		else {
				spr.setTextureRect(sf::IntRect(16, 112, 16, 16));
		}
		if (is_pushed_down)
		{
			spr.setTextureRect(sf::IntRect(16 + 16, 112, 16, 16));
		}

		wnd.draw(spr);
		spr.setScale(1.f, 1.f);

		if (leverCounter > 0)
		{
			const int size = 25;
			sf::IntRect leverBckRect = sf::IntRect(pos.x, pos.y - 16, size, 4);
			sf::RectangleShape leverBckShape = sf::RectangleShape();
			leverBckShape.setPosition(leverBckRect.left, leverBckRect.top);
			leverBckShape.setSize(sf::Vector2f(leverBckRect.width, leverBckRect.height));
			leverBckShape.setFillColor(sf::Color(73, 0, 0));

			wnd.draw(leverBckShape);

			int width = (leverCounter* size)/ LEVER_MAX_COUNTER;

			sf::IntRect leverFrontRect = sf::IntRect(pos.x, pos.y - 16, width, 4);
			sf::RectangleShape leverFrontShape = sf::RectangleShape();
			leverFrontShape.setPosition(leverFrontRect.left, leverFrontRect.top);
			leverFrontShape.setSize(sf::Vector2f(leverFrontRect.width, leverFrontRect.height));
			leverFrontShape.setFillColor(sf::Color(188, 0, 0));

			wnd.draw(leverFrontShape);
		}
	}

};

