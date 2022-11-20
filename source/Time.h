#pragma once

#include <SDL.h>

#include "Constants.h"

class Time
{
public:
	Time();
	~Time();
	float getDeltaTime() const;
	unsigned int getLastFrameTicks() const;
	void updateDeltaTime();
	void clampDeltaTime();
	void updateLastFrameTicks();
	void calcAndExecFrameDelay();

private:
	float deltaTime;
	unsigned int lastFrameTicks;
};

