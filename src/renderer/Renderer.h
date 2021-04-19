#pragma once

#include "../debug/Log.h"
#include "Model.h"

#ifndef VIEW_ID
#define VIEW_ID 0
#endif

#define RENDERER_API bgfx

namespace Chimera {
	class Renderer {
	public:
		Renderer() = delete;
		Renderer(RENDERER_API::Init init);
		void cleanUp();
		~Renderer();

		void beginFrame();
		void render(Model& model);
		void endFrame();
	};
}