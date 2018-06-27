#include "Game.h"

//BreakOut game
//by: Alan Doose


//Running list of next steps:
//	-create class for paddle and ball
//	-determine how to handle blocks.. 

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

