#include "SDL.h"
#include <stdio.h>

const int SCREEN_W = 800;
const int SCREEN_H = 600;

int main(int argc, char *argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
		return 1;
	}


	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	return 0;
}