#include "Core.h"
#include <math.h>

double Vector2_lengthSquared(Vector2* vector2) {
	return pow(vector2->x, 2) + pow(vector2->y, 2);
}