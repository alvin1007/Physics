#include "main.h"
#include "System.h"

System::System() {}
System::~System() {}

bool System::Init() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return false;

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		return false;

	MainWindow = SDL_CreateWindow("Physics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	if (!MainWindow)
		return false;

	MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE|SDL_RENDERER_PRESENTVSYNC);
	if (!MainRenderer)
		return false;

	MainEvent = new SDL_Event;
	if (!MainEvent)
		return false;
	
	for (int i = 0; i < 5; i++)
		Balls.push_back(new Ball);
	
	Balls[0]->Init(100, 640, 360);
	Balls[1]->Init(30, 800, 500);
	Balls[2]->Init(60, 120, 130);
	Balls[3]->Init(70, 530, 480);
	Balls[4]->Init(50, 340, 700);

	return true;
}

bool System::Render() {

	while (!SystemQuit) {
		while (SDL_PollEvent(MainEvent) != 0) {
			switch (MainEvent->type) {
			case SDL_QUIT:
				SystemQuit = true;
				break;
			}
		}

		SDL_SetRenderDrawColor(MainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(MainRenderer);

		SDL_SetRenderDrawColor(MainRenderer, 0x00, 0x00, 0x00, 0xFF);

		for (int i = 0; i < Balls.size(); i++)
		{
			Balls[i]->Draw(MainRenderer, time);
			Balls[i]->Update(deltaTime);
		}

		SDL_RenderPresent(MainRenderer);

		time += deltaTime;
	}

	return true;
}

bool System::Clear() {

	SDL_DestroyWindow(MainWindow);
	SDL_DestroyRenderer(MainRenderer);
	delete MainEvent;

	for (int i = 0; i < Balls.size(); i++)
		delete Balls[i];

	return true;
}