#pragma once

namespace Chimera {
	class Application {
	public:
		Application();

		// Physics update, Ai, etc
		void onUpdate(long ms);

		void onRender();

		void showImGUI();

		~Application();
	};
}