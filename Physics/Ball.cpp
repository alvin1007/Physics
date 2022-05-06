#include "main.h"
#include "Ball.h"

void Ball::Draw(SDL_Renderer* renderer, float deltaTime) {
	const int diameter = _radius * 2;

	float x = (float)_radius - 1;
	float y = 0;
	float tx = 1;
	float ty = 1;
	float error = tx - diameter;

    _pos.x += ((float)(1.0 / 2.0) * _v.x * deltaTime);
    _pos.y += ((float)(1.0 / 2.0) * _v.y * deltaTime);

	while (x >= y) {
        SDL_RenderDrawLineF(renderer, _pos.x + x, _pos.y - y, _pos.x + x, _pos.y + y);
        SDL_RenderDrawLineF(renderer, _pos.x - x, _pos.y - y, _pos.x - x, _pos.y + y);
        SDL_RenderDrawLineF(renderer, _pos.x + y, _pos.y - x, _pos.x + y, _pos.y + x);
        SDL_RenderDrawLineF(renderer, _pos.x - y, _pos.y - x, _pos.x - y, _pos.y + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        } else if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
	}
}

void Ball::Update(float deltaTime) {
    _v.x += _a.x * deltaTime;
    _v.y += _a.y * deltaTime;

     if (_pos.x + _radius <= 2 * _radius || _pos.x + _radius >= 1280)
        _v.x = -_v.x;

     if (_pos.y - _radius <= 0 || _pos.y + _radius >= 720)
         _v.y = -_v.y;
}

void Ball::Force(Vector* force) {
    _v.x = 0.1 * force->x / _m + _v.x;
    _v.y = 0.1 * force->y / _m + _v.y;
}