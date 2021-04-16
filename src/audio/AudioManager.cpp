#include "vttpch.h"

#include "AudioManager.h"

namespace VTT {

	bool AudioManager::INSTANCE = false;

	AudioManager::AudioManager()
	{
		if (INSTANCE) {
			Logger::getLogger()->warn("AudioManager already created.");
			throw 1;
		}

		INSTANCE = true;
		
		// try to open a device
		Logger::getLogger()->debug("Opening ALCdevice");
		device = alcOpenDevice(nullptr);

		if (!device) {
			Logger::getLogger()->error("Failed to open alc device.");
			INSTANCE = false;
			throw 1;
		}

		// try to create a context
		Logger::getLogger()->debug("Opening ALCcontext");
		context = alcCreateContext(device, nullptr);
		if (!context) {
			Logger::getLogger()->error("Failed to create alc context.");
			AudioManager::checkALCError(device);
			throw 1;
		}

		// try to make the context current
		ALCboolean isContextCurrent;
		isContextCurrent = alcMakeContextCurrent(context);

		if (isContextCurrent != AL_TRUE) {
			Logger::getLogger()->error("Unable to make alc context current.");
			AudioManager::checkALCError(device);
			throw 1;
		}
	}
	
	AudioManager::~AudioManager()
	{
		Logger::getLogger()->debug("Shutting down AudioManager");

		alcMakeContextCurrent(context);

		alcDestroyContext(context);

		alcCloseDevice(device);
		INSTANCE = false;
	}

	ALenum AudioManager::checkALError()
	{
		ALenum error_code = alGetError();

		if (error_code != AL_NO_ERROR)
		{
			Logger::getLogger()->warn("AL error detected:");
			switch (error_code)
			{
			case AL_INVALID_NAME:
				Logger::getLogger()->error("AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function");
				break;
			case AL_INVALID_ENUM:
				Logger::getLogger()->error("AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function");
				break;
			case AL_INVALID_VALUE:
				Logger::getLogger()->error("AL_INVALID_VALUE: an invalid value was passed to an OpenAL function");
				break;
			case AL_INVALID_OPERATION:
				Logger::getLogger()->error("AL_INVALID_OPERATION: the requested operation is not valid");
				break;
			case AL_OUT_OF_MEMORY:
				Logger::getLogger()->error("AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
				break;
			default:
				Logger::getLogger()->error("UNKNOWN AL ERROR: {}", error_code);
			}
		}

		return error_code;
	}
	ALCenum AudioManager::checkALCError(ALCdevice * device)
	{
		ALCenum error_code = alcGetError(device);
		if (error_code != ALC_NO_ERROR)
		{
			Logger::getLogger()->warn("AL error detected:");
			switch (error_code)
			{
			case ALC_INVALID_VALUE:
				Logger::getLogger()->error("ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function");
				break;
			case ALC_INVALID_DEVICE:
				Logger::getLogger()->error("ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function");
				break;
			case ALC_INVALID_CONTEXT:
				Logger::getLogger()->error("ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function");
				break;
			case ALC_INVALID_ENUM:
				Logger::getLogger()->error("ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function");
				break;
			case ALC_OUT_OF_MEMORY:
				Logger::getLogger()->error("ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function");
				break;
			default:
				Logger::getLogger()->error("UNKNOWN ALC ERROR: {}", error_code);
			}
		}
		return error_code;
	}
}