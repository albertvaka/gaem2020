#include "powerup.h"

#include "mates.h"
#include "assets.h"
#include "window.h"
#include "rand.h"
#include "assets.h"
#include "anim_lib.h"

extern float mainClock;

PowerUp::PowerUp(const vec& from, const vec& to, bool inner)
	: inner(inner)
{
	vec perp = (from - to).Perp().Normalized() * 2;

	bbounds.TL = from + perp;
	bbounds.BL = from - perp;
	bbounds.TR = to + perp;
	bbounds.BR = to - perp;

}
void PowerUp::Draw() const
{
	bbounds.Draw();
}
