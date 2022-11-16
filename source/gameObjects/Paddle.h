#pragma once
#include "../graphics/LTexture.h"

class Paddle
{
public:
	static const int PADDLE_WIDTH = 90;
	static const int PADDLE_HEIGHT = 20;
	static const int PADDLE_HITBOXES = 7;
	static const int PADDLE_SPEED = 10; //pixles per frame
	static const int PADDLE_SPEED_MOUSE = 20;

	LTexture mPaddleTexture;

	int mPosX, mPosY;
	int mVelX, mVelY;

	SDL_Rect mPaddleCollider[PADDLE_HITBOXES];


	Paddle(int x, int y, bool setCollidersAuto, unsigned int middleWidth = 0);
	~Paddle();
	void move(); //collision checking will be handled in the ball class (i think)
	void render(SDL_Renderer* cRender);
	void handleEvent(SDL_Event &e);
	bool loadTexture(std::string path, SDL_Renderer* cRender);
	void moveAI(int ballPosX);

	SDL_Rect* getCollider(int index);
	int getPaddleWidth();
	int getPaddleHeight();
};
