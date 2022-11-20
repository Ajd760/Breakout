#include "Game.h"

Game::Game()
{
	gameWindow = nullptr;
	windowSurface = nullptr;
	mainRender = nullptr;
	font = nullptr;

	timer = new LTimer;
	time = new Time;
	manager = new GameObjectManager;

	bisRunning = false;
	lastFrameTicks = 0;
}

Game::~Game()
{
	close();

	manager->destroyEverything();

	gameWindow = nullptr;
	windowSurface = nullptr;
	mainRender = nullptr;
	font = nullptr;

	delete timer;
	delete manager;
}

//Initializes SDL subsystems. Currently Initializing:
// \SDL_VIDEO & Renderer
// \SDL_Audio & Mixer
// \IMG_PNG format
// \TTF Font
// - Also creates the game window and surface inside the window
bool Game::init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		LOG("Failed to load video! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else //create window
	{
		gameWindow = SDL_CreateWindow("BreakOut by AjD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (gameWindow == NULL)
		{
			LOG("Failed to create game window! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else //get renderer
		{
			mainRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (mainRender == NULL)
			{
				LOG("Failed to init Renderer! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			else //set render draw color default and init PNG image loading
			{
				SDL_SetRenderDrawColor(mainRender, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LOG("Failed to set PNG image loading! IMG_Error: %s\n", IMG_GetError());
					success = false;
				}
				else //open audio channel
				{
					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						LOG("Failed to open audio channel! Mix_Error: %s\n", Mix_GetError());
						success = false;
					}
					else //init TTF font
					{
						if (TTF_Init() == -1)
						{
							LOG("Failed to init TTF! TTF_Error: %s\n", TTF_GetError());
							success = false;
						}
						else //set screen surface
						{
							windowSurface = SDL_GetWindowSurface(gameWindow);
							if (windowSurface == NULL)
							{
								LOG("Failed to set surface on the window! SDL_Error: %s\n", SDL_GetError());
								success = false;
							}
						}
					}
				}
			}
		}
	}
	bisRunning = true;
	return success;
}

//Closes and cleans up all SDL/IMG/TTF/MIX data
void Game::close()
{
	SDL_FreeSurface(windowSurface);
	SDL_DestroyRenderer(mainRender);
	SDL_DestroyWindow(gameWindow);
	TTF_CloseFont(font);

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//spawns a rectangle of blocks starting at given x,y origin with quantity of blocks
//  equal to width*height
void Game::spawnBlocks(int x, int y, int width, int height)
{
	int columnCount = 0;
	int newX = x;

	LOG("About to add blocks...\n");

	for (int i = height; i > 0; i--) //for each row
	{
		for (int j = 0; j < width; j++)
		{
			Block toAdd(newX, y);
			blocks.push_back(toAdd); //add block to the vector
			columnCount++;
			LOG("Added block with blockID %i\n", toAdd.blockID);
			newX = newX + blocks[0].getBlockWidth(); //move the x coordinate to the right
		}

		newX = x; //reset newX to the left
		y = y + blocks[0].getBlockHeight(); //move the row coordinate down a block height
	}

	for (unsigned int i = 0; i < blocks.size(); i++)
	{
		blocks[i].loadTexture("red_block.png", mainRender);
	}

}

void Game::loadAllTextures(Ball* ball, Paddle* paddle)
{
	ball->loadTexture("ball.png", mainRender);
	paddle->loadTexture("space_paddle90px.png", mainRender);
}

void Game::gameLoop()
{
	SDL_Event e; //event handler

	//Pregame object spawning
	bool paddleCollidersAuto = false; //if set to true, this sets all paddle colliders to the same width
	Paddle* gamePaddle = new Paddle(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 30, paddleCollidersAuto, 10); //spawn paddle at the center middle of screen
	Ball* gameBall = new Ball();
	gameBall->reset(gamePaddle); //immediately reset ball back to paddle after spawn
	spawnBlocks(250, 200, 7, 7); //setting a 5x5 stack of blocks

	//pregame object texture loading
	loadAllTextures(gameBall, gamePaddle); //load all textures for objects

	//load background texture
	if (!(backgroundTexture.loadFromFile("background.png", mainRender)))
	{
		LOG("Failed to load background texture... Aborting startup\n");
		bisRunning = false;
	}

	//main game loop
	while (bisRunning)
	{
		processInput(gamePaddle, gameBall, e);
		update(gamePaddle, gameBall);
		render(gamePaddle, gameBall);
	}

	delete gamePaddle;
	delete gameBall;
	LOG("BYE, Felicia\n");
}

bool Game::isRunning() const
{
	return bisRunning;
}

void Game::processInput(Paddle* gamePaddle, Ball* gameBall, SDL_Event &e)
{
	//user input loop
	while (SDL_PollEvent(&e) != 0)
	{
		//allow program to run until user closes the window
		if (e.type == SDL_QUIT)
			bisRunning = false;
		if ((e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) && gameBall->isMoving == false)
		{
			//launch ball on space button press or mousebutton press
			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:
				gameBall->launch();
				printf("Launch ball!\n");
				break;

			default: break;
			}

			switch (e.button.state)
			{
			case SDL_PRESSED:
				gameBall->launch();
				printf("Launch ball!\n");
				break;

			default: break;
			}
		}
		//currently uses mouse movement or arrows to control paddle
		gamePaddle->handleEvent(e);
	}
}

void Game::update(Paddle* gamePaddle, Ball* gameBall)
{
	// handle time every update
	time->calcAndExecFrameDelay(); // wait for last frame if we need to
	time->updateDeltaTime();
	time->clampDeltaTime();
	time->getLastFrameTicks();

	for (unsigned int i = 0; i < manager->getGameObjCount(); i++)
	{
		manager->getGameObjects()[i]->update(time->getDeltaTime());
	}

	gamePaddle->move();
	gameBall->move(blocks, gamePaddle);
}

void Game::render(Paddle* gamePaddle, Ball* gameBall) //void Game::render()
{
	SDL_RenderClear(mainRender);
	//SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 0xff); //black background

	for (unsigned int i = 0; i < manager->getGameObjCount(); i++)
	{
		manager->getGameObjects()[i]->render();
	}

	//render background
	backgroundTexture.render(0, 0, mainRender);

	//render paddle and ball
	gamePaddle->render(mainRender);
	gameBall->render(mainRender);

	//raycast line visualization debugging
	//SDL_SetRenderDrawColor(mainRender, 255, 255, 255, 0xff);
	//SDL_RenderDrawLine(mainRender, gameBall->ballRay.originX, gameBall->ballRay.originY, gameBall->ballRay.originX, gameBall->ballRay.originY - gameBall->ballRay.length);

	//TODO: remove this once blocks are refactored into GameObjects
	for (unsigned int i = 0; i < blocks.size(); i++)
	{
		blocks[i].render(mainRender);
	}


	//refresh screen
	SDL_RenderPresent(mainRender);
}

void Game::loadLevel(int levelNum)
{
}
