#pragma once
#include "MADRengine/MADRpch.h"
#include "Events.h"

class Collider: public EventListener
{
	void EventResponse(EVENT e) 
	{
		InputFrame i = e.data.GetInputs();
	}
};