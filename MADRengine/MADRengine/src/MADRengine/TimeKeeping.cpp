#include "TimeKeeping.h"
#include "SDL_timer.h"

#define PHYSICS_UPDATE_RATE 120

//Shows number of ticks since last update, useful for running time-based functions.
Uint64 deltaTime;
Uint64 startup = SDL_GetPerformanceCounter();
Uint64 totalTicksSinceStartup;
float physicsFrameInTicks = (float)(SDL_GetPerformanceFrequency() / (float)PHYSICS_UPDATE_RATE);
Uint64 currTick;
Uint64 priorTick;
bool lastFrameRender;
int totalRenders = 0;

std::vector<Event_Timer> allTimers;




//Gets the current ticks per frame. Used mostly in timestep testing.
int GetCurrentTick()
{
	return (int)(currTick / physicsFrameInTicks);
};

//Begins time startup.
void TimeStartup()
{
	priorTick = startup;
	//WriteDebug(to_string(physicsFrameInTicks));
};

//Updates game time based on the computer's clock and the current tick. 
//Updates Rendering, Physics, Inputs, and map interactions.
void UpdateTime(GLFWwindow* window)
{
	currTick = SDL_GetPerformanceCounter();
	deltaTime = currTick - priorTick;


	if (deltaTime >= physicsFrameInTicks)
	{
		priorTick = currTick;

		//PhysicsUpdate();

		//EventManagerUpdate();
		if (!lastFrameRender)
		{
			//RenderUpdate(window);
			//SaveInputs(window);
			//RunInputs();
			//UpdateMap();
			lastFrameRender = true;
		}
		else
			lastFrameRender = false;
	}
}