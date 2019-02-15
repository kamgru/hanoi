#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include "Sprite.h"
#include "Core.h"
#include "GameObject.h"


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
	
	ASprite* spr1 = SlicedSprite_new(
		texture,
		&(SDL_Rect){.x = 0, .y = 0, .w = 16, .h = 16},
		SliceInfo_new(4, 12, 4, 12));

	ASprite* spr2 = SlicedSprite_new(
		texture,
		&(SDL_Rect){.x = 16, .y = 0, .w = 32, .h = 32},
		SliceInfo_new(4, 28, 4, 28));

	ASprite* spr3 = SlicedSprite_new(
		texture,
		&(SDL_Rect){.x = 16, .y = 0, .w = 32, .h = 32},
		SliceInfo_new(4, 28, 4, 28));



	GameObjectManager_initialize();
	GameObject* gobj1 = GameObject_create(spr1, NULL);
	gobj1->position = (Vector2){ .x = 20,.y = 50 };
	gobj1->size = (Vector2) { .x = 100, .y = 32 };

	GameObject* gobj2 = GameObject_create(spr2, NULL);
	gobj2->position = (Vector2) { .x = 50, .y = 10 };
	gobj2->size = (Vector2) { .x = 16, .y = 42 };

	GameObject* gobj3 = GameObject_create(spr3, NULL);
	gobj3->position = (Vector2) { .x = 400, .y = 350 };
	gobj3->size = (Vector2) { .x = 64, .y = 64};


	SDL_Event event;
	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		GameObject_draw(GameObject_find(&gobj1->id), renderer);
		GameObject_draw(GameObject_find(&gobj2->id), renderer);
		GameObject_draw(GameObject_find(&gobj3->id), renderer);

		SDL_RenderPresent(renderer);
	}

	GameObject_destroy(gobj1);
	GameObject_destroy(gobj2);
	GameObject_destroy(gobj3);

	SDL_DestroyTexture(texture);
	SDL_Quit();

	return 0;
}