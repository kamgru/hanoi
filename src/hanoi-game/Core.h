#pragma once

typedef struct Vector2 Vector2;

struct Vector2 {
	int x;
	int y;
};

double Vector2_lengthSquared(Vector2* vector2);