#pragma once
#include <vttpch.h>

#include "Audio.h"

namespace VTT {
	class Buffer;

	class Source {
		ALuint handle;
	public:
		Source(float pitch, float gain, glm::vec3 pos, glm::vec3 vel, bool shouldLoop, Buffer& buffer);
		~Source();

		void play() { alSourcePlay(handle); };
		void pause() { alSourcePause(handle); };
		void stop() { alSourceStop(handle); };

		bool isPlaying() { return queryInt(AL_SOURCE_STATE) == AL_PLAYING; };

		ALint queryInt(ALenum param) { int value = 0; alGetSourcei(handle, param, &value); return value; };

		void setFloat(ALenum param, float data) { alSourcef(handle, param, data); };
		void setInt(ALenum param, int data) { alSourcei(handle, param, data); };
		void setVec3f(ALenum param, glm::vec3 data) { alSource3f(handle, param, data.x, data.y, data.z); };
	};
}