#ifndef VECTORHEADER
#define VECTORHEADER

class Vector {
public:
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	~Vector() {}

	float x = 0, y = 0;
};

#endif
