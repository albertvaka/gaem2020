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
		pos = position;
		canLet = false;
		isEmpty = true;

		anim.Ensure(AnimationType::);
	}

	void Update(int dt) {

	}
	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		if (canLet || (currentPlayer >= 0 && !isEmpty)) 
		{
			sf::RectangleShape shape;
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(sf::Color::Yellow);
			shape.setOutlineThickness(1);
			shape.setPosition(pos.x, pos.y);
			shape.setSize(sf::Vector2f(16, 16));

			wnd.draw(shape);
		}
	}

};

