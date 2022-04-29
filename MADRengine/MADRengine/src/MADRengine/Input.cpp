#include "Input.h"

std::vector<InputFrame> priorFrames;
std::vector<InputFrame>::iterator ptr;
MouseMode currMouseMode;

InputFrame currFrame;
bool isSelecting;

EVENT inputEvent;


//Defines when the player can input.
bool canInput;
void BlockAllInputs() { canInput = false; };
void UnblockAllInputs() { canInput = true; };


//static void cursorPoitionCallback(GLFWwindow* window, double xPos, double yPos)
//{
//	//WriteDebug(vecToStr(glm::vec2(xPos, yPos)));
//}
//static void cursorClickCallback(GLFWwindow* window, int button, int action, int mods)
//{
//	double xPos, yPos;
//	glfwGetCursorPos(window, &xPos, &yPos);
//
//	if (action == GLFW_PRESS)
//	{
//		//WriteDebug("Clicked at location: " + vecToStr(glm::vec2(xPos, yPos)));
//		inputEvent = EVENT(EventType::EngineEvent, "Mouse Click Input");
//		inputEvent.data.SetVector2("MousePos", glm::vec2(xPos, yPos));
//		if (button == GLFW_MOUSE_BUTTON_LEFT)
//			inputEvent.data.SetInt("LeftClick", 1);
//		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
//			inputEvent.data.SetInt("LeftClick", 0);
//
//		//QueueEvent(inputEvent);
//		//UIMouseSelect(glm::vec2(xPos, yPos));
//	}
//}

//sets the key event callback to CollectInputs() and fills the inputframe list with empty data so no input errors can occur.
void InputControlStartup()
{
	//glfwSetKeyCallback(window, CollectInputs);
	//glfwSetCursorPosCallback(window, cursorPoitionCallback);
	for (int i = 1; i <= MAX_SAVED_INPUTFRAMES; i++)
	{
		ptr = priorFrames.begin();
		ptr = priorFrames.insert(ptr, InputFrame());
	}

	UnblockAllInputs();
}

InputFrame CollectInputs() {
	InputFrame newFrame = InputFrame();
	glm::bvec4 dirs = currFrame.RAW_DIRECTIONS();
	glm::bvec4 buttons = currFrame.RAW_BUTTONS();
	glm::bvec4 buttons2 = currFrame.RAW_BUTTONS2();
	if (canInput)
	{

#pragma region Press
#pragma endregion

#pragma region Release
		
#pragma endregion
		newFrame = InputFrame(dirs, buttons, buttons2);
		return newFrame;
	}
	else return InputFrame(dirs, buttons, buttons2);
}

//Moves the inputFrame list forward to the current frame and erases the oldest one.
void SaveInputs()
{
	ptr = priorFrames.begin();
	ptr = priorFrames.insert(ptr, currFrame);
	currFrame = CollectInputs();
	priorFrames.pop_back();
}

//Runs inputs. Called once every frame to prevent input errors in a singleplayer environment.
//If you wanted to handle multiplayer or an update-based framework, you'd need to change this to compensate.
//void RunInputs()
//{
//	//WriteDebug("dirs " + vecToStr(currFrame.RAW_DIRECTIONS()));
//	//WriteDebug("buts " + vecToStr(currFrame.RAW_BUTTONS()));
//
//	Camera* cam = FindCamera(17);
//	//WriteDebug(vecToStr(currFrame.RAW_DIRECTIONS()) + " " + vecToStr(currFrame.RAW_BUTTONS()));
//	if (currFrame.UP() && !priorFrames[0].UP())
//	{
//		//testSelector.MoveSelector(North);
//
//		//cam->RotateCamera(glm::vec3(0, 5, 0));
//
//
//		GetMapEntity(0)->Walk(GetMapEntity(0)->GetCurrentFacing(1));
//		//for (int i = 0; i < walkForward.size(); i++)
//			//testGameObject.MoveObjectRelative(GetMapEntity(0)->RotateCoords(walkForward[i]));
//		//WriteDebug(vecToStr(testGameObject.GetTransform().GetWorldPosition()));
//		//testGameObject.MoveObjectRelative(glm::vec3(0,0,1));
//	}
//	if (currFrame.RIGHT() && !priorFrames[0].RIGHT())
//	{
//		//testSelector.MoveSelector(East);
//
//		//cam->RotateCamera(glm::vec3(-5, 0, 0));
//
//
//		GetMapEntity(0)->Rotate(0);
//
//
//		//testGameObject.MoveObjectRelative(glm::vec3(-1, 0, 0));
//
//	}
//	if (currFrame.LEFT() && !priorFrames[0].LEFT())
//	{
//		//testSelector.MoveSelector(West);
//
//		//cam->RotateCamera(glm::vec3(5, 0, 0));
//		GetMapEntity(0)->Rotate(1);
//		//testGameObject.MoveObjectRelative(glm::vec3(1, 0, 0));
//	}
//
//	if (currFrame.DOWN() && !priorFrames[0].DOWN())
//	{
//		//testSelector.MoveSelector(South);
//
//		//cam->RotateCamera(glm::vec3(0, -5, 0));
//
//		//cam->RotateCamera(glm::vec3(0, -5, 0));
//		//testGameObject.MoveObjectRelative(glm::vec3(1,0,0));
//		//WriteDebug(vecToStr(testGameObject.GetTransform().GetWorldPosition()));
//		//WriteDebug((int)priorFrames[0].DOWN() + " curr: " + (int)currFrame.DOWN());
//		GetMapEntity(0)->Flip();
//
//
//		//testGameObject.MoveObjectRelative(glm::vec3(0, 0, -1));
//	}
//	else
//
//		if (currFrame.BUTTON_1())
//		{
//			//testSelector.SelectNode();
//
//			testGameObject.MoveObjectRelative(glm::vec3(0, 1, 0));
//			//cam->RotateCamera(glm::vec3(0, 5, 0));
//
//			//cam->RotateCamera(glm::vec3(0, 0, -5));
//			//GetRenderObject(1)->objModel.StartAnim("AnimLoadTest");
//		}
//	if (currFrame.BUTTON_2())
//	{
//		//testSelector.InteractWithItem();
//
//		//testStatus.PlayerStatusStartup();
//
//		//testGameObject.MoveObjectRelative(glm::vec3(0, -1, 0));
//		cam->RotateCamera(glm::vec3(0, -5, 0));
//		//ResizeWindow(GetWindow(), glm::vec2(640, 360));
//
//		//cam->RotateCamera(glm::vec3(0, 0, 5));
//		//cam->PlayCameraAction(LookMiddleFromUp);
//		//GetRenderObject(1)->objModel.StartAnim("AnimLoadTest");
//	}
//	if (currFrame.BUTTON_3() && !priorFrames[0].BUTTON_3())
//	{
//		//newTest.GetModelPTR()->textures = LoadObjectTextures(FileType::ObjTextureFile, "TestTextureSwap.mtl");
//		//AnimData newMap = *(AnimData*)GetLoadController()->RetrieveData(FileType::AnimFile, "AnimLoadTest", 0);
//		//WriteDebug(newMap.GetLength());
//		//testStatus.TestRemoval();
//		//ResizeWindow(GetWindow(), glm::vec2(640, 360), false);
//
//	}
//	if (currFrame.BUTTON_4() && !priorFrames[0].BUTTON_4())
//	{
//		//AddUIElement(&newTest, Model("UIPlaneTest", "UIPlaneTest.mtl"));
//		//ResizeWindow(GetWindow(), glm::vec2(1920,1080), true);
//		cam->RotateCamera(glm::vec3(0, 0, 5));
//
//		//GetRenderObject(1)->objModel.StartAnim("AnimLoadTest");
//
//		//InventoryItem testItem(glm::vec2(2), "whatever", EmptyItemType);
//		//testInventory.AddItem(testItem, glm::vec2(0));
//
//	}
//	cam->MoveCamera(testGameObject.GetTransform().GetWorldPosition());
//
//	if (currFrame.ESCAPE())
//	{
//		ResizeWindow(GetWindow(), glm::vec2(640, 360), false);
//	}
//}