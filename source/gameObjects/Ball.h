#pragma once
#include <vector>
#include "../graphics/LTexture.h"
#include "Paddle.h"
#include "Block.h"
#include "../SoundPlayer.h"

struct CircleCollider
{
	int x, y; //center position
	int r; //radius
};

struct RayCast2D
{
	int originX, originY;
	int length; //ray length to be fixed at circle radius + ball speed
};

class Ball
{
public:
	LTexture ballTexture;
	CircleCollider ballCollider;
	RayCast2D ballRay;

	static const int BALL_RADIUS = 6;
	static const int BALL_SPEED = -10; 
	const float MASS;

	int ballPos_X, ballPos_Y;
	int ballVelocity_X;
	int ballVelocity_Y;
	bool isMoving;

	Ball();
	Ball(float m); //init mass
	~Ball();

	bool loadTexture(std::string path, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void launch();
	void move(std::vector<Block>& blocks, Paddle* paddle);
	void reset(Paddle* paddle);
	float colllisionAngle(SDL_Rect* col);
	SDL_Rect* detectCollision(std::vector<Block>& blocks, Paddle* paddle);
	double distanceSquared(int x1, int y1, int x2, int y2);
	CircleCollider* getCollider();
	SoundPlayer soundPlayer;
};
