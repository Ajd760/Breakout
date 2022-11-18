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
	//constants and statics
	static const int BLOCK_QTY = 20;
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 600;
//	static int level; //starts at 0


	//variables/objects:
	SDL_Window* gameWindow;
	SDL_Surface* windowSurface;
	SDL_Renderer* mainRender;
	TTF_Font* font;
	LTexture backgroundTexture; 

	std::vector<Block> blocks; //vector of blocks

	//functions:
	Game();
	~Game();

	//core game functions: //
	bool init(); //start
	void gameLoop(); //play
	void close(); //game over
	/////////////////////////

	void spawnBlocks(int x, int y, int width, int height); //spawns a rectangle of blocks at origin x,y 
	void renderBlocks();
	void loadAllTextures(Ball* ball, Paddle* paddle);
};
