#include "Paddle.h"

//Paddle implementation file

Paddle::Paddle(int x, int y)
{
	mPosX = x; mPosY = y; //set paddle starting position

	//set collider starting dimensions
	for (int i = 0; i < PADDLE_HITBOXES; i++)
	{
		mPaddleCollider[i].w = PADDLE_WIDTH / PADDLE_HITBOXES; //width of each based on # of hit zones
		mPaddleCollider[i].h = PADDLE_HEIGHT; //height always the same

		if (i == 0) //first collider (left one) starts at left edge of paddle position
		{	
			mPaddleCollider[i].x = mPosX;
			mPaddleCollider[i].y = mPosY;
		}
		else //subsequent paddle boxes start at the right edge of the previous paddle
		{
			mPaddleCollider[i].x = mPaddleCollider[i-1].x + mPaddleCollider[i-1].w;
			mPaddleCollider[i].y = mPosY; //y posistion is static always

		}
	}

	//set initial velocity to 0
	mVelX = mVelY = 0;
}

Paddle::~Paddle()
{
	//nothing to do
}

void Paddle::handleEvent(SDL_Event &e)
{
	//core code for dispatching user inputs to proper functions
	
	//mouseover movement tracking:
	if (e.type == SDL_MOUSEMOTION)
	{
		mPosX = e.motion.x - (PADDLE_WIDTH/2);
		for (int i = 0; i < PADDLE_HITBOXES; i++)
		{
			if (i == 0)
				mPaddleCollider[i].x = mPosX;
			else
				mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
		}
		//if it hits an edge, stop 
		if (mPosX < 0)
		{
			mPosX = 0;
			for (int i = 0; i < PADDLE_HITBOXES; i++)
			{
				if (i == 0)
					mPaddleCollider[i].x = mPosX;
				else
					mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
			}
		}
		else if (mPosX > (WINDOW_WIDTH - PADDLE_WIDTH))
		{
			mPosX = WINDOW_WIDTH - PADDLE_WIDTH;
			for (int i = 0; i < PADDLE_HITBOXES; i++)
			{
				if (i == 0)
					mPaddleCollider[i].x = mPosX;
				else
					mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
			}
		}
	}

	//keyboard movement input:
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT: mVelX += PADDLE_SPEED; break;
		case SDLK_LEFT: mVelX -= PADDLE_SPEED; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT: mVelX -= PADDLE_SPEED; break;
		case SDLK_LEFT: mVelX += PADDLE_SPEED; break;
		}
	}
}

//Paddle should only move on the X-axis (static y axis, make no changes to Y)
void Paddle::move()
{
	//move the paddle left/right on the X axis
	mPosX += mVelX;
	for (int i = 0; i < PADDLE_HITBOXES; i++)
	{
		if(i == 0)
			mPaddleCollider[i].x = mPosX;
		else
			mPaddleCollider[i].x = mPaddleCollider[i-1].x + mPaddleCollider[i-1].w;
	}

	//if it hits an edge, stop 
	if (mPosX < 0 || mPosX > (WINDOW_WIDTH - PADDLE_WIDTH))
	{
		mPosX -= mVelX;
		for (int i = 0; i < PADDLE_HITBOXES; i++)
		{
			if (i == 0)
				mPaddleCollider[i].x = mPosX;
			else
				mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
		}
	}
}

void Paddle::render(SDL_Renderer* cRender)
{
	mPaddleTexture.render(mPosX, mPosY, cRender);
}

bool Paddle::loadTexture(std::string path, SDL_Renderer* cRender)
{
	return mPaddleTexture.loadFromFile(path, cRender);
}

//For automated testing with an AI paddle controller
void Paddle::moveAI(int ballPosX)
{
	//move the paddle left/right on the X axis
	mPosX += mVelX;
	for (int i = 0; i < PADDLE_HITBOXES; i++)
	{
		if (i == 0)
			mPaddleCollider[i].x = mPosX;
		else
			mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
	}

	if (mPosX + (PADDLE_WIDTH / 2) < ballPosX)
	{
		mPosX += 40;
		for (int i = 0; i < PADDLE_HITBOXES; i++)
		{
			if (i == 0)
				mPaddleCollider[i].x = mPosX;
			else
				mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
		}
	}
	else if (mPosX + (PADDLE_WIDTH / 2) > ballPosX)
	{
		mPosX -= 40;
		for (int i = 0; i < PADDLE_HITBOXES; i++)
		{
			if (i == 0)
				mPaddleCollider[i].x = mPosX;
			else
				mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
		}
	}

	//if it hits an edge, stop 
	if (mPosX < 0 || mPosX >(WINDOW_WIDTH - PADDLE_WIDTH))
	{
		mPosX -= mVelX;
		for (int i = 0; i < PADDLE_HITBOXES; i++)
		{
			if (i == 0)
				mPaddleCollider[i].x = mPosX;
			else
				mPaddleCollider[i].x = mPaddleCollider[i - 1].x + mPaddleCollider[i - 1].w;
		}
	}
}

//returns the address of the paddle collider to check for collisions with other objects
SDL_Rect* Paddle::getCollider(int index)
{
	return &mPaddleCollider[index];
}

int Paddle::getPaddleWidth()
{
	return PADDLE_WIDTH;
}

int Paddle::getPaddleHeight()
{
	return PADDLE_HEIGHT;
}

//AI move function
/*AI Function for testing - requires refactoring for breakout
void Paddle::moveAI(const Ball& ball)
{
	int AIPaddleSpeed = 3;
	//attempts to keep the AI paddle tracking the ball
	int x = ball.getBallPositionX(); //x location of the ball
	int y = ball.getBallPositionY(); //y location of the ball

	if((mPosY + (PADDLE_HEIGHT/2)) < y)
	{
		//track the ball 
		mPosY += AIPaddleSpeed;
		mPaddleCollider.y = mPosY;
	}
	else if ((mPosY + (PADDLE_HEIGHT / 2)) > y)
	{
		//track the ball
		mPosY -= AIPaddleSpeed;
		mPaddleCollider.y = mPosY;
	}
	
	//if it hits an edge, stop 
	if (mPosY < 0)
	{
		mPosY += AIPaddleSpeed;
		mPaddleCollider.y = mPosY;
	}
	if (mPosY > (SCREEN_HEIGHT - PADDLE_HEIGHT))
	{
		mPosY -= AIPaddleSpeed;
		mPaddleCollider.y = mPosY;
	}

}
*/
