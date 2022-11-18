#pragma once
#include "../graphics/LTexture.h"

static unsigned int Block_Counter = 0;

class Block
{
public:
	//Block dimensions - TODO: use SDL_QueryTexture() to dynamically get dimensions from a block texture?
	static const int BLOCK_WIDTH = 40; //these dimensions are good for now
	static const int BLOCK_HEIGHT = 10;
	unsigned int blockID = Block_Counter++;

	LTexture blockTexture; //rendered texture
	SDL_Rect blockCollider; //rect colllider
	
	int x, y; //coordinates and dimensions

	Block();
	Block(int X, int Y);
	~Block();

	void render(SDL_Renderer* renderer); //show a block at its set position
	void destroy(); //destroy a block
	void loadTexture(std::string path, SDL_Renderer* renderer);

	int getBlockWidth() const;
	int getBlockHeight() const;
	SDL_Rect* getBlockCollider();
};

