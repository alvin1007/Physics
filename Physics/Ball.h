#ifndef BALLHEADER
#define BALLHEADER

#include "Vector.h"

class Ball {
public:

	Ball(int r, float x, float y, float vx, float vy) : _radius(r), _pos(x, y), _v(vx, vy) {}
	~Ball() {};
	
	void Draw(SDL_Renderer*, float deltaTime);
	void Update(float deltaTime);
	void Force(Vector* force);

	int GetRadius() { return _radius; }
	Vector GetPos() { return _pos; }
private:
	int _radius = 0;

	Vector _pos, _v;
	Vector _a = Vector(0, 50);

	int _m = 1;
};

#endif
