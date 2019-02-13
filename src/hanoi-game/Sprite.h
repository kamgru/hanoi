#pragma once

#include "SDL.h"

typedef struct ASprite ASprite;
typedef struct SpriteInterface SpriteInterface;
typedef struct BasicSprite BasicSprite;
typedef struct SlicedSprite SlicedSprite;
typedef struct SliceInfo SliceInfo;

struct SpriteInterface {
	void(*draw)(void* instance, SDL_Renderer* renderer, SDL_Rect* dstRect);
	void(*destroy)(void* instance);
};

struct BasicSprite {
	SDL_Rect* srcRect;
	SDL_Texture* texture;
};

struct SlicedSprite {
	SDL_Rect slices[9];
	SDL_Texture* texture;
	SliceInfo* sliceInfo;
};

struct SliceInfo {
	int top, bottom, left, right;
};

struct ASprite {
	void* instance;
	SpriteInterface* interface;
};

void ASprite_draw(ASprite* sprite, SDL_Renderer* renderer, SDL_Rect* dstRect);
void ASprite_destroy(ASprite* sprite);

ASprite* BasicSprite_new(SDL_Texture* texture, SDL_Rect* srcRect);
void BasicSprite_destroy(BasicSprite* instance);

ASprite* SlicedSprite_new(SDL_Texture* texture, SDL_Rect* srcRect, SliceInfo* sliceInfo);
void SlicedSprite_destroy(SlicedSprite* instance);

SliceInfo* SliceInfo_new(int left, int right, int top, int bottom);