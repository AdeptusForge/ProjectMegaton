#include "MADRpch.h"
#include "IDControl.h"

std::map<std::string, IDController> allIDControllers;

//Sets up various needed IDControllers for the engine.
void IDStartup()
{
	allIDControllers.insert(std::pair<std::string, IDController>("RenderObjects", IDController(TOTAL_RENDER_ID)));
	allIDControllers.insert(std::pair<std::string, IDController>("InventoryItems", IDController(TOTAL_INVENTORY_ID)));
	allIDControllers.insert(std::pair<std::string, IDController>("Cameras", IDController(32)));
}

//Retrieves an ID controller by string checking
//TODO:: Make a faster checking method that is as easily read as strings
IDController* GetIDController(std::string purpose)
{
	return &allIDControllers.at(purpose);
}