#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "vector.h"

struct TextMolest : public SortedDrawable, public EntS<TextMolest>
{
	enum Type 
	{
		GOOD,
		BAD
	};

	int timer = 0;
	Type m_type = GOOD;

	TextMolest(vec position, Type type) 
	{
		pos = vec(16*13.5f, 16*10);
		m_type = type;

		speed.x = 0;// 16 * 2.5f;
		speed.y = -16* 1.8f;
	}

	void Update(int dt)
	{
		timer += dt;

		pos += (dt/1000.0f) * speed;

		if (timer > 10000) alive = false;
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		float scx = 4 + cos(timer/200.0f)*2;
		float scy = 4 + sin(timer/200.0f)*2;

		float rot = sin(timer / 100.0f) * 5;

		spr.setOrigin(16 * 2.5f, 8);
		spr.setScale(scx, scy);
		spr.setRotation(rot);

		
		switch (m_type)
		{
			case Type::GOOD:
			{
				spr.setTextureRect(sf::IntRect(128, 192, 16*4, 16));
			
				spr.setPosition(pos);
				wnd.draw(spr);
			} break;

			case Type::BAD:
			{
				//spr.setTextureRect(anim.CurrentFrame());
				spr.setPosition(pos);
				wnd.draw(spr);
			} break;
		}

		spr.setScale(1, 1);
		spr.setOrigin(0, 0);
		spr.setRotation(0);
	}

};
