#include "Sprite.h"

void ASprite_draw(ASprite* sprite, SDL_Renderer* renderer, SDL_Rect* dstRect) {
	sprite->interface->draw(sprite->instance, renderer, dstRect);
}

void ASprite_destroy(ASprite* sprite) {
	sprite->interface->destroy(sprite->instance);
	free(sprite);
}