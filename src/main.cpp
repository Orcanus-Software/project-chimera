#include "vttpch.h"

#include "render_target/Window.h"
#include "debug/Log.h"
#include "audio/Audio.h"

using namespace VTT;

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

bgfx::ShaderHandle loadShader(const char * filename) 
{
	MICROPROFILE_SCOPEI("shader", "loadshader", MP_YELLOW);
	const char* shaderPath = "";

	switch (bgfx::getRendererType()) {
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D9:  shaderPath = "shaders/dx9/";   break;
	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
	case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
	case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
	case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
	case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;
	}

	size_t shaderLen = strlen(shaderPath);
	size_t fileLen = strlen(filename);
	char* filePath = (char*)malloc(shaderLen + fileLen+1);
	memcpy(filePath, shaderPath, shaderLen);
	memcpy(&filePath[shaderLen], filename, fileLen);
	filePath[shaderLen + fileLen] = '\0';

	Logger::getLogger()->info("Opening shader file: {}", filePath);

	FILE* file = fopen(filePath, "rb");
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
	fread(mem->data, 1, fileSize, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	return bgfx::createShader(mem);
}

int main(int argc, char** argv) {
	MicroProfileOnThreadCreate("Main");
	MicroProfileSetEnableAllGroups(true);
	MicroProfileSetForceMetaCounters(true);

	Logger::Init();

	Logger::getLogger()->info("Initializing GLFW.");

	// Initialize glfw error callback
	glfwSetErrorCallback(glfwErrorCallback);

	
	VTT::Window window = VTT::Window("BGFX Test Application", 1024, 768);

	glfwSetKeyCallback(window.getHandle(), glfwKeyCallback);
	glfwSetFramebufferSizeCallback(window.getHandle(), glfwFramebufferResizeCallback);

	Logger::getLogger()->info("Initializing BGFX");
	// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
	// Most graphics APIs must be used on the same thread that created the window.
	bgfx::renderFrame();

	Logger::getLogger()->trace("Filling init struct");
	// Initialize bgfx using the native window handle and window resolution.
	bgfx::Init init;
	window.fillBGFXInit(init);

	// Try to initialize bgfx
	Logger::getLogger()->trace("Attempting BGFX Initialize");
	if (!bgfx::init(init)) {
		Logger::getLogger()->error("Could not initialize BGFX, aborting.");
		return 1;
	}

	Logger::getLogger()->trace("Setting up the view.");
	// Set view 0 to the same dimensions as the window and to clear the color buffer.
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355F, 1.0f, 0);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

	Logger::getLogger()->trace("Setting up the cube vertices.");
	// create a new cube
	bgfx::VertexLayout pcvDecl;
	pcvDecl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	.end();

	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), pcvDecl);
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

	Logger::getLogger()->trace("Loading shaders.");
	bgfx::ShaderHandle vsh = loadShader("vs_cubes.bin");
	bgfx::ShaderHandle fsh = loadShader("fs_cubes.bin");
	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);

	AudioManager audioManager;
	Buffer sound1 = audioManager.loadVorbisFile("resources/audio/test1.ogg");
	Buffer sound2 = audioManager.loadVorbisFile("resources/audio/bounce.ogg");
	Buffer sound3 = audioManager.loadVorbisFile("resources/audio/music1.ogg");
	Source source = audioManager.createSource(sound1);
	source.play();

	window.setVisible(true);

	// while the window should stay open.
	unsigned long counter = 0;
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

		// cube rendering
		const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
		float view[16];
		bx::mtxLookAt(view, eye, at);

		float proj[16];
		bx::mtxProj(proj, 60.0f, float(window.getSize().x) / float(window.getSize().y), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(0, view, proj);

		float mtx[16];
		bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
		bgfx::setTransform(mtx);

		bgfx::setVertexBuffer(0, vbh);
		bgfx::setIndexBuffer(ibh);

		bgfx::submit(0, program);

		// Advance to next frame. Process submitted rendering primitives.
		bgfx::frame();
		counter++;
		MicroProfileFlip(nullptr);
	}

	Logger::getLogger()->debug("Shutting Down!");
	// Try to shutdown and terminate
	bgfx::destroy(vsh);
	bgfx::destroy(fsh);
	bgfx::destroy(program);
	bgfx::destroy(vbh);
	bgfx::destroy(ibh);
	bgfx::shutdown();
	window.CleanUp();
	glfwTerminate();

	// Stop profiling last
	MicroProfileShutdown();

	return 0;
}