// Window.cpp
#include <vttpch.h>
#include "Window.h"

VTT::Window::Window(const char * name, int width, int height) 
{
	// Try to initalize glfw or print an error and fail
	if (!glfwInit()) {
		Logger::getLogger()->error("GLFW could not initalize, aborting!");
		throw 1;
	}

	// NOAPI, so that BGFX can render agnostically
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	windowHandle = glfwCreateWindow(width, height, name, nullptr, nullptr);

	// Test if the window exists
	if (!windowHandle) {
		Logger::getLogger()->error("Failed to create window, aborting.");
		throw 1;
	}
}

VTT::Window::Window(GLFWwindow* window) 
{
	this->windowHandle = window;
}

void VTT::Window::CleanUp()
{
	glfwDestroyWindow(windowHandle);
}

VTT::Window::~Window() 
{

}

void VTT::Window::fillBGFXInit(bgfx::Init& init) 
{
	#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(windowHandle);
	#elif BX_PLATFORM_OSX
	init.platformData.nwh = glfwGetCocoaWindow(windowHandle);
	#elif BX_PLATFORM_WINDOWS
	init.platformData.nwh = glfwGetWin32Window(windowHandle);
	#endif

	int win_width, win_height;
	glfwGetWindowSize(windowHandle, &win_width, &win_height);
	init.resolution.width = (uint32_t)win_width;
	init.resolution.height = (uint32_t)win_height;
	init.resolution.reset = BGFX_RESET_VSYNC;
}

glm::vec2 VTT::Window::getSize()
{
	int width;
	int height;
	glfwGetWindowSize(windowHandle, &width, &height);
	
	return glm::vec2{width, height};
}
