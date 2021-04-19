#pragma once
#include <vttpch.h>

#include "Buffer.h"

namespace Chimera {
	class Buffer;

	class Source {
		ALuint handle;
		Source(float pitch, float gain, glm::vec3 pos, glm::vec3 vel, bool shouldLoop);

		friend class AudioManager;
	public:
		void CleanUp();
		~Source();

		void play() { alSourcePlay(handle); };
		void pause() { alSourcePause(handle); };
		void stop() { alSourceStop(handle); };
		void rewind() { alSourceRewind(handle); };
		void queue(Buffer& buffer);
		void unqueue(Buffer& buffer);
		void setBuffer(Buffer& buffer);

		bool isPlaying() { return queryInt(AL_SOURCE_STATE) == AL_PLAYING; };

		ALint queryInt(ALenum param) { ALint value = 0; alGetSourcei(handle, param, &value); return value; };
		ALfloat queryFloat(ALenum param) { ALfloat value = 0; alGetSourcef(handle, param, &value); return value; };
		glm::ivec3 queryVec3i(ALenum param) { int x, y, z; alGetSource3i(handle, param, &x, &y, &z); return glm::ivec3{ x, y, z }; };
		glm::vec3 queryVec3f(ALenum param) { float x, y, z; alGetSource3f(handle, param, &x, &y, &z); return glm::vec3{ x, y, z }; };

		void setFloat(ALenum param, float data) { alSourcef(handle, param, data); };
		void setInt(ALenum param, int data) { alSourcei(handle, param, data); };
		void setVec3f(ALenum param, glm::vec3 data) { alSource3f(handle, param, data.x, data.y, data.z); };
		void setVec3i(ALenum param, glm::ivec3 data) { alSource3i(handle, param, data.x, data.y, data.z); };
	};
}