// Code based on https://github.com/robn/maxibon/blob/master/maxibon.c

#include "emoji.h"
#include "window.h"

#include <vector>
#include <tuple>

#include <ft2build.h>

#include FT_FREETYPE_H
#include FT_TRUETYPE_TABLES_H
#include FT_GLYPH_H

static_assert(
	(static_cast<unsigned char>("💩"[0]) == 0xF0) &&
	(static_cast<unsigned char>("💩"[1]) == 0x9F) &&
	(static_cast<unsigned char>("💩"[2]) == 0x92) &&
	(static_cast<unsigned char>("💩"[3]) == 0xA9), "Source or compiler not UTF-8 compliant! Add flag /utf-8 for Visual Studio.");


const char* FT_Error_String(FT_Error err) {
  #undef __FTERRORS_H__
  #define FT_ERRORDEF( e, v, s )  case e: return s;
  #define FT_ERROR_START_LIST     switch (err) {
  #define FT_ERROR_END_LIST       }
  #include FT_ERRORS_H
  return "[unknown error]";
}

// returns num bytes consumed, or 0 for end/bogus
int utf8_decode_char(uint32_t *chr, const char *src) {
  unsigned int c = * (const unsigned char *) src;
  if (!c) { *chr = c; return 0; }
  if (!(c & 0x80)) { *chr = c; return 1; }
  else if (c >= 0xf0) {
    if (!src[1] || !src[2] || !src[3]) return 0;
    c = (c & 0x7) << 18;
    c |= (src[1] & 0x3f) << 12;
    c |= (src[2] & 0x3f) << 6;
    c |= src[3] & 0x3f;
    *chr = c; return 4;
  }
  else if (c >= 0xe0) {
    if (!src[1] || !src[2]) return 0;
    c = (c & 0xf) << 12;
    c |= (src[1] & 0x3f) << 6;
    c |= src[2] & 0x3f;
    *chr = c; return 3;
  }
  else {
    if (!src[1]) return 0;
    c = (c & 0x1f) << 6;
    c |= src[1] & 0x3f;
    *chr = c; return 2;
  }
}

Emoji::Emoji(TTF_Font* font, const char* bytes) {

	FT_Face ftface = *((FT_Face*)font); // Hack: First element in a TTF_Font is the FT_Face

	std::vector<std::tuple<SDL_Surface*, SDL_Rect>> surfaces;
	unsigned int offset_x = 0;
	unsigned int height = 0;
	uint32_t chr;
	int n;
	while ((n = utf8_decode_char(&chr, bytes))) {
		bytes += n;

		uint32_t glyph_index = FT_Get_Char_Index(ftface, chr);
		if (!glyph_index) {
			Debug::out << "Emoji: glyph not found in font, skipping";
			continue;
		}

		FT_Error fterr = FT_Load_Glyph(ftface, glyph_index, FT_LOAD_COLOR | FT_LOAD_DEFAULT);
		if (fterr) {
			Debug::out << "Emoji: FT_Load_Glyph: " << FT_Error_String(fterr);
			continue;
		}

		fterr = FT_Render_Glyph(ftface->glyph, FT_RENDER_MODE_NORMAL);
		if (fterr) {
			Debug::out << "Emoji: FT_Render_Glyph: " << FT_Error_String(fterr);
			continue;
		}

		FT_Bitmap *ftbm = &ftface->glyph->bitmap;
		if (ftbm->pixel_mode != FT_PIXEL_MODE_BGRA) {
			Debug::out << "Emoji: glyph found but not as a color emoji";
			continue;
		}

		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(ftbm->buffer, ftbm->width, ftbm->rows, 32, ftbm->pitch, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		if (!surface) {
			printf("Emoji: SDL_CreateRGBSurfaceFrom: %s\n", SDL_GetError());
			continue;
		}

		// Make a copy, since ftbm->buffer will be overwriten for the next glyph, and surface only has a pointer to it
		SDL_Surface* copy = SDL_CreateRGBSurfaceWithFormat(0, ftbm->width, ftbm->rows, 32, Window::nativePixelFormat);
		SDL_BlitSurface(surface,NULL,copy,NULL);
		SDL_FreeSurface(surface);
		
		SDL_Rect target_rect;
		target_rect.w = ftbm->width;
		target_rect.h = ftbm->rows;
		target_rect.x = offset_x;
		target_rect.y = 0;

		if (ftbm->rows > height) {
			height = ftbm->rows;
		}
		offset_x += ftface->glyph->advance.x >> 6;

		surfaces.push_back(std::make_tuple(copy, target_rect));
	}

	size.x = offset_x;
	size.y = height;

	SDL_Surface* final = SDL_CreateRGBSurfaceWithFormat(0, offset_x, height, 32, Window::nativePixelFormat);
	for (auto& [s, rect] : surfaces) {
		SDL_BlitSurface(s, NULL, final, &rect);
		SDL_FreeSurface(s);
	}

	image = GPU_CopyImageFromSurface(final);
	GPU_SetImageFilter(image, GPU_FILTER_NEAREST);
	GPU_SetSnapMode(image, GPU_SNAP_NONE);
	SDL_FreeSurface(final);
	if (!image) {
		Debug::out << "Unable to create text texture. SDL Error:" << SDL_GetError();
	}

}

