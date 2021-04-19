#pragma once

#include "Audio.h"
#include "../debug/Log.h"

namespace Chimera {
	class Buffer;
	class Source;

	class AudioManager {
	private:
		static bool INSTANCE;
		ALCdevice* device;
		ALCcontext* context;

		std::vector<Buffer> buffers;
		std::vector<Source> sources;
	public:
		AudioManager();
		~AudioManager();

		Buffer loadVorbisFile(const char* filename);
		Source createSource();

		void setListenerPosition(glm::vec3 position) { alListener3f(AL_POSITION, position.x, position.y, position.z);  };
		void setListenerVelocity(glm::vec3 velocity) { alListener3f(AL_POSITION, velocity.x, velocity.y, velocity.z); };
		void setOrientation(glm::vec2 orientation) { ALfloat values[2] = { orientation.x, orientation.y }; alListenerfv(AL_ORIENTATION, values); };

		glm::vec3 getListenerPosition() { ALfloat x, y, z = 0;  alGetListener3f(AL_POSITION, &x, &y, &z); return glm::vec3{ x, y, z }; };
		glm::vec3 getListenerVelocity() { ALfloat x, y, z = 0;  alGetListener3f(AL_VELOCITY, &x, &y, &z); return glm::vec3{ x, y, z }; };
		glm::vec2 getOrientation() { ALfloat values[2] = { 0 }; alGetListenerfv(AL_ORIENTATION, values); return glm::vec2{ values[0], values[1] }; };

		static ALenum checkALError();
		static ALCenum checkALCError(ALCdevice* device);
	};
}