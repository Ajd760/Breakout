#pragma once
#include "math_header.h"
//physics functions header file

float xFinal(float xi, float a, unsigned int ticks)
{//TODO: static cast result? find a better method
	float seconds = ticks / 1000; //convert ms to s
	return (float)(xi + 0.5f*a*(seconds*seconds));
}

float vFinal(float vi, float a, unsigned int ticks)
{//TODO: static cast result? find a better method
	return (float)(vi + (a*(ticks / 1000)));
}

float vFinalSq(float vi, float a, unsigned int ticks)
{//TODO: static cast result? find a better method
	float seconds = (float)(ticks / 1000); //convert ms to s
	float viSq = vi*vi;
	return (viSq + (2 * a*(seconds*seconds)));
}

float radDir()
{
	//
}