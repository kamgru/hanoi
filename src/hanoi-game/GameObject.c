#include "GameObject.h"

void GameObjectManager_initialize();
GameObject* GameObject_create(ASprite* sprite, SDL_Rect* collider);
GameObject* GameObject_find(GameObjectId* gameObjectId);
void GameObject_destroy(GameObject* gameObject);
void GameObject_draw(GameObject* gameObject, SDL_Renderer* renderer);

typedef struct Node Node;
static int GameObjectId_hash(GameObjectId* id);
static void GameObjectManager_insert(GameObject* gameObject);
static GameObject* GameObject_new(ASprite* sprite, SDL_Rect* collider);
static int GameObject_generateId();
static Node* Node_new(GameObject* gameObject, Node* previous);

static const int bucketCount = 2;
static Node** buckets;
static int nodeCount;

struct Node {
	GameObject* gameObject;
	Node* next;
	Node* previous;
};

static Node* Node_new(GameObject* gameObject, Node* previous) {
	Node* node = malloc(sizeof(Node));
	node->gameObject = gameObject;
	node->previous = previous;
	node->next = NULL;
	return node;
}

void GameObjectManager_initialize() {
	buckets = calloc(32, sizeof(Node*));
}

GameObject* GameObject_create(ASprite* sprite, SDL_Rect* collider) {
	GameObject* gameObject = GameObject_new(sprite, collider);
	GameObjectManager_insert(gameObject);
	return gameObject;
}

static int GameObjectId_hash(GameObjectId* id) {
	return (*id) % bucketCount;
}

static void GameObjectManager_insert(GameObject* gameObject) {
	int hashIndex = GameObjectId_hash(&gameObject->id);

	Node* node = buckets[hashIndex];
	if (node == NULL) {
		buckets[hashIndex] = Node_new(gameObject, NULL);
	}
	else {
		while (node->next != NULL) {
			node = node->next;
		}

		node->next = Node_new(gameObject, node);
	}

	nodeCount++;
}

GameObject* GameObject_find(GameObjectId* gameObjectId) {
	int hashIndex = GameObjectId_hash(gameObjectId);

	Node* node = buckets[hashIndex];
	if (node == NULL) {
		return NULL;
	}

	while (node->gameObject->id != *gameObjectId) {
		node = node->next;
		if (node == NULL) {
			return NULL;
		}
	}
	return node->gameObject;
}

static void GameObjectManager_remove(GameObjectId* gameObjectId) {
	int hashIndex = GameObjectId_hash(gameObjectId);

	Node* node = buckets[hashIndex];
	if (node == NULL) {
		return;
	}

	while (node->gameObject->id != *gameObjectId) {
		node = node->next;
		if (node == NULL) {
			return;
		}
	}

	if (node->previous == NULL) {
		buckets[hashIndex] = node->next;
	}
	else {
		node->previous->next = node->next;
	}
	free(node);
}

static GameObject* GameObject_new(ASprite* sprite, SDL_Rect* collider) {
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

	GameObjectManager_remove(&gameObject->id);

	if (gameObject->sprite != NULL) {
		ASprite_destroy(gameObject->sprite);
	}

	free(gameObject);
}

static int GameObject_generateId() {
	static int counter = 0;
	return counter++;
}