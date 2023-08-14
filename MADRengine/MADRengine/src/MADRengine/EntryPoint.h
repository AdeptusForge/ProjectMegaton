#pragma once
#include "MADRpch.h"
#include "Trace.h"

namespace EngineCore
{
	bool Startup() 
	{
		Logging::Startup();







		return true;
	}
	void Loop()
	{
		while (true) 
		{
			
		}
	}

	bool Shutdown() 
	{


		Logging::Log("Engine Shutdown Successful");
		return true;
	}
}







