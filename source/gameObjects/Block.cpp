#include "Block.h"



Block::Block()
{
	x = 0;
	y = 0;
	blockCollider.w = 0;
	blockCollider.h = 0;
}

Block::Block(int X, int Y)
{
	x = X;
	y = Y;
	blockCollider.x = X;
	blockCollider.y = Y;
	blockCollider.w = BLOCK_WIDTH;
	blockCollider.h = BLOCK_HEIGHT;
}


Block::~Block()
{
	destroy();
}

void Block::render(SDL_Renderer* renderer)
{
	blockTexture.render(x, y, renderer);
}

void Block::destroy()
{
	blockTexture.free();
}

void Block::loadTexture(std::string path, SDL_Renderer* renderer)
{
	blockTexture.loadFromFile(path, renderer);
}

int Block::getBlockWidth() const
{
	return BLOCK_WIDTH;
}

int Block::getBlockHeight() const
{
	return BLOCK_HEIGHT;
}

SDL_Rect* Block::getBlockCollider()
{
	return &blockCollider;
}
