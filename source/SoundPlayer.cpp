#include "SoundPlayer.h"

int SoundPlayer::randomizer;

SoundPlayer::SoundPlayer()
{
	ballLaunch = NULL;
	ballHitPaddle = NULL;
	ballHitBlock1 = NULL;
	ballHitBlock2 = NULL;
	SoundPlayer::randomizer = 0;
}


SoundPlayer::~SoundPlayer()
{
	close();
}

bool SoundPlayer::loadSounds()
{
	bool success = true;

	ballLaunch = Mix_LoadWAV("Sounds/rlaunch.wav");
	ballHitPaddle = Mix_LoadWAV("Sounds/normalhit.wav");
	ballHitBlock1 = Mix_LoadWAV("Sounds/iceball.wav");
	ballHitBlock2 = Mix_LoadWAV("Sounds/slimeball.wav");

	if (ballHitPaddle == NULL || ballHitBlock1 == NULL || ballHitBlock2 == NULL || ballLaunch == NULL)
	{
		printf("Problem loading a sound! Mix_Error: %s", Mix_GetError());
		success = false;
	}

	return success;
}

void SoundPlayer::launchSound()
{
	Mix_PlayChannel(-1, ballLaunch, 0);
	SoundPlayer::randomizer++;
}

void SoundPlayer::hitPaddle()
{
	Mix_PlayChannel(-1, ballHitPaddle, 0);
	SoundPlayer::randomizer++;
}

void SoundPlayer::hitBlock()
{
	if (SoundPlayer::randomizer % 2 == 0)
		Mix_PlayChannel(-1, ballHitBlock1, 0);
	else
		Mix_PlayChannel(-1, ballHitBlock2, 0);

	SoundPlayer::randomizer++;
}

void SoundPlayer::close()
{
	Mix_FreeChunk(ballLaunch);
	Mix_FreeChunk(ballHitPaddle);
	Mix_FreeChunk(ballHitBlock1);
	Mix_FreeChunk(ballHitBlock2);

	ballLaunch = NULL;
	ballHitPaddle = NULL;
	ballHitBlock1 = NULL;
	ballHitBlock2 = NULL;

}
