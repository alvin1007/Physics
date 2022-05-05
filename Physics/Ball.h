#ifndef BALLHEADER
#define BALLHEADER

class Ball {
public:
	Ball();
	~Ball();
	bool Init(int r, int x , int y);
	void Draw(SDL_Renderer*, float time);
	void Update(float deltaTime);
private:
	int radius = 0;
	int posx = 0;
	int posy = 0;

	float ax = 0;
	float ay = 10;

	float vx = 50;
	float vy = -200;
};

#endif
