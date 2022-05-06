#include "main.h"
#include "System.h"

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
	
	Balls.push_back(new Ball(40, 340, 640, 100.0, -190.0));
	Balls.push_back(new Ball(40, 1000, 570, -160.0, -180.0));

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
			Balls[i]->Draw(MainRenderer, deltaTime);
			Balls[i]->Update(deltaTime);
		}

		if (VectorDistance(Balls[0]->GetPos(), Balls[1]->GetPos()) <= Balls[0]->GetRadius() + Balls[1]->GetRadius()) {
			float theta = atan((Balls[0]->GetPos().y - Balls[1]->GetPos().y) / (Balls[0]->GetPos().x - Balls[1]->GetPos().x));
			
			// 힘은 100 N 이라고 가정된 코드
			const float FORCE = 1000;

			if (Balls[0]->GetPos().x > Balls[1]->GetPos().x) {
				Balls[0]->Force(new Vector(FORCE * cos(theta), FORCE * sin(theta)));
				Balls[1]->Force(new Vector(-FORCE * cos(theta), -FORCE * sin(theta)));
			} else {
				Balls[0]->Force(new Vector(-FORCE * cos(theta), -FORCE * sin(theta)));
				Balls[1]->Force(new Vector(FORCE * cos(theta), FORCE * sin(theta)));
			}
		}

		SDL_RenderPresent(MainRenderer);
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