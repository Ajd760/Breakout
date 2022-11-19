#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include "LTimer.h"
#include "gameObjects/Block.h"
#include "gameObjects/Paddle.h"
#include "gameObjects/Ball.h"

#define LOG printf

// moved to Constants.h
//const int SCREEN_FPS = 60;
//const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class Game
{
public:
	SDL_Renderer* mainRender;
	TTF_Font* font;
	LTexture backgroundTexture; 
	LTimer* timer;
	unsigned int lastFrameTicks;

	// Old variables to be removed
	std::vector<Block> blocks; //vector of blocks

	Game();
	~Game();
	bool init(); //start
	bool isRunning() const;
	void processInput(); //currently in gameLoop()
	void update(float deltaTime);
	void render();
	void loadLevel(int levelNum);
	void close(); //cleanup/gameover

	// Old functions to be removed or refactored
	void gameLoop(); //play
	void spawnBlocks(int x, int y, int width, int height); //spawns a rectangle of blocks at origin x,y 
	void renderBlocks();
	void loadAllTextures(Ball* ball, Paddle* paddle);

private:
	SDL_Window* gameWindow;
	SDL_Surface* windowSurface;
	bool bisRunning;
};
