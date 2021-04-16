#include <vttpch.h>

#include "Buffer.h"

namespace VTT {
	Buffer::Buffer(std::uint8_t channels, std::int32_t sampleRate, std::uint8_t bitsPerSample, char* data, ALsizei data_size)
	{
		alGenBuffers(1, &handle);
		
		Logger::getLogger()->debug("Created buffer");
		AudioManager::checkALError();

		if (setData(channels, sampleRate, bitsPerSample, data, data_size)) {
			throw 1;
		}
	}

	void Buffer::CleanUp()
	{
		Logger::getLogger()->trace("Deleting Buffer: {}", handle);
		if(alIsBuffer(handle))
			alDeleteBuffers(1, &handle);
	}

	Buffer::~Buffer()
	{
	}
	
	int Buffer::setData(std::uint8_t channels, std::int32_t sampleRate, std::uint8_t bitsPerSample, char* data, ALsizei data_size)
	{
		int error_code = 0;

		ALenum format;
		if (channels == 1 && bitsPerSample == 8) {
			format = AL_FORMAT_MONO8;
			Logger::getLogger()->debug("Mono8 format detected.");
		} else if (channels == 1 && bitsPerSample == 16) {
			format = AL_FORMAT_MONO16;
			Logger::getLogger()->debug("Mono16 format detected.");
		} else if (channels == 2 && bitsPerSample == 8) {
			format = AL_FORMAT_STEREO8;
			Logger::getLogger()->debug("Stereo8 format detected.");
		} else if (channels == 2 && bitsPerSample == 16) {
			format = AL_FORMAT_STEREO16;
			Logger::getLogger()->debug("Stereo16 format detected.");
		}	
		else {
			Logger::getLogger()->error("Unrecognized wav file format. Channels: {} BPS: {}", channels, bitsPerSample);
			error_code = 1;
			return error_code;
		}

		alBufferData(handle, format, data, data_size, sampleRate);

		Logger::getLogger()->debug("Filled Buffer Data");
		AudioManager::checkALError();

		return error_code;
	}
}