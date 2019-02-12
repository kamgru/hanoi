#pragma once

#include "SDL.h"

typedef struct ASprite ASprite;
typedef struct SpriteInterface SpriteInterface;
typedef struct BasicSprite BasicSprite;
typedef struct SlicedSprite SlicedSprite;

struct SpriteInterface {
	void(*draw)(void* instance, SDL_Renderer* renderer, SDL_Rect* dstRect);
};

struct BasicSprite {
	SDL_Rect* srcRect;
	SDL_Texture* texture;
};

struct ASprite {
	void* instance;
	SpriteInterface* interface;
};

ASprite* BasicSprite_new(SDL_Texture* texture, SDL_Rect* srcRect);
void BasicSprite_draw(BasicSprite* instance, SDL_Renderer* renderer, SDL_Rect* dstRect);
void ASprite_draw(ASprite* sprite, SDL_Renderer* renderer, SDL_Rect* dstRect);