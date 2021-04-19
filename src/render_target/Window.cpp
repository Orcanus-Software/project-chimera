// Window.cpp
#include <vttpch.h>
#include "Window.h"

namespace Chimera {
	Window::Window(const std::string& name, int width, int height, int hints_length, ...)
	{
		glfwSetErrorCallback(Window::LogError);

		va_list valist;

		// Try to initalize glfw or print an error and fail
		if (!glfwInit()) {
			Logger::getLogger()->error("GLFW could not initalize, aborting!");
			throw 1;
		}

		// NOAPI, so that BGFX can render agnostically
		glfwDefaultWindowHints();
		
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		if(hints_length % 2 == 0) {
			va_start(valist, hints_length);

			for(int i = 0; i < (hints_length/2); i++) {
				int hint = va_arg(valist, int);
				int value = va_arg(valist, int);

				glfwWindowHint(hint, value);
			}

			va_end(valist);
		} else {
			Logger::getLogger()->error("You must provide matched pairs of glfw enums and values to window constructor");
		}

		windowHandle = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

		// Test if the window exists
		if (!windowHandle) {
			Logger::getLogger()->error("Failed to create window, aborting.");
			throw 1;
		}

		setResizeCallback(Window::OnResize);
	}

	Window::Window(GLFWwindow* window)
	{
		this->windowHandle = window;
	}

	void Window::cleanUp()
	{
		glfwDestroyWindow(windowHandle);
	}

	Window::~Window()
	{

	}

	void Window::fillBGFXInit(bgfx::Init& init)
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
		init.resolution.reset = BGFX_RESET_VSYNC; // | BGFX_RESET_MSAA_X16;
	}

	glm::vec2 Window::getSize()
	{
		int width;
		int height;
		glfwGetWindowSize(windowHandle, &width, &height);

		return glm::vec2{ width, height };
	}

	void Window::LogError(int error, const char* description)
	{
		Logger::getLogger()->error("GLFW Error: {}: {}", error, description);
	}

	void Window::OnResize(GLFWwindow* window, int width, int height)
	{
		bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
		bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
	}

}