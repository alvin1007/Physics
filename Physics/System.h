#ifndef SYSTEMHEADER
#define SYSTEMHEADER

#include <vector>
#include "Ball.h"

class System {
public:
	System();
	~System();

	bool Init();
	bool Render();
	bool Clear();
private:
	SDL_Window* MainWindow = nullptr;
	SDL_Renderer* MainRenderer = nullptr;
	SDL_Event* MainEvent = nullptr;

	bool SystemQuit = false;

	std::vector<Ball*> Balls;

	float time = 0;
	float deltaTime = 0.05;
};

#endif
