#pragma once

#include "entity.h"
#include "lever.h"

#include "extremity.h"

struct Mesa : public Entity, EntS<Mesa>
{

	enum type {
		RIGHT_LEG,
		LEFT_LEG,
		RIGHT_ARM,
		LEFT_ARM,
		HEAD
	};

	bool canLet;
	bool isEmpty;

	Cadaver* cadaver;
	Lever* lever;

	int type;
	int currentPlayer;

	Mesa(vec position)
	{
		pos = position;
		canLet = false;
		isEmpty = true;

		anim.Ensure(AnimationType::POKEMON);
		lever = new Lever(pos);
	}

	void Update(int dt)
	{
		if (lever->engineIsFinished || isEmpty)
		{
			lever->canPull = false;
		}
		else
		{
			lever->canPull = true;
		}

	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		//if (canLet || (currentPlayer >= 0 && !isEmpty)) 
		//{
		//	sf::RectangleShape shape;
		//	shape.setFillColor(sf::Color::Transparent);
		//	shape.setOutlineColor(sf::Color::Yellow);
		//	shape.setOutlineThickness(1);
		//	shape.setPosition(pos.x, pos.y);
		//	shape.setSize(sf::Vector2f(16, 16));

		//	wnd.draw(shape);
		//}

		spr.setTextureRect(anim.CurrentFrame());
		spr.setPosition(pos.x - 7, pos.y - 16);
		wnd.draw(spr);

		if (lever->engineIsFinished)
		{
			//TODO:: RAYOS Y RETRUECANOS
		}
	}

};

