// window.h
#pragma once 

#include <vttpch.h>

#include "debug/Log.h"

namespace VTT {
	class Window 
	{
	public:
		Window(const char* name, int width, int height);
		~Window();

		GLFWwindow* getHandle() { return windowHandle; }

		void fillBGFXInit(bgfx::Init& init);

		glm::vec2 getSize();
	private:
		GLFWwindow* windowHandle;
	};
}