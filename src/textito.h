#pragma once

#include "entity.h"
#include "selfregister.h"
#include "text.h"
#include "assets.h"

struct Textito : Entity, SelfRegister<Textito>
{
	Textito(const vec& pos, const std::string txt, const vec& dir): 
		screenText(Assets::font_30, Assets::font_30_outline),
		pos(pos),
		timer(0.0f),
		alive(true),
		dir(dir)
	{
		screenText.SetString(txt);
	}

	vec pos;
	vec dir;
	Text screenText;
	float timer;
	bool alive;

	void Update(float dt);

	void Draw() const;
};
