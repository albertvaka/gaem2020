#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "vector.h"

struct TextMolest : public SortedDrawable, public EntS<TextMolest>
{
	enum Type {
		GOOD,
		BAD
	};
	float timer = 1.f;
	Type m_type = GOOD;
	TextMolest(vec position, Type type) {
		pos = position;
		m_type = type;
	}

	void Update(int dt)
	{
		timer += dt;
		if (timer > 3000) alive = true;

	}
	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		spr.setScale(3, 3);
		switch (m_type)
		{
		case Type::GOOD:
		{
			spr.setTextureRect(sf::IntRect(0,0,700,700));
			
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

	}

};
