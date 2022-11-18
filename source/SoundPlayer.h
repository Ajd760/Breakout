#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

class SoundPlayer
{
private:
	static int randomizer;
public:
	SoundPlayer();
	~SoundPlayer();

	Mix_Chunk* ballLaunch;
	Mix_Chunk* ballHitPaddle;
	Mix_Chunk* ballHitBlock1;
	Mix_Chunk* ballHitBlock2;

	bool loadSounds();
	void launchSound();
	void hitPaddle();
	void hitBlock();
	void close();
};

