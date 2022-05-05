#include "main.h"
#include "Ball.h"

Ball::Ball() {}
Ball::~Ball() {}

bool Ball::Init(int r, int x, int y) {
	radius = r;
	posx = x;
	posy = y;
    return true;
}

void Ball::Draw(SDL_Renderer* renderer, float time) {
	const int diameter = radius * 2;

	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = tx - diameter;

    int RealPosX = posx + (int)((1.0 / 2.0) * vx * time);
    int RealPosY = posy + (int)((1.0 / 2.0) * vy * time);

	while (x >= y) {
        SDL_RenderDrawLine(renderer, RealPosX + x, RealPosY - y, RealPosX + x, RealPosY + y);
        SDL_RenderDrawLine(renderer, RealPosX - x, RealPosY - y, RealPosX - x, RealPosY + y);
        SDL_RenderDrawLine(renderer, RealPosX + y, RealPosY - x, RealPosX + y, RealPosY + x);
        SDL_RenderDrawLine(renderer, RealPosX - y, RealPosY - x, RealPosX - y, RealPosY + x);

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
    vx += ax * deltaTime;
    vy += ay * deltaTime;
}