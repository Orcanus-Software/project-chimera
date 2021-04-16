#pragma once

#include "Audio.h"
#include "../debug/Log.h"

namespace VTT {
	class AudioManager {
	private:
		static bool INSTANCE;
		ALCdevice* device;
		ALCcontext* context;
	public:
		AudioManager();
		~AudioManager();

		static ALenum checkALError();
		static ALCenum checkALCError(ALCdevice* device);
	};
}