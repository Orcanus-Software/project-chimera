#include <vttpch.h>

#include "Renderer.h"

namespace Chimera {

Renderer::Renderer(RENDERER_API::Init init)
{
	// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
	// Most graphics APIs must be used on the same thread that created the window.
	RENDERER_API::renderFrame();

	// Try to initialize bgfx
	Logger::getLogger()->trace("Attempting BGFX Initialize");
	if (!RENDERER_API::init(init)) {
		Logger::getLogger()->error("Could not initialize BGFX, aborting.");
		throw 1;
	}

	// Set view 0 to the same dimensions as the window and to clear the color buffer.
	bgfx::setViewClear(VIEW_ID, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355F, 1.0f, 0);
	bgfx::setViewRect(VIEW_ID, 0, 0, bgfx::BackbufferRatio::Equal);
}

void Renderer::cleanUp()
{
	RENDERER_API::shutdown();
}

Renderer::~Renderer()
{
	
}

void Renderer::beginFrame()
{
	RENDERER_API::touch(VIEW_ID);
}

void Renderer::render(Model& model)
{
	model.bind();
}

void Renderer::endFrame()
{
	RENDERER_API::setDebug(BGFX_DEBUG_TEXT);

	RENDERER_API::frame();
}

}