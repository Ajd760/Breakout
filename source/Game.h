#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include "GameObjectManager.h"
#include "LTimer.h"
#include "Time.h"
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
	TTF_Font* font;
	LTexture backgroundTexture; 
	LTimer* timer;
	GameObjectManager* manager;
	Time* time;
	unsigned int lastFrameTicks;

	// Old variables to be removed /////
	std::vector<Block> blocks; //vector of blocks - TODO: convert to gameObjects
	////////////////////////////////////

	Game();
	~Game();
	bool init(); // SDL init stuff
	bool isRunning() const;
	//void processInput(); //currently in gameLoop()
	void processInput(Paddle* gamePaddle, Ball* gameBall, SDL_Event &e);//temp processInput passing in old game classes while refactor is in progress
	//void update();
	void update(Paddle* gamePaddle, Ball* gameBall); //temp update passing in old game classes while refactor is in progress
	//void render();
	void render(Paddle* gamePaddle, Ball* gameBall); //temp render passing in old game classes while refactor is in progress
	void loadLevel(int levelNum);
	void close(); //cleanup/gameover

	// Old functions to be removed or refactored /////
	void gameLoop(); //play
	void spawnBlocks(int x, int y, int width, int height); //spawns a rectangle of blocks at origin x,y 
	void loadAllTextures(Ball* ball, Paddle* paddle);
	//////////////////////////////////////////////////

private:
	SDL_Renderer* mainRender;
	SDL_Surface* windowSurface;
	SDL_Window* gameWindow;
	bool bisRunning;
};
