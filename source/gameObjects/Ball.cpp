#include "Ball.h"



Ball::Ball() : MASS(0.1f)
{
	ballPos_X = ballPos_Y = 0;
	ballCollider.x = ballCollider.y = 0;
	ballCollider.r = BALL_RADIUS;

	ballRay.originX = ballRay.originY = 0;
	ballRay.length = ballCollider.r - BALL_SPEED;

	isMoving = false;

	//init sound chunks
	if (!soundPlayer.loadSounds())
	{
		printf("Failed to load sounds!\n");
	}
}

Ball::Ball(float m) : MASS(m)
{
	ballPos_X = ballPos_Y = 0;
	ballCollider.x = ballCollider.y = 0;
	ballCollider.r = BALL_RADIUS;

	ballRay.originX = ballRay.originY = 0;
	ballRay.length = ballCollider.r - BALL_SPEED;

	isMoving = false;

	//init sound chunks
	if (!soundPlayer.loadSounds())
	{
		printf("Failed to load sounds!\n");
	}
}

Ball::~Ball()
{
	ballTexture.free();
	soundPlayer.close();
}

bool Ball::loadTexture(std::string path, SDL_Renderer* renderer)
{
	return ballTexture.loadFromFile(path, renderer);
}

void Ball::render(SDL_Renderer * renderer)
{
	ballTexture.render(ballPos_X, ballPos_Y, renderer);
	//printf("Rendering ball at %i, %i\n", ballPos_X, ballPos_Y);
}

void Ball::launch()
{
	ballVelocity_Y = BALL_SPEED;
	soundPlayer.launchSound();
	isMoving = true;
}

void Ball::move(std::vector<Block>& blocks, Paddle* paddle)
{
	if (!isMoving)
	{
		reset(paddle);
	}
	else
	{
		SDL_Rect* col = NULL; //holds any item collided with
	
		//move the ball
		ballPos_X += ballVelocity_X;
		ballPos_Y += ballVelocity_Y;
		ballCollider.x = ballPos_X + BALL_RADIUS;
		ballCollider.y = ballPos_Y + BALL_RADIUS;
		ballRay.originX = ballCollider.x;
		ballRay.originY = ballCollider.y;

		//check for collisions with blocks and paddle
		col = detectCollision(blocks, paddle);
		if (col != NULL)
		{
			//NEED TO FIND A MORE ELEGANT SOLUTION THAN HARDCODING THIS!!!
			if (col == paddle->getCollider(0)) //left side of paddle
			{
				printf("collided with left side of paddle\n");
				ballVelocity_Y *= -1;
				ballVelocity_X = -5;
			}
			else if (col == paddle->getCollider(1)) //middle of paddle
			{
				printf("collided with middle of paddle\n");
				ballVelocity_Y *= -1;
			}
			else if (col == paddle->getCollider(2))
			{
				printf("collided with right side of paddle\n");
				ballVelocity_Y *= -1;
				ballVelocity_X = 5;
			}
			else //else collided with a block
			{
				//col points to the specific block that was hit (should)
				printf("collided with a block\n");
				ballVelocity_Y *= -1;
				soundPlayer.hitBlock();
			}
			soundPlayer.hitPaddle();
		}

		//check for collision with edges
		if (ballCollider.x - ballRay.length < 0)
			ballVelocity_X = 4;
		if (ballCollider.x + ballRay.length > WINDOW_WIDTH)
			ballVelocity_X = -4;
		if (ballCollider.y - ballRay.length < 0)
			ballVelocity_Y *= -1;
		if (ballCollider.y > WINDOW_HEIGHT)
			reset(paddle);
	}
}

void Ball::reset(Paddle* paddle)
{
	ballVelocity_X = 0;
	ballVelocity_Y = 0;

	ballPos_X = paddle->mPosX + ((paddle->getPaddleWidth() / 2) - ballCollider.r);
	ballPos_Y = paddle->mPosY - ((paddle->getPaddleHeight()) - ballCollider.r);

	ballCollider.x = ballPos_X + BALL_RADIUS;
	ballCollider.y = ballPos_Y + BALL_RADIUS;

	ballRay.originX = ballCollider.x;
	ballRay.originY = ballCollider.y;

	isMoving = false;
}


//checks for collisions with blocks and paddle, returns a pointer to the object collided with so it can be handled in move()
SDL_Rect* Ball::detectCollision(std::vector<Block>& blocks, Paddle* paddle)
{
	int cX, cY; //closest points on paddle/block

	//check paddle collision:

	for (int i = 0; i < paddle->PADDLE_HITBOXES; i++)
	{

		//get x coord
		if (ballCollider.x < paddle->mPaddleCollider[i].x) //if closest x point is on left side of paddle (i.e. ball center is to the left of paddle)
			cX = paddle->mPaddleCollider[i].x;
		else if (ballCollider.x > paddle->mPaddleCollider[i].x + paddle->mPaddleCollider[i].w) //else if closest x point is on right side of paddle
			cX = paddle->mPaddleCollider[i].x + paddle->mPaddleCollider[i].w;
		else //else closest x point is wherever the circle's x point is (it's within the paddle's x range)
			cX = ballCollider.x;
	
		//get y coord - same idea as x (no iteration here, y position is static for EVERY hitbox)
		if (ballCollider.y < paddle->mPosY)
			cY = paddle->mPosY;
		else if (ballCollider.y > paddle->mPosY + paddle->PADDLE_HEIGHT)
			cY = paddle->mPosY + paddle->PADDLE_HEIGHT;
		else
			cY = ballCollider.y;

		//check distance and return paddle collider if a collision occured
		if (distanceSquared(ballCollider.x, ballCollider.y, cX, cY) < ballCollider.r*ballCollider.r) //if the distance squared between the circle center and the closest point on the paddle is less than the ball radius squared
			return paddle->getCollider(i);
	}


	printf("Block Vector size is %i\n", blocks.size());
	//check collision with every block
	for (int i = 0; i < blocks.size() - 1; i++)
	{
		//get x coord
		if (ballCollider.x < blocks[i].x) //if closest x point is on left side of block (i.e. ball center is to the left of the block)
			cX = paddle->mPosX;
		else if (ballCollider.x > blocks[i].x + blocks[i].BLOCK_WIDTH) //else if closest x point is on right side of the block
			cX = blocks[i].x + blocks[i].BLOCK_WIDTH;
		else //else closest x point is wherever the circle's x point is (it's within the blocks's x range)
			cX = ballCollider.x;

		//get y coord - same idea as x
		if (ballCollider.y < blocks[i].y)
			cY = paddle->mPosY;
		else if (ballCollider.y > blocks[i].y + blocks[i].BLOCK_HEIGHT)
			cY = blocks[i].y + blocks[i].BLOCK_HEIGHT;
		else
			cY = ballCollider.y;

		//check distance and return block collider if a collision occured. Also destroy block and remove from vector
		if (distanceSquared(ballCollider.x, ballCollider.y, cX, cY) < ballCollider.r*ballCollider.r)
		{
			Block destroyed = blocks[i]; //copy the block
			blocks[i].destroy(); //free texture
			blocks.erase(blocks.cbegin() + i); //not quite working as intended... supposed to erase from vector, BUT also removes last block (visually) in vector
			return destroyed.getBlockCollider(); //return the copied collider location iot remove it from the rendering loop
		}
	}

	//if no collisions detected, return null
	return NULL;
}

double Ball::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

CircleCollider * Ball::getCollider()
{
	return &ballCollider;
}

//TODO: look up the trig funtion to apply to the force equation
float Ball::colllisionAngle(SDL_Rect * col)
{

	return 0.0f;
}