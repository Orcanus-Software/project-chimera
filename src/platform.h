// Defines some values on a per platform basis
#include <bgfx/platform.h>

// BGFX Init macro definition
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#define SET_PLATFORM init.platformData.ndt = glfwGetX11Display(); init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
#define SET_PLATFORM init.platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
#define SET_PLATFORM init.platformData.nwh = glfwGetWin32Window(window);
#endif