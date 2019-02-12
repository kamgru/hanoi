#include "Sprite.h"

void BasicSprite_draw(BasicSprite* instance, SDL_Renderer* renderer, SDL_Rect* dstRect) {
	SDL_RenderCopy(renderer, instance->texture, instance->srcRect, dstRect);
}

SpriteInterface* BasicSpriteInterface = &(SpriteInterface) {
	.draw = BasicSprite_draw
};

ASprite* BasicSprite_new(SDL_Texture* texture, SDL_Rect* srcRect) {
	ASprite* asprite = malloc(sizeof(ASprite));
	asprite->interface = BasicSpriteInterface;
	BasicSprite* instance = malloc(sizeof(BasicSprite));
	instance->srcRect = srcRect;
	instance->texture = texture;

	asprite->instance = instance;
	return asprite;
}

void ASprite_draw(ASprite* sprite, SDL_Renderer* renderer, SDL_Rect* dstRect) {
	sprite->interface->draw(sprite->instance, renderer, dstRect);
}