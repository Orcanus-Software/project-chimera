// window.h
#pragma once 

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>
#include "debug/Log.h"
#include <bx/bx.h>
#include <bx/math.h>

namespace VTT {
	class Window 
	{
	public:
		Window(const char* name, int width, int height);
		~Window();

		GLFWwindow* getHandle() { return windowHandle; }

		void fillBGFXInit(bgfx::Init& init);

		bx::Vec3 getSize();
	private:
		GLFWwindow* windowHandle;
	};
}