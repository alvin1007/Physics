#include "main.h"
#include "System.h"

bool System::Init() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		return false;

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"))
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

	// std::random_device rd;
	// std::mt19937 gen(rd());
	
	//std::uniform_int_distribution<int> dis1(20, 1220);
	//std::uniform_int_distribution<int> dis2(680, 710);
	//std::uniform_int_distribution<int> dis3(-1, 1);

	//for (int i = 0; i < 900; i++)
		//Balls.push_back(new Ball(5, dis1(gen), dis2(gen), dis3(gen), dis3(gen)));

#if (MOD == 1)
	Balls.push_back(new Ball(40, 200, 600, 150, -10));
	Balls.push_back(new Ball(40, 1000, 400, -10, -100));
	Balls.push_back(new Ball(40, 600, 500, -50, -20));
	Balls.push_back(new Ball(40, 800, 600, 70, -60));
#elif (MOD == 2)
	Balls.push_back(new Ball());
#elif (MOD == 3)
	Balls.push_back(new Ball());
#elif (MOD == 4)
	Balls.push_back(new Ball());
#endif

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
#ifdef DEBUG_MOD
			Balls[i]->DrawVector(MainRenderer);
#endif
		}

		for (int i = 0; i < Balls.size(); i++)
		{
			for (int j = i + 1; j < Balls.size(); j++)
			{
				if (VectorDistance(Balls[i]->GetPos(), Balls[j]->GetPos()) <= Balls[i]->GetRadius() + Balls[j]->GetRadius()) {
					const float theta = atan((Balls[i]->GetPos().y - Balls[j]->GetPos().y) / (Balls[i]->GetPos().x - Balls[j]->GetPos().x));
					const float distance = VectorDistance(Balls[i]->GetPos(), Balls[j]->GetPos());

					const float FORCE1 = Balls[i]->GetK() * (Balls[i]->GetRadius() + Balls[j]->GetRadius() - distance);
					const float FORCE2 = Balls[j]->GetK() * (Balls[i]->GetRadius() + Balls[j]->GetRadius() - distance);
					    
					if (Balls[i]->GetPos().x > Balls[j]->GetPos().x) {
						Balls[i]->Force(new Vector(FORCE1 * cos(theta), FORCE1 * sin(theta)));
						Balls[j]->Force(new Vector(-FORCE2 * cos(theta), -FORCE2 * sin(theta)));
					} else {
						Balls[i]->Force(new Vector(-FORCE1 * cos(theta), -FORCE1 * sin(theta)));
						Balls[j]->Force(new Vector(FORCE2 * cos(theta), FORCE2 * sin(theta)));
					}

					// std::cout << abs((Balls[0]->GetV() + Balls[1]->GetV()).x) + abs((Balls[0]->GetV() + Balls[1]->GetV()).y) << std::endl;
				}
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