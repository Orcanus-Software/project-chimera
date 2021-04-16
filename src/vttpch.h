#include <iostream>
#include <memory>

#include <spdlog/spdlog.h>

#include <bx/bx.h>
#include <bx/math.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <par_shapes.h>

#include "tinyfiledialogs.h"

#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <Yoga.h>
#include <YGNode.h>
#include <YGLayout.h>

#include <glm/glm.hpp>