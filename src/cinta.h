#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Cinta : Entity, EntS<Cinta>
{
	
	Cinta(vec position, EntityDirection direction) {
		pos = position;
		anim.Ensure(AnimationType::BELT_RIGHT);
		state = EntityState::MOVING;
		dir = direction;
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{

	}

	void Update(float dt)
	{

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