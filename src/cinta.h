#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Cinta : public Entity, public EntS<Cinta>
{

	Cinta(vec position) {
		pos = position;
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		spr.setOrigin(0, 0);
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(sf::IntRect(64, 0, 16, 16));

		window.draw(spr);

	}

	void Draw(sf::VertexArray &vertexArray)
	{
		/*
		float x = pos.x / 100.0f;
		float y = pos.y / 100.0f;
		sf::Vector2f posStartInSpritesheet(100.f, 100.f);
		sf::Vector2f sizeSprite(16.f, 16.f);
		//sf::Vector2f sizeSprite(64.f, 64.f);
		sf::Vector2u scale(4, 4);
		vertexArray.append(sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(posStartInSpritesheet.x, posStartInSpritesheet.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x + sizeSprite.x*scale.x, y), sf::Vector2f(posStartInSpritesheet.x + sizeSprite.x, posStartInSpritesheet.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x + sizeSprite.x*scale.x, y + sizeSprite.y*scale.y), sf::Vector2f(posStartInSpritesheet.x + sizeSprite.x, posStartInSpritesheet.y + sizeSprite.y)));
		vertexArray.append(sf::Vertex(sf::Vector2f(x, y + sizeSprite.y*scale.y), sf::Vector2f(posStartInSpritesheet.x, posStartInSpritesheet.y + sizeSprite.y)));

		*/

	}


};