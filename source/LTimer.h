#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//program timer class
class LTimer
{
public:
	LTimer();

	//basic functionality
	void start();
	void stop();
	void pause();
	void unpause();
	void restart();

	//get the timer's time
	Uint32 getTicks();

	//checks
	bool isPaused();
	bool isStarted();

private:
	//the clock time when the timer started
	Uint32 mStartTicks;

	//the time stored when the timer is paused
	Uint32 mPausedTicks;

	//timer status
	bool mPaused;
	bool mStarted;
};

