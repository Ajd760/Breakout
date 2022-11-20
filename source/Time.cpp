#include "Time.h"

Time::Time()
{
	deltaTime = 0.0f;
	lastFrameTicks = SDL_GetTicks();
}

Time::~Time()
{
}

float Time::getDeltaTime() const
{
	return deltaTime;
}

unsigned int Time::getLastFrameTicks() const
{
	return lastFrameTicks;
}

// calculates time since last frame was rendered
void Time::updateDeltaTime()
{
	deltaTime = (SDL_GetTicks() - lastFrameTicks) / 1000.0f;
}

// clamp delta time to prevent a lag or pause from making time warp forward
// TODO: send in the clamp as a parameter instead of hardcoding it?
void Time::clampDeltaTime()
{
	// sets deltaTime to 0.05f if deltaTime is over 0.05 seconds, otherwise use value calculated in updateDeltaTime()
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
}

// call every update, keeps track of time at last update()
void Time::updateLastFrameTicks()
{
	lastFrameTicks = SDL_GetTicks();
}

void Time::calcAndExecFrameDelay()
{
	// calc delay in ms as desired frame window minus delta time between cycles in ms
	// TODO: should use deltaTime converted back to ms here? or too much messing around
	int delayTime = SCREEN_TICKS_PER_FRAME_TARGET - (SDL_GetTicks() - lastFrameTicks);

	// if delayTime is > 0 and <= to desired frame time, delay to hit the target frame rate
	if (delayTime > 0 && delayTime <= SCREEN_TICKS_PER_FRAME_TARGET)
		SDL_Delay(delayTime);
}
