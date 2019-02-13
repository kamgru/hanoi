#include "Sprite.h"

static void BasicSprite_draw(BasicSprite* instance, SDL_Renderer* renderer, SDL_Rect* dstRect);

SpriteInterface* BasicSpriteInterface = &(SpriteInterface) {
	.draw = BasicSprite_draw,
	.destroy = BasicSprite_destroy
};

ASprite* BasicSprite_new(SDL_Texture* texture, SDL_Rect* srcRect) {
	ASprite* sprite = malloc(sizeof(ASprite));
	sprite->interface = BasicSpriteInterface;
	BasicSprite* instance = malloc(sizeof(BasicSprite));
	instance->srcRect = srcRect;
	instance->texture = texture;

	sprite->instance = instance;
	return sprite;
}

void BasicSprite_destroy(BasicSprite* instance) {
	free(instance->srcRect);
	free(instance);
}

void BasicSprite_draw(BasicSprite* instance, SDL_Renderer* renderer, SDL_Rect* dstRect) {
	SDL_RenderCopy(renderer, instance->texture, instance->srcRect, dstRect);
}
