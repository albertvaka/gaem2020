#pragma once

#include <array>

#include "SDL_gpu.h"
#include "sound.h"
#include "shader.h"
typedef struct _TTF_Font TTF_Font;

namespace Assets
{
	extern void LoadAll();

	inline GPU_Image* spritesheet;

	inline TTF_Font* font_30;
	inline TTF_Font* font_30_outline;

	inline Shader tintShader;
};

