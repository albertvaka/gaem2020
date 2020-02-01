#pragma once

#include "entity.h"

struct Mesa : public Entity, EntS<Mesa>
{

	bool canLet;
	bool isEmpty;

	Cadaver* cadaver;

	int currentPlayer;

	Mesa(vec position)
	{
		pos.x = position.x;
		pos.y = position.y;
		canLet = false;
		isEmpty = true;
	}

	void Draw(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Yellow);
		shape.setOutlineThickness(1);
		shape.setPosition(pos.x, pos.y);
		shape.setSize(sf::Vector2f(16, 16));

		wnd.draw(shape);
	}

};

