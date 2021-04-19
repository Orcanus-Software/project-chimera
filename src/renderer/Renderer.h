#pragma once

#include "../debug/Log.h"

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

		void render();
	};
}