#pragma once

#include "SDL_gpu.h"
#include <SDL_ttf.h>

#include "vec.h"

struct Emoji
{
	Emoji(TTF_Font* font, const char* bytes);

	~Emoji() { GPU_FreeImage(image); }
	operator GPU_Image*() const { return image;	}
	vec GetSize() const { return size; }


private:
	vec size;
	mutable GPU_Image* image;
};

