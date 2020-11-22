module;

#include "angles.h"

#include "debug.h"

#include "SDL_gpu.h"

export module window;

import bounds;

export namespace Window
{
	export constexpr const int GAME_HEIGHT = 21 * 16;
	export constexpr const int GAME_WIDTH = GAME_HEIGHT * 16.f / 9;

	export constexpr const char* WINDOW_TITLE = "Gaem";

	export SDL_Window* window;
	export GPU_Target* screenTarget;
	export GPU_Target* currentDrawTarget;
	export SDL_PixelFormatEnum nativePixelFormat;

	bool has_focus;

	export int Init();
	export void ProcessEvents();

	export inline bool HasFocus() { return has_focus; }

	export inline void Clear(uint8_t r, uint8_t g, uint8_t b) {
		GPU_ClearRGBA(Window::currentDrawTarget, r, g, b, 255);
	}

	export inline GPU_Image* CreateTexture(int w = Window::GAME_WIDTH, int h = Window::GAME_HEIGHT) {
		GPU_Image* texture = GPU_CreateImage(w, h, GPU_FORMAT_RGBA);
		GPU_SetImageFilter(texture, GPU_FILTER_NEAREST);
		GPU_SetSnapMode(texture, GPU_SNAP_NONE);
		return texture;
	}

	export void BeginRenderToTexture(GPU_Image* targetTexture, bool useCamera);
	export inline void EndRenderToTexture() {
		Window::currentDrawTarget = Window::screenTarget;
	}

	export namespace DrawPrimitive {

		export void Pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		export inline void Pixel(vec v, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { Pixel(v.x, v.y, r, g, b, a); }
		export inline void Pixel(float x, float y, const SDL_Color& c) { Pixel(x, y, c.r, c.g, c.b, c.a); }
		export inline void Pixel(vec v, uint8_t r, const SDL_Color & c) { Pixel(v.x, v.y, c.r, c.g, c.b, c.a); }

		// pass thickness < 0 to draw a filled shape
		export void Rectangle(float x1, float y1, float x2, float y2, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		export inline void Rectangle(const Bounds& box, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Rectangle(box.Left(), box.Top(), box.Right(), box.Bottom(), thickness, r, g, b, a);
		}
		export inline void Rectangle(float x1, float y1, float x2, float y2, float thickness, const SDL_Color& c) {
			Rectangle(x1, y1, x2, y2, thickness, c.r, c.g, c.b, c.a);
		}
		export inline void Rectangle(const Bounds& box, float thickness, const SDL_Color& c) {
			Rectangle(box.Left(), box.Top(), box.Right(), box.Bottom(), thickness, c.r, c.g, c.b, c.a);
		}

		export void Line(float x1, float y1, float x2, float y2, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		export inline void Line(const vec& v1, const vec& v2, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Line(v1.x, v1.y, v2.x, v2.y, thickness, r, g, b, a);
		}
		export inline void Line(float x1, float y1, float x2, float y2, float thickness, const SDL_Color& c) {
			Line(x1, y1, x2, y2, thickness, c.r, c.g, c.b, c.a);
		}
		export inline void Line(const vec& v1, const vec& v2, float thickness, const SDL_Color & c) {
			Line(v1.x, v1.y, v2.x, v2.y, thickness, c.r, c.g, c.b, c.a);
		}

		// pass thickness < 0 to draw a filled shape
		export void Circle(float x, float y, float radius, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		export inline void Circle(const vec& v, float radius, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Circle(v.x, v.y, radius, thickness, r, g, b, a);
		}
		export inline void Circle(const CircleBounds& bounds, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Circle(bounds.pos, bounds.radius, thickness, r, g, b, a);
		}
		export inline void Circle(float x, float y, float radius, float thickness, const SDL_Color& c) {
			Circle(x, y, radius, thickness, c.r, c.g, c.b, c.a);
		}
		export inline void Circle(const vec& v, float radius, float thickness, const SDL_Color& c) {
			Circle(v.x, v.y, radius, thickness, c.r, c.g, c.b, c.a);
		}
		export inline void Circle(const CircleBounds& bounds, float thickness, const SDL_Color& c) {
			Circle(bounds.pos, bounds.radius, thickness, c.r, c.g, c.b, c.a);
		}

		// pass thickness < 0 to draw a filled shape
		export void Arc(float x, float y, float radius, float start_angle, float end_angle, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		export inline void Arc(const vec& v, float radius, float start_angle, float end_angle, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			Arc(v.x, v.y, radius, start_angle, end_angle, thickness, r, g, b, a);
		}
		export inline void Arc(float x, float y, float radius, float start_angle, float end_angle, float thickness, const SDL_Color& c) {
			Arc(x, y, radius, start_angle, end_angle, thickness, c.r, c.g, c.b, c.a);
		}
		export inline void Arc(const vec& v, float radius, float start_angle, float end_angle, float thickness, const SDL_Color& c) {
			Arc(v.x, v.y, radius, start_angle, end_angle, thickness, c.r, c.g, c.b, c.a);
		}
	}

	export class Draw {
		GPU_Image* t;
		vec dest;
		GPU_Rect src = { 0,0,0,0 };
		GPU_Rect* srcp = nullptr;
		float rotation = 0;
		vec scale = vec(1.f, 1.f);
		vec origin = vec(0.f,0.f);
	public:
		inline constexpr Draw(GPU_Image* t, const vec& pos) : t(t), dest(pos) { }
		inline constexpr Draw(GPU_Image* t, float x, float y) : t(t), dest(x,y) { }
		inline constexpr Draw(GPU_Image* t, const Bounds& destRect) // sets scale
			: t(t), dest(destRect.TopLeft())
			, scale(destRect.width/float(t->w), destRect.height/float(t->h)) { }

		inline constexpr Draw& withRect(float x, float y, float w, float h) {
			return withRect({ x, y, w, h });
		}

		inline constexpr Draw& withRect(const GPU_Rect& r) {
			src = r;
			srcp = &src;
			return *this;
		}

		inline Draw& withColor(SDL_Color c) {
			return withColor(c.r, c.g, c.b, c.a);
		}

		inline Draw& withColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
			GPU_SetRGBA(t, r, g, b, a);
			return *this;
		}

		inline constexpr Draw& withOrigin(float x, float y) {
			origin.x = x;
			origin.y = y;
			return *this;
		}

		inline constexpr Draw& withOrigin(const vec& o) {
			return withOrigin(o.x, o.y);
		}

		inline constexpr Draw& withRotationDegs(float degrees) {
			rotation = degrees;
			return *this;
		}

		inline constexpr Draw& withRotationRads(float rads) {
			rotation = Angles::RadsToDegs(rads);
			return *this;
		}

		inline constexpr Draw& withScale(float x, float y) {
			scale = vec(x, y);
			return *this;
		}

		inline constexpr Draw& withScale(float s) {
			return withScale(s, s);
		}

		inline constexpr Draw& withScale(const vec& v) {
			return withScale(v.x, v.y);
		}

		inline ~Draw() {
			#if defined(__APPLE__) //&& defined(SUPERHACK_TO_FIX_MISALIGNED_TEXTRECT)
			if (Window::currentDrawTarget != Window::screenTarget) {
				float decimalPart = (dest.y - (int)(dest.y));
				const float e = 0.004f;
				if (decimalPart > 0.5f-e && decimalPart < 0.5f+e) {
					dest.y -= 2*e;
				}
			}
			#endif
			// We pass origin as rotation pivot. We could change that to a different variable.
			GPU_BlitTransformX(t, srcp, Window::currentDrawTarget, dest.x, dest.y, origin.x, origin.y, rotation, scale.x, scale.y);
			GPU_SetRGBA(t, 255, 255, 255, 255);
		}
	};

	namespace DrawRaw {

		const unsigned short MAX_VERTICES = 60000; //From SDL_GPU's GPU_BLIT_BUFFER_ABSOLUTE_MAX_VERTICES
		const unsigned int MAX_INDICES = (MAX_VERTICES / 4) * 6; //6 indices for each 4 vertices (quads drawn as 2 triangles)
		const unsigned int MAX_COMPONENTS_PER_VERTEX = 8; // Max of GPU_BATCH_XY_ST (4), GPU_BATCH_XY_RGB (5) and GPU_BATCH_XY_ST_RGBA (8) 

		extern unsigned short vertex_count;
		extern unsigned int index_count;
		extern float vertices[MAX_VERTICES * MAX_COMPONENTS_PER_VERTEX];
		extern unsigned short indices[MAX_INDICES];

		inline void FlushTexturedQuads(GPU_Image* t) {
			//Debug::out << "vertices:" << vertex_count << " indices:" << index_count;
			GPU_TriangleBatch(t, Window::currentDrawTarget, vertex_count, vertices, index_count, indices, GPU_BATCH_XY_ST);
			vertex_count = 0;
			index_count = 0;
		}

		inline void FlushRGBQuads() {
			//Debug::out << "vertices:" << vertex_count << " indices:" << index_count;
			GPU_TriangleBatch(NULL, Window::currentDrawTarget, vertex_count, vertices, index_count, indices, GPU_BATCH_XY_RGB);
			vertex_count = 0;
			index_count = 0;
		}

		inline void FlushColoredTexturedQuads(GPU_Image* t) {
			//Debug::out << "vertices:" << vertex_count << " indices:" << index_count;
			GPU_TriangleBatch(t, Window::currentDrawTarget, vertex_count, vertices, index_count, indices, GPU_BATCH_XY_ST_RGBA);
			vertex_count = 0;
			index_count = 0;
		}

		//Colors and texture coords between 0 and 1
		inline void BatchColoredTexturedQuad(GPU_Image* t, float x, float y, float w, float h, const GPU_Rect& tr, float r, float g, float b, float a)
		{
			const int COMPONENTS_PER_VERTEX = 8; // GPU_BATCH_XY_ST_RGBA
			unsigned int i = vertex_count * COMPONENTS_PER_VERTEX;

			//bottom left
			vertices[i++] = x;
			vertices[i++] = y + h;
			vertices[i++] = tr.x;
			vertices[i++] = tr.y + tr.h;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;
			vertices[i++] = a;

			//top left
			vertices[i++] = x;
			vertices[i++] = y;
			vertices[i++] = tr.x;
			vertices[i++] = tr.y;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;
			vertices[i++] = a;

			//top right
			vertices[i++] = x + w;
			vertices[i++] = y;
			vertices[i++] = tr.x + tr.w;
			vertices[i++] = tr.y;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;
			vertices[i++] = a;

			//bottom right
			vertices[i++] = x + w;
			vertices[i++] = y + h;
			vertices[i++] = tr.x + tr.w;
			vertices[i++] = tr.y + tr.h;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;
			vertices[i++] = a;

			indices[index_count++] = vertex_count;
			indices[index_count++] = vertex_count + 1;
			indices[index_count++] = vertex_count + 2;
			indices[index_count++] = vertex_count;
			indices[index_count++] = vertex_count + 2;
			indices[index_count++] = vertex_count + 3;

			vertex_count += 4;

			if (vertex_count + 4 >= MAX_VERTICES) {
				// Flush what we have so we don't go over MAX_VERTICES
				FlushColoredTexturedQuads(t);
			};
		}
		
		//Texture coords between 0 and 1
		inline void BatchTexturedQuad(GPU_Image* t, float x, float y, float w, float h, const GPU_Rect& tr)
		{
			const int COMPONENTS_PER_VERTEX = 4; // GPU_BATCH_XY_ST
			unsigned int i = vertex_count * COMPONENTS_PER_VERTEX;

			//bottom left
			vertices[i++] = x;
			vertices[i++] = y + h;
			vertices[i++] = tr.x;
			vertices[i++] = tr.y + tr.h;

			//top left
			vertices[i++] = x;
			vertices[i++] = y;
			vertices[i++] = tr.x;
			vertices[i++] = tr.y;

			//top right
			vertices[i++] = x + w;
			vertices[i++] = y;
			vertices[i++] = tr.x + tr.w;
			vertices[i++] = tr.y;

			//bottom right
			vertices[i++] = x + w;
			vertices[i++] = y + h;
			vertices[i++] = tr.x + tr.w;
			vertices[i++] = tr.y + tr.h;

			indices[index_count++] = vertex_count;
			indices[index_count++] = vertex_count + 1;
			indices[index_count++] = vertex_count + 2;
			indices[index_count++] = vertex_count;
			indices[index_count++] = vertex_count + 2;
			indices[index_count++] = vertex_count + 3;

			vertex_count += 4;

			if (vertex_count + 4 >= MAX_VERTICES) {
				// Flush what we have so we don't go over MAX_VERTICES
				FlushTexturedQuads(t);
			};
		}

		//Colors between 0 and 1
		inline void BatchRGBQuad(float x, float y, float width, float height, float r, float g, float b)
		{
			const int COMPONENTS_PER_VERTEX = 5; // GPU_BATCH_XY_RGB
			unsigned int i = vertex_count * COMPONENTS_PER_VERTEX;

			//bottom left
			vertices[i++] = x;
			vertices[i++] = y + height;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;

			//top left
			vertices[i++] = x;
			vertices[i++] = y;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;

			//top right
			vertices[i++] = x + width;
			vertices[i++] = y;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;

			//bottom right
			vertices[i++] = x + width;
			vertices[i++] = y + height;
			vertices[i++] = r;
			vertices[i++] = g;
			vertices[i++] = b;

			indices[index_count++] = vertex_count;
			indices[index_count++] = vertex_count + 1;
			indices[index_count++] = vertex_count + 2;
			indices[index_count++] = vertex_count;
			indices[index_count++] = vertex_count + 2;
			indices[index_count++] = vertex_count + 3;

			vertex_count += 4;

			if (vertex_count + 4 >= MAX_VERTICES) {
				// Flush what we have so we don't go over MAX_VERTICES
				FlushRGBQuads();
			};
		}

	}


}

inline void RectToTextureCoordinates(const GPU_Image* i, GPU_Rect& tr) {
	tr.x /= i->texture_w;
	tr.y /= i->texture_h;
	tr.w /= i->texture_w;
	tr.h /= i->texture_h;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_Point& rhs)
{
	os << rhs.x << "," << rhs.y;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_FPoint& rhs)
{
	os << rhs.x << "," << rhs.y;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_Rect& rhs)
{
	os << rhs.x << "," << rhs.y << "," << rhs.w << "," << rhs.h;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_FRect& rhs)
{
	os << rhs.x << "," << rhs.y << "," << rhs.w << "," << rhs.h;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const GPU_Rect& rhs)
{
	os << rhs.x << "," << rhs.y << "," << rhs.w << "," << rhs.h;
	return os;
}




#include "SDL_gpu.h"

#ifdef _IMGUI
#include "imgui_impl_sdl.h"
#endif

#include "debug.h"
#include "raw_input.h"
#include "camera.h"

namespace Window
{
	
	int Init() {
		GPU_SetDebugLevel(GPU_DEBUG_LEVEL_1);

#ifdef __EMSCRIPTEN__
		int scale = 1;
#else
		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);
		int scale = std::min(dm.w / GAME_WIDTH, dm.h / GAME_HEIGHT);
		Debug::out << "Scaling to x" << scale;
		//Debug::out << dm.w << " " << dm.h;
#endif
		auto sdl_create_window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
		screenTarget = GPU_Init(GAME_WIDTH * scale, GAME_HEIGHT * scale, sdl_create_window_flags);
		if (screenTarget == NULL) {
			Debug::out << "GPU_Init failed";
			return 1;
		}
		window = SDL_GetWindowFromID(screenTarget->context->windowID);
		SDL_SetWindowTitle(window, Window::WINDOW_TITLE);

		// SDL_GetWindowPixelFormat() doesn't always do what we want (eg: on Windows it returns a format without alpha)
		// We should probably use glGetInternalFormativ() instead, but for now I'm hardcoding it.
		nativePixelFormat = SDL_PIXELFORMAT_ARGB8888;

		// SDL-gpu anchors images at the center by default, change it to the top-left corner
		GPU_SetDefaultAnchor(0.f, 0.f);

		// FIXME: Too late for this game, but we have the option to set the Y coordinates the right way
		//GPU_SetCoordinateMode(false);

		currentDrawTarget = screenTarget;

		GPU_EnableCamera(screenTarget, true);
		Camera::camera = GPU_GetDefaultCamera();
		Camera::gui_camera = GPU_GetDefaultCamera();
		Camera::gui_camera.use_centered_origin = false;
		Camera::SetTopLeft(0.f, 0.f);

		GPU_SetVirtualResolution(Window::screenTarget, Window::GAME_WIDTH, Window::GAME_HEIGHT);

		return 0;
	}

	void ProcessEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) > 0)
		{
			switch (event.type)
			{
			case SDL_WINDOWEVENT_FOCUS_LOST:
				has_focus = false;
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				has_focus = true;
				break;
			case SDL_CONTROLLERDEVICEADDED:
				GamePad::_Added(SDL_GameControllerOpen(event.jdevice.which));
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				GamePad::_Removed(SDL_GameControllerFromInstanceID(event.jdevice.which));
				break;
			case SDL_MOUSEWHEEL:
				Mouse::scrollWheel += event.wheel.y;
				break;
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					int width = event.window.data1;
					int height = event.window.data2;
					GPU_SetWindowResolution(width, height);

					// Workaround: Re-read the width and height for scaling.
					// On high-dpi mode, the width and height reported in the event are not the real ones.
					// See: https://github.com/grimfang4/sdl-gpu/issues/188
					SDL_GL_GetDrawableSize(window, &width, &height);

					const float scaleW = width / float(Window::GAME_WIDTH);
					const float scaleH = height / float(Window::GAME_HEIGHT);
					const float aspect = Window::GAME_WIDTH / float(Window::GAME_HEIGHT);
					GPU_Rect rect;
					if (scaleW < scaleH) {
						rect.w = width;
						rect.h = width / aspect;
						rect.x = 0;
						rect.y = (height - rect.h) / 2;
					}
					else {
						rect.w = height * aspect;
						rect.h = height;
						rect.x = (width - rect.w) / 2;
						rect.y = 0;
					}
					GPU_SetViewport(Window::screenTarget, rect);
					GPU_SetVirtualResolution(Window::screenTarget, Window::GAME_WIDTH, Window::GAME_HEIGHT);
				}
				break;
			}
#ifdef _IMGUI
			ImGui_ImplSDL2_ProcessEvent(&event);
#endif
		}
	}

	void BeginRenderToTexture(GPU_Image* targetTexture, bool useCamera) {
		GPU_Target* target = GPU_GetTarget(targetTexture);
		Window::currentDrawTarget = target;
		GPU_EnableCamera(target, useCamera);
		if (useCamera) {
			GPU_SetCamera(target, &Camera::camera);
		}
	}

	namespace DrawPrimitive {

		void Pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			GPU_Pixel(Window::currentDrawTarget, x, y, { r,g,b,a });
		}

		void Rectangle(float x1, float y1, float x2, float y2, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			if (thickness < 0)
			{
				GPU_SetLineThickness(0);
				GPU_RectangleFilled(Window::currentDrawTarget, x1, y1, x2, y2, { r,g,b,a });
			}
			else
			{
				GPU_SetLineThickness(thickness);
				GPU_Rectangle(Window::currentDrawTarget, x1, y1, x2, y2, { r,g,b,a });
			}
		}

		void Line(float x1, float y1, float x2, float y2, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			GPU_SetLineThickness(thickness);
			GPU_Line(Window::currentDrawTarget, x1, y1, x2, y2, { r,g,b,a });
		}

		void Circle(float x, float y, float radius, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			GPU_SetLineThickness(thickness);
			if (thickness < 0) {
				GPU_SetLineThickness(0);
				GPU_CircleFilled(Window::currentDrawTarget, x, y, radius, { r,g,b,a });
			}
			else {
				GPU_SetLineThickness(thickness);
				GPU_Circle(Window::currentDrawTarget, x, y, radius, { r,g,b,a });
			}
		}

		void Arc(float x, float y, float radius, float start_angle, float end_angle, float thickness, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			GPU_SetLineThickness(thickness);
			if (thickness < 0) {
				GPU_SetLineThickness(0);
				GPU_ArcFilled(Window::currentDrawTarget, x, y, radius, start_angle, end_angle, { r,g,b,a });
			}
			else {
				GPU_SetLineThickness(thickness);
				GPU_Arc(Window::currentDrawTarget, x, y, radius, start_angle, end_angle, { r,g,b,a });
			}
		}
	}


	namespace DrawRaw {
		unsigned short vertex_count = 0;
		unsigned int index_count = 0;
		float vertices[MAX_VERTICES * MAX_COMPONENTS_PER_VERTEX];
		unsigned short indices[MAX_INDICES];
	}
}
