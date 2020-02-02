#pragma once

#include <vector>
#include "rand.h"

#include "entity.h"
#include "lever.h"
#include "extremity.h"

struct Mesa;
struct Collector;

void UpdateCollector(Collector*, int);

struct Collector : public SortedDrawable, EntS<Collector>
{
	ExtremityType type;
	int player = -1;
	Mesa* mesa = nullptr;
	int currentPlayer;

	bool mesa_was_empty = true;

	Collector(vec position, ExtremityType et)
	{
		type = et;
		pos = position;
		anim.Ensure(AnimationType::CAPSULE_CLOSED);
		anim.loopable = false;
	}

	void Update(int dt) 
	{
		UpdateCollector(this, dt);
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		spr.setScale(1, 1);
		spr.setTextureRect(anim.CurrentFrame());
		spr.setPosition(pos.x, pos.y);
		wnd.draw(spr);
		spr.setScale(1, 1);
	}

};

struct Mesa : public SortedDrawable, EntS<Mesa>
{
	bool canLet;
	bool isEmpty;

	Cadaver* cadaver = nullptr;
	Lever* lever = nullptr;


	ExtremityType type;
	int currentPlayer = -1;
	Collector* collector = nullptr;

	Mesa(vec position, ExtremityType et)
	{
		type = et;
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

		spr.setScale(1.25f, 1.25f);
		spr.setTextureRect(anim.CurrentFrame());
		spr.setPosition(pos.x - 11.2f, pos.y - 22.5f);
		wnd.draw(spr);
		spr.setScale(1,1);

		if (cadaver && lever->engineIsFinished)
		{
			if (cadaver->HasExtremity(type)) 
			{
				cadaver->DeatachExtremity(type, collector->pos);
			}
	
			//TODO:: RAYOS Y RETRUECANOS
		}
	}

};



void UpdateCollector(Collector* c, int dt)
{
	bool mesa_empty = c->mesa->isEmpty;

	if (c->mesa_was_empty && !mesa_empty)
	{
		c->anim.Ensure(AnimationType::CAPSULE_OPENING);
		c->anim.loopable = false;
	}

	if (mesa_empty && !c->mesa_was_empty)
	{
		c->anim.Ensure(AnimationType::CAPSULE_CLOSING);
		c->anim.loopable = false;
	}

	c->mesa_was_empty = mesa_empty;
}