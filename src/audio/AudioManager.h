#pragma once

#include "Audio.h"
#include "../debug/Log.h"

namespace VTT {
	class Buffer;
	class Source;

	class AudioManager {
	private:
		static bool INSTANCE;
		ALCdevice* device;
		ALCcontext* context;

		std::vector<std::shared_ptr<Buffer>> buffers;
		std::vector<std::shared_ptr<Source>> sources;
	public:
		AudioManager();
		~AudioManager();

		std::shared_ptr<Buffer> loadVorbisFile(const char* filename);
		std::shared_ptr<Source> createSource(std::shared_ptr<Buffer> buffer);

		static ALenum checkALError();
		static ALCenum checkALCError(ALCdevice* device);
	};
}