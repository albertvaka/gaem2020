#include "wall.h"

#include "mates.h"
#include "assets.h"
#include "window.h"
#include "rand.h"
#include "assets.h"
#include "anim_lib.h"

extern float mainClock;

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
void Wall::Draw() const
{
	Window::DrawPrimitive::Line(from, to, 2, { 255,255,255,255 });
	if (Debug::Draw) {
		bbounds.Draw();
	}
}
