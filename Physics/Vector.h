#ifndef VECTORHEADER
#define VECTORHEADER

#include <math.h>

class Vector {
public:
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	~Vector() {}

	Vector operator+(Vector& v) {
		return Vector(this->x + v.x, this->y + v.y);
	}

	float VectorDistance(Vector& v2) {
		return sqrtf((this->x - v2.x) * (this->x - v2.x) + (this->y - v2.y)* (this->y - v2.y));
	}

	float x = 0, y = 0;
};

#endif
