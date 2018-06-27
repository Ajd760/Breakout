#include "LTimer.h"

/*********************************/
/* LTimer Class implementation */
/*********************************/
LTimer::LTimer()
{
	mStartTicks = 0;
	mPausedTicks = 0;
	mStarted = false;
	mPaused = false;
}

//starts the timer
void LTimer::start()
{
	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;

}

//basically resets the timer by restoring default values
void LTimer::stop()
{
	mStarted = false;
	mPaused = false;
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	if (mStarted && !mPaused) //if the timer is started and not paused
	{
		mPaused = true;
		mPausedTicks = SDL_GetTicks() - mStartTicks; //save the time when the timer was paused
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	if (mPaused && mStarted) //if the timer has started and is paused
	{
		mStartTicks = SDL_GetTicks() - mPausedTicks; //reset the timer stating reference time
		mPaused = false;
		mPausedTicks = 0; //reset the paused ticks
	}
}

Uint32 LTimer::getTicks()
{
	//the actual timer time
	Uint32 time = 0;

	if (mStarted) //if the timer is started
	{
		if (mPaused) //if the timer is paused
		{
			time = mPausedTicks; //return the time when the timer was paused
		}
		else //else the timer is not paused
		{
			time = SDL_GetTicks() - mStartTicks; //return the current time minus the start time
		}
	}

	return time;
}

void LTimer::restart()
{
	stop();
	start();
}

bool LTimer::isPaused()
{
	return mPaused && mStarted; //only return true if the timer has started and is currently paused
}

bool LTimer::isStarted()
{
	return mStarted;
}
