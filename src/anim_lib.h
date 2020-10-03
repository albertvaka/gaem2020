#pragma once

#include "../engine/anim_frame.h"

namespace AnimLib {

	constexpr const AnimationFrame GOOMBA[] = {
		{ {14 * 16, 16, 16, 16}, .2f },
		{ {15 * 16, 16, 16, 16}, .2f },
	};

	constexpr const GPU_Rect POWERUP = {5*16, 11*16, 16, 16};

}
