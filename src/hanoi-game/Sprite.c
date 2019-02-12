#include "Sprite.h"

void BasicSprite_draw(BasicSprite* instance, SDL_Renderer* renderer, SDL_Rect* dstRect) {
	SDL_RenderCopy(renderer, instance->texture, instance->srcRect, dstRect);
}

void BasicSprite_destroy(BasicSprite* instance) {
	free(instance->srcRect);
	free(instance);
}

SpriteInterface* BasicSpriteInterface = &(SpriteInterface) {
	.draw = BasicSprite_draw,
	.destroy = BasicSprite_destroy
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

void ASprite_destroy(ASprite* sprite) {
	sprite->interface->destroy(sprite->instance);
	free(sprite);
}