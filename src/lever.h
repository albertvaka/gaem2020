#pragma once

#include "entity.h"

struct Player;

struct Lever : SortedDrawable, EntS<Lever>
{
	bool is_connected = false;
	bool is_ready = false;

	int is_pushed_timer = -1;

	int push = 0;
	const int PUSH_MAX = 2000;

	Player* player = nullptr;
	Buttonable* ent_connected = nullptr;

	Lever(vec position)
	{
		pos = position;
	}

	void Push()
	{
		push += 300;
		is_pushed_timer = 20;
	}

	void Hold()
	{
		is_pushed_timer = 20;
	}

	void Update(int dt)
	{

		if (!player)
		{
			is_ready = false;
		}
		if (push >= PUSH_MAX)
		{
			if (ent_connected) ent_connected->Operate();
			push = 0;
		}
		if (push > 0)
		{
			push -= dt;
			if (push < 0)
			{
				push = 0;
			}
		}


		if (is_pushed_timer > 0)
		{
			is_pushed_timer -= dt;
		}
		
		// Reset collision
		player = nullptr;
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		//Bounds(pos.x - 1, pos.y - 1, 2, 2).Draw(wnd);

		//Cablesitos

		int lvl = std::max(0, push);
		int cable_spr_dx = (int)(std::min(8.0f, float(push / (PUSH_MAX/8.0f)))) * 32;
		
		spr.setTextureRect(sf::IntRect(cable_spr_dx, 11 * 16, 16, 16));
		spr.setPosition(pos.x - 1.5f, pos.y + 10);
		wnd.draw(spr);
		spr.setTextureRect(sf::IntRect(16 + cable_spr_dx, 11 * 16, 16, 16));
		spr.setPosition(pos.x + 14.5f, pos.y + 10);
		wnd.draw(spr);

		//Button Lever
		spr.setScale(0.75f, 0.75f);
		spr.setPosition(pos.x, pos.y);


		const int TIMER_FLASH_LEVER = 250;
		int t = mainClock.getElapsedTime().asMilliseconds() % (TIMER_FLASH_LEVER*2);

		int dx_flash_effect = 0;
		int dx_pushed_effect = 0;

		if (is_pushed_timer > 0)
		{
			dx_pushed_effect = 16;
		}
		if (is_connected && (t > TIMER_FLASH_LEVER))
		{
			dx_flash_effect = 32;
		}
		
		spr.setTextureRect(sf::IntRect(16 + dx_flash_effect + dx_pushed_effect, 112, 16, 16));

		wnd.draw(spr);
		spr.setScale(1.f, 1.f);

		/*
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
		*/
	}

};

