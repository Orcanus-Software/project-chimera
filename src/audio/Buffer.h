#pragma once

#include <vttpch.h>
#include "Audio.h"

namespace VTT {
	class Buffer {
	private:
		ALuint handle;

		friend class Source;
		friend class AudioManager;
	public:
		Buffer(std::uint8_t channels, std::int32_t sampleRate, std::uint8_t bitsPerSample, short* data, int data_size);
		~Buffer();

		int setData(std::uint8_t channels, std::int32_t sampleRate, std::uint8_t bitsPerSample, short* data, int data_size);
	};
}