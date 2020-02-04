#pragma once

#include "mates.h"
#include "selfregister.h"
#include "animation.h"

enum class EntityState
{
	IDLE,
	MOVING,
};

enum class EntityDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};


struct Entity : public EntS<Entity>
{
	EntityState state;
	vec pos;
	vec speed;
	vec size;
	int timer = 0;
	Animation anim;
	bool alive = true;
	//Entity* parent = NULL;
	EntityDirection dir = EntityDirection::DOWN;

	void dbg_DrawBBox(sf::RenderTarget& wnd, sf::Color outline = sf::Color::Red)
	{
		sf::RectangleShape dbg_bbox;
		dbg_bbox.setPosition(pos - size/2);
		dbg_bbox.setSize(size);
		dbg_bbox.setFillColor(sf::Color::Transparent);
		dbg_bbox.setOutlineColor(outline);
		dbg_bbox.setOutlineThickness(1);
		wnd.draw(dbg_bbox);
	}

	void dbg_DrawBBox_Tiled(sf::RenderTarget& wnd)
	{
		sf::RectangleShape dbg_bbox;
		dbg_bbox.setPosition(pos);
		dbg_bbox.setSize(size);
		dbg_bbox.setFillColor(sf::Color::Transparent);
		dbg_bbox.setOutlineColor(sf::Color::Cyan);
		dbg_bbox.setOutlineThickness(1);
		wnd.draw(dbg_bbox);
	}

};

struct SortedDrawable : public Entity, public EntS<SortedDrawable> {
	virtual void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{

	}
	virtual void Draw(sf::VertexArray& vao)
	{

	}
};





