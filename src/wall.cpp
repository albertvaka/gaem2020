#include "wall.h"

#include "mates.h"
#include "assets.h"
#include "window.h"
#include "rand.h"
#include "assets.h"
#include "anim_lib.h"

extern float mainClock;

float kTimerColDuration = 0.35f;

Wall::Wall(const vec& from, const vec& to, bool inner)
	: inner(inner)
	, from(from)
	, to(to)
{
	vec perp = (from - to).Perp().Normalized() * 2;

	bbounds.TL = from + perp;
	bbounds.BL = from - perp;
	bbounds.TR = to + perp;
	bbounds.BR = to - perp;

}


void Wall::Update(float dt)
{
	timerLastCol -= dt;
}

void Wall::JustCollided()
{
	timerLastCol = kTimerColDuration;
}

void Wall::Draw() const
{

	if (timerLastCol > 0.0f)
	{
		const float kBorderFull = 12;
		float t = 1.0f - (timerLastCol / kTimerColDuration);

		Window::DrawPrimitive::Line(from, to, kBorderFull - (kBorderFull -2)*t, { 255,(Uint8)(255*t),(Uint8)(255*t),255 });
	}
	else
	{
		Window::DrawPrimitive::Line(from, to, 2, { 255,255,255,255 });
	}

	if (Debug::Draw) 
	{
		bbounds.Draw();
	}
}
