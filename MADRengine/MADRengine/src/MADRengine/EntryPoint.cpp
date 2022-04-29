#include "MADRengine/MADRpch.h"
#include "EntryPoint.h"
#include "SDL.h"

bool EngineStartup() 
{
	SDL_Init(SDL_INIT_VIDEO);
	return true;
}

bool EngineRunning() 
{

	return true;
}
void CentralLoop() 
{
	while (EngineRunning())
	{
		UpdateTime();
	}
}