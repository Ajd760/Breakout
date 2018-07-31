#include "Game.h"

//BreakOut game
//by: Alan Doose


//Running list of next steps:
//	-cleanup ball and paddle classes (move collision handling into its own class/system)
//	-implement math library (linear algebra)
//	-implement better collision detection and resolution
//	-begin an actual game framework (menu screen, options, levels, scoring, statistics, powerups, win state, etc)

int main(int argc, char* args[])
{
	Game newGame; //game instance

	if (!newGame.init()) //if game fails to load
	{
		LOG("Failed to initialize game! Closing...\n");
	}
	else //game loaded, begin play
	{
		LOG("About to enter game loop...\n");
		newGame.gameLoop();
	}

	newGame.close(); //cleanup

	return 0;
}

