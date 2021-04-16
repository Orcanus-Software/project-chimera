#include <vttpch.h>

#include "Source.h"

namespace VTT {
	Source::Source(float pitch, float gain, glm::vec3 pos, glm::vec3 vel, bool shouldLoop, Buffer& buffer)
	{
		alGenSources(1, &handle);
		setFloat(AL_PITCH, pitch);
		setFloat(AL_GAIN, gain);
		setVec3f(AL_POSITION, pos);
		setVec3f(AL_VELOCITY, vel);
		setInt(AL_LOOPING, shouldLoop ? AL_TRUE : AL_FALSE);
		setInt(AL_BUFFER, buffer.handle);
	}

	Source::~Source()
	{
		alDeleteSources(1, &handle);
	}
}