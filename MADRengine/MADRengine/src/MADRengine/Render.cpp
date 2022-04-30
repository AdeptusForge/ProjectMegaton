
#include "Render.h"
GLFWwindow* rWindow;

GLFWwindow** RenderStartup()
{
	if (glfwInit()) 
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		rWindow = glfwCreateWindow(1920, 1080, "TestWindow", NULL, NULL);
		if (rWindow != NULL)
		{


			glfwMakeContextCurrent(rWindow);
			//glfwSetFramebufferSizeCallback(rWindow, framebuffer_size_callback);
			//std::cout << "GLAD initialized successfully.\n";

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				std::cerr << "GLAD failed to initialize\n";
		}
	}

	return &rWindow;
}

void RenderUpdate(GLFWwindow* window)
{
	//glfwSwapBuffers(rWindow);
	//glFlush();
	glfwPollEvents();
}
