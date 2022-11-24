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

	//query and set chunk volumes - TODO: make something that does this and expose it via a static or something for global volume control
	int volume = Mix_VolumeChunk(ballLaunch, -1); // -1 to query current volumet
	Mix_VolumeChunk(ballLaunch, (int)(volume*.2)); //set volume to 20% of the default (cuz it's loud af by default
	volume = Mix_VolumeChunk(ballHitPaddle, -1);
	Mix_VolumeChunk(ballHitPaddle, (int)(volume * .2)); 
	volume = Mix_VolumeChunk(ballHitBlock1, -1); 
	Mix_VolumeChunk(ballHitBlock1, (int)(volume * .2)); 
	volume = Mix_VolumeChunk(ballHitBlock2, -1); 
	Mix_VolumeChunk(ballHitBlock2, (int)(volume * .2));

	if (ballHitPaddle == NULL || ballHitBlock1 == NULL || ballHitBlock2 == NULL || ballLaunch == NULL)
	{
		printf("Problem loading a sound! Mix_Error: %s\n", Mix_GetError());
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
