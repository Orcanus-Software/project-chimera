// window.h
#pragma once 

#include <vttpch.h>

#include "debug/Log.h"

namespace VTT {
	class Window 
	{
	public:
		Window(const char* name, int width, int height);
		Window(GLFWwindow* windowHandle);
		void CleanUp();
		~Window();

		GLFWwindow* getHandle() { return windowHandle; }

		void fillBGFXInit(bgfx::Init& init);

		glm::vec2 getSize();

		int getAttribute(GLenum param) {return glfwGetWindowAttrib(windowHandle, param); };

		void setVisible(bool visible) { if(!visible) { glfwHideWindow(windowHandle); } else { glfwShowWindow(windowHandle); } };
		bool isVisible() {return getAttribute(GLFW_VISIBLE); };

		void focusWindow() { glfwFocusWindow(windowHandle); }
		void requestFocus() { glfwRequestWindowAttention(windowHandle); }

		void setName(const char * name) { glfwSetWindowTitle(windowHandle, name); }
		void setIcons(int size, GLFWimage * images) { glfwSetWindowIcon(windowHandle, size, images); }

		void setMinimized(bool minimize) {if (minimize) { glfwIconifyWindow(windowHandle); } else { glfwRestoreWindow(windowHandle); }}
		bool isMinimized() { return getAttribute(GLFW_ICONIFIED); }
	private:
		GLFWwindow* windowHandle;
	};
}