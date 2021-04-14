#include <iostream>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "render_target/Window.h"

#define LOG(x) std::cout << x << std::endl

const bgfx::ViewId kClearView = 0;

struct PosColorVertex
{
    float x;
    float y;
    float z;
    uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
    0, 1, 2,
    1, 3, 2,
    4, 6, 5,
    5, 6, 7,
    0, 2, 4,
    4, 2, 6,
    1, 5, 3,
    5, 7, 3,
    0, 4, 1,
    4, 5, 1,
    2, 3, 6,
    6, 3, 7,
};

static void glfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
	//	s_showStats = !s_showStats;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(window, true);
}

static void glfwFramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
}

int main(int argc, char** argv) {
	LOG("Hello BGFX!");

	// Initialize glfw error callback
	glfwSetErrorCallback(glfwErrorCallback);

	
	VTT::Window window = VTT::Window("BGFX Test Application", 1024, 768);

	glfwSetKeyCallback(window.getHandle(), glfwKeyCallback);
	glfwSetFramebufferSizeCallback(window.getHandle(), glfwFramebufferResizeCallback);

	// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
	// Most graphics APIs must be used on the same thread that created the window.
	bgfx::renderFrame();
	// Initialize bgfx using the native window handle and window resolution.
	bgfx::Init init;
	window.fillBGFXInit(init);

	// Try to initialize bgfx
	if (!bgfx::init(init)) {
		LOG("Could not initialize BGFX, aborting.");
		return 1;
	}

	// Set view 0 to the same dimensions as the window and to clear the color buffer.
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355F, 1.0f, 0);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

	// create a new cube
	bgfx::VertexDecl pcvDecl;
	pcvDecl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	.end();

	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices), pcvDecl));
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

	// while the window should stay open.
	while (!glfwWindowShouldClose(window.getHandle())) {
		glfwPollEvents();
		// This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
		bgfx::touch(kClearView);
		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		//bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(win_width / 2 / 8), 20) - 20, bx::max<uint16_t>(uint16_t(win_height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
		bgfx::dbgTextPrintf(0, 0, 0x0f, "Cube Demo");
		bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
		bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
		bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
		const bgfx::Stats* stats = bgfx::getStats();
		bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
		// Enable stats or debug text.
		bgfx::setDebug(false ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
		// Advance to next frame. Process submitted rendering primitives.
		bgfx::frame();
	}

	// Try to shutdown and terminate
	bgfx::shutdown();
	glfwTerminate();

	return 0;
}