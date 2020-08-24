#include <stdio.h>
#include "SDL_gpu.h"

int main(int argc, char* argv[])
{
	GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

	GPU_Target* screen = GPU_Init(256, 128, 0);

	GPU_SetDefaultAnchor(0.f, 0.f);

	GPU_Image* intermediate = GPU_CreateImage(256, 256, GPU_FORMAT_RGBA);
	GPU_Target* intermediateTarget = GPU_LoadTarget(intermediate);

	GPU_Image* texture = GPU_LoadImage("redsquare.png");
	if (!texture) {
		printf("Unable to load image\n");
		return 1;
	}

	GPU_SetImageFilter(texture, GPU_FILTER_NEAREST);
	GPU_SetSnapMode(texture, GPU_SNAP_NONE);

	while (true) {
		// Render three squares onto intermediateTarget
		GPU_ClearRGB(intermediateTarget, 0, 0, 0);
		GPU_Rect textureSrc = { 32, 32, 32, 32 };
		GPU_Blit(texture, &textureSrc, intermediateTarget, 50.f,  50.45f); // displays OK
		GPU_Blit(texture, &textureSrc, intermediateTarget, 100.f, 50.50f); // displays incorrectly
		GPU_Blit(texture, &textureSrc, intermediateTarget, 150.f, 50.55f); // displays OK
		GPU_Flip(intermediateTarget);

		// Render intermediateTarget onto screen 		
		GPU_ClearRGB(screen, 100, 100, 100);
		GPU_Rect screenSrc = { 0, 0, 256, 256 };
		GPU_Blit(intermediate, &screenSrc, screen, 0, 0);
		GPU_Flip(screen);
	
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				return 0;
			}
		}
	}
}

