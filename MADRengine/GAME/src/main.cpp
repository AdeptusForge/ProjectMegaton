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




	return 0;
}