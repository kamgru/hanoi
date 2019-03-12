#include "SDL.h"
#include "Core.h"
#include "Sprite.h"

typedef struct GameObject GameObject;
typedef unsigned int GameObjectId;

struct GameObject {
	unsigned int id;
	Vector2 position;
	Vector2 size;
	ASprite* sprite;
	SDL_Rect collider;
};

GameObject* GameObject_new(ASprite* sprite, SDL_Rect* collider);
void GameObject_destroy(GameObject* gameObject);
void GameObject_draw(GameObject* gameObject, SDL_Renderer* renderer);