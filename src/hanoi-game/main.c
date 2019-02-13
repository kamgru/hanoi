#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include "Sprite.h"

const int SCREEN_W = 640;
const int SCREEN_H = 480;

int main(int argc, char *argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
		return 1;
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
		return 1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, IMG_GetError());
		return 1;
	}

	SDL_Texture* texture = IMG_LoadTexture(renderer, "..\\..\\Assets\\grey_.png");
	if (texture == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, IMG_GetError());
		return 1;
	}
	
	SlicedSprite* greySlicedSprite = SlicedSprite_new(
		texture,
		&(SDL_Rect){.x = 0, .y = 0, .w = 16, .h = 16},
		SliceInfo_new(4, 12, 4, 12));

	SDL_Rect redSrcRect = {
		.x = 16,
		.y = 0,
		.w = 32,
		.h = 32
	};
	SlicedSprite* redSlicedSprite = SlicedSprite_new(texture, &redSrcRect, SliceInfo_new(4, 28, 4, 28));

	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		ASprite_draw(greySlicedSprite, renderer, &(SDL_Rect){.x = 100, .y = 50, .w = 64, .h = 128});

		ASprite_draw(redSlicedSprite, renderer, &(SDL_Rect){.x = 250, .y = 150, .w = 320, .h = 60});
		SDL_RenderPresent(renderer);
	}

	ASprite_destroy(greySlicedSprite);
	SDL_DestroyTexture(texture);
	SDL_Quit();

	return 0;
}