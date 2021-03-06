#include <vttpch.h>

#include "Source.h"

namespace Chimera {
	Source::Source(float pitch, float gain, glm::vec3 pos, glm::vec3 vel, bool shouldLoop)
	{
		alGenSources(1, &handle);
		Logger::getLogger()->debug("Source created.");

		setFloat(AL_PITCH, pitch);
		Logger::getLogger()->debug("Pitch set.");
		AudioManager::checkALError();

		setFloat(AL_GAIN, gain);
		Logger::getLogger()->debug("Gain set.");
		AudioManager::checkALError();

		setVec3f(AL_POSITION, pos);
		Logger::getLogger()->debug("Position set.");
		AudioManager::checkALError();

		setVec3f(AL_VELOCITY, vel);
		Logger::getLogger()->debug("Velocity set.");
		AudioManager::checkALError();

		setInt(AL_LOOPING, shouldLoop ? AL_TRUE : AL_FALSE);
		Logger::getLogger()->debug("Looping set.");
		AudioManager::checkALError();

		// setInt(AL_BUFFER, buffer.handle);
		// Logger::getLogger()->debug("Buffer set.");
		// AudioManager::checkALError();
	}

	void Source::CleanUp()
	{
		if(alIsSource(handle))
			alDeleteSources(1, &handle);
	}

	Source::~Source()
	{
	}

	void Source::queue(Buffer& buffer) 
	{ 
		alSourceQueueBuffers(handle, 1, &buffer.handle); 
	};
	
	void Source::unqueue(Buffer& buffer) 
	{ 
		alSourceUnqueueBuffers(handle, 1, &buffer.handle); 
	};

	void Source::setBuffer(Buffer& buffer)
	{
		setInt(AL_BUFFER, buffer.handle);
	}
}