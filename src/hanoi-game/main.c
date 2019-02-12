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
	
	ASprite* mySprite = BasicSprite_new(texture, NULL);
	
	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		ASprite_draw(mySprite, renderer, &(SDL_Rect){.x = 0, .y = 0, .w = 16, .h = 16});
		SDL_RenderPresent(renderer);
	}

	return 0;
}