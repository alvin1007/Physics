#ifndef SYSTEMHEADER
#define SYSTEMHEADER

#include <vector>
#include <random>
#include "Ball.h"

class System {
public:
	System() {};
	~System() {};

	bool Init();
	bool Render();
	bool Clear();

private:
	float VectorDistance(Vector&& v1, Vector&& v2) {
		return sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
	}

private:
	SDL_Window* MainWindow = nullptr;
	SDL_Renderer* MainRenderer = nullptr;
	SDL_Event* MainEvent = nullptr;

	bool SystemQuit = false;

	std::vector<Ball*> Balls;

	float deltaTime = 0.05f;
};

#endif
