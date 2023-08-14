#pragma once
#include <stdlib.h>
#include <crtdbg.h>
#include <pmpch.h>
#include "MADRengine/MADRpch.h"
#include "MADRengine/EntryPoint.h"




int main(int argc, char** argv)
{
	argv;
	argc;

	if (EngineCore::Startup()) 
	{
		EngineCore::Loop();
	}
	if (EngineCore::Shutdown())
		return 0;


	return 1;
}