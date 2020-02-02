#pragma once

#include <vector>
#include "rand.h"

#include "entity.h"
#include "lever.h"
#include "extremity.h"

static std::vector<int> v;

void initMesaVector()
{
	for (int i = 0; i < 5; i++)
	{
		v.push_back(i);
	}
	std::random_shuffle(v.begin(), v.end());
}

struct Mesa : public SortedDrawable, EntS<Mesa>
{

	enum Type {
		RIGHT_LEG,
		LEFT_LEG,
		RIGHT_ARM,
		LEFT_ARM,
		HEAD,
		SIZE
	};

	bool canLet;
	bool isEmpty;

	Cadaver* cadaver;
	Lever* lever;

	Type type;
	int currentPlayer;

	Mesa(vec position)
	{
		type = (Type) v.back();
		v.pop_back();

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

