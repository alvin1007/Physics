#ifndef BALLHEADER
#define BALLHEADER

#include "Vector.h"

class Ball {
public:

	Ball(int r, float x, float y, float vx, float vy) : _radius(r), _pos(x, y), _v(vx, vy) {}
	~Ball() {};
	
	void Draw(SDL_Renderer*, float deltaTime);
	void DrawVector(SDL_Renderer*);
	void Update(float deltaTime);
	void Force(Vector* force);

	int GetRadius() { return _radius; }
	int GetK() { return _k; }
	Vector GetPos() { return _pos; }
	Vector GetV() { return _v; }
private:
	int _radius = 0;

	Vector _pos, _v;
	Vector _a = Vector(0, 50);

	int _m = 1;
	int _k = 5;
};

#endif
