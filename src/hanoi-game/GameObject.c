#include "GameObject.h"

void GameObject_destroy(GameObject* gameObject);
void GameObject_draw(GameObject* gameObject, SDL_Renderer* renderer);
GameObject* GameObject_new(ASprite* sprite, SDL_Rect* collider);

static int GameObject_generateId();

GameObject* GameObject_new(ASprite* sprite, SDL_Rect* collider) {
	GameObject* gameObject = malloc(sizeof(GameObject));
	gameObject->sprite = sprite;

	if (collider != NULL) {
		gameObject->collider = *collider;
	}

	gameObject->id = GameObject_generateId();

	return gameObject;
}

void GameObject_draw(GameObject* gameObject, SDL_Renderer* renderer) {
	SDL_Rect dstRect = {
		.x = gameObject->position.x,
		.y = gameObject->position.y,
		.w = gameObject->size.x,
		.h = gameObject->size.y
	};

	ASprite_draw(gameObject->sprite, renderer, &dstRect);
}

void GameObject_destroy(GameObject* gameObject) {

	if (gameObject->sprite != NULL) {
		ASprite_destroy(gameObject->sprite);
	}

	free(gameObject);
}

static int GameObject_generateId() {
	static int counter = 0;
	return counter++;
}