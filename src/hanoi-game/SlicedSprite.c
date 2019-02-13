#include "Sprite.h"

static void SlicedSprite_draw(SlicedSprite* instance, SDL_Renderer* renderer, SDL_Rect* dstRect);
SliceInfo* SliceInfo_new(int left, int right, int top, int bottom);

SpriteInterface* SlicedSpriteInterface = &(SpriteInterface) {
	.draw = SlicedSprite_draw,
	.destroy = SlicedSprite_destroy
};

ASprite* SlicedSprite_new(SDL_Texture* texture, SDL_Rect* srcRect, SliceInfo* sliceInfo) {
	ASprite* sprite = malloc(sizeof(ASprite));
	sprite->interface = SlicedSpriteInterface;
	SlicedSprite* instance = malloc(sizeof(SlicedSprite));
	instance->texture = texture;
	instance->sliceInfo = sliceInfo;

	//top left
	instance->slices[0] = (SDL_Rect) {
		.x = srcRect->x,
			.y = srcRect->y,
			.w = sliceInfo->left,
			.h = sliceInfo->top
	};

	//top
	instance->slices[1] = (SDL_Rect) {
		.x = srcRect->x + sliceInfo->left,
			.y = srcRect->y,
			.w = sliceInfo->right - sliceInfo->left,
			.h = sliceInfo->top
	};

	//top right
	instance->slices[2] = (SDL_Rect) {
		.x = srcRect->x + sliceInfo->right,
			.y = srcRect->y,
			.w = srcRect->w - sliceInfo->right,
			.h = sliceInfo->top
	};

	//middle left
	instance->slices[3] = (SDL_Rect) {
		.x = srcRect->x,
			.y = srcRect->y + sliceInfo->top,
			.w = sliceInfo->left,
			.h = sliceInfo->bottom - sliceInfo->top
	};

	//middle
	instance->slices[4] = (SDL_Rect) {
		.x = srcRect->x + sliceInfo->left,
			.y = srcRect->y + sliceInfo->top,
			.w = sliceInfo->right - sliceInfo->left,
			.h = sliceInfo->bottom - sliceInfo->top
	};

	//middle right
	instance->slices[5] = (SDL_Rect) {
		.x = srcRect->x + sliceInfo->right,
			.y = srcRect->y + sliceInfo->top,
			.w = srcRect->w - sliceInfo->right,
			.h = sliceInfo->bottom - sliceInfo->top
	};

	//bottom left
	instance->slices[6] = (SDL_Rect) {
		.x = srcRect->x,
			.y = srcRect->y + sliceInfo->bottom,
			.w = sliceInfo->left,
			.h = srcRect->h - sliceInfo->bottom
	};

	//bottom
	instance->slices[7] = (SDL_Rect) {
		.x = srcRect->x + sliceInfo->left,
			.y = srcRect->y + sliceInfo->bottom,
			.w = sliceInfo->right - sliceInfo->left,
			.h = srcRect->h - sliceInfo->bottom
	};

	//bottom right
	instance->slices[8] = (SDL_Rect) {
		.x = srcRect->x + sliceInfo->right,
			.y = srcRect->y + sliceInfo->bottom,
			.w = srcRect->w - sliceInfo->right,
			.h = srcRect->h - sliceInfo->bottom
	};

	sprite->instance = instance;
	return sprite;
}

void SlicedSprite_destroy(SlicedSprite* instance) {
	free(instance->sliceInfo);
	free(instance);
}

void SlicedSprite_draw(SlicedSprite* instance, SDL_Renderer* renderer, SDL_Rect* dstRect) {

	int xOffset = dstRect->x;
	int yOffset = dstRect->y;
	int leftColumnWidth = instance->sliceInfo->left;
	int rightColumnWidth = instance->slices[2].w;
	int middleColumnWidth = dstRect->w - leftColumnWidth - rightColumnWidth;
	int topRowHeight = instance->sliceInfo->top;
	int bottomRowHeight = instance->slices[6].h;
	int middleRowHeight = dstRect->h - topRowHeight - bottomRowHeight;

	SDL_Rect topLeft = {
		.x = xOffset,
		.y = yOffset,
		.w = leftColumnWidth,
		.h = topRowHeight
	};

	SDL_Rect top = {
		.x = xOffset + leftColumnWidth,
		.y = yOffset,
		.w = middleColumnWidth,
		.h = topRowHeight
	};

	SDL_Rect topRight = {
		.x = xOffset + leftColumnWidth + middleColumnWidth,
		.y = yOffset,
		.w = rightColumnWidth,
		.h = topRowHeight
	};

	SDL_Rect middleLeft = {
		.x = xOffset,
		.y = yOffset + topRowHeight,
		.w = leftColumnWidth,
		.h = middleRowHeight
	};

	SDL_Rect middle = {
		.x = xOffset + leftColumnWidth,
		.y = yOffset + topRowHeight,
		.w = middleColumnWidth,
		.h = middleRowHeight
	};

	SDL_Rect middleRight = {
		.x = xOffset + leftColumnWidth + middleColumnWidth,
		.y = yOffset + topRowHeight,
		.w = rightColumnWidth,
		.h = middleRowHeight
	};

	SDL_Rect bottomLeft = {
		.x = xOffset,
		.y = yOffset + dstRect->h - instance->slices[6].h,
		.w = leftColumnWidth,
		.h = instance->slices[6].h
	};

	SDL_Rect bottom = {
		.x = xOffset + instance->slices[0].w,
		.y = yOffset + dstRect->h - instance->slices[6].h,
		.w = middleColumnWidth,
		.h = instance->slices[6].h
	};

	SDL_Rect bottomRight = {
		.x = xOffset + dstRect->w - instance->slices[2].w,
		.y = yOffset + dstRect->h - instance->slices[6].h,
		.w = rightColumnWidth,
		.h = instance->slices[6].h
	};

	SDL_RenderCopy(renderer, instance->texture, &instance->slices[0], &topLeft);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[1], &top);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[2], &topRight);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[3], &middleLeft);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[4], &middle);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[5], &middleRight);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[6], &bottomLeft);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[7], &bottom);
	SDL_RenderCopy(renderer, instance->texture, &instance->slices[8], &bottomRight);
}

SliceInfo* SliceInfo_new(int left, int right, int top, int bottom) {
	SliceInfo* sliceInfo = malloc(sizeof(SliceInfo));
	sliceInfo->left = left;
	sliceInfo->right = right;
	sliceInfo->top = top;
	sliceInfo->bottom = bottom;
	return sliceInfo;
}