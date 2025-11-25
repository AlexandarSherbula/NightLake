#pragma once

#include "Utils/Utilities.hpp"

#include "miniaudio.h"

#include <filesystem>

namespace aio
{
	struct AudioSource
	{
		uint32_t channels = 0;
		uint32_t sampleRate = 0;
		uint32_t currentFrame = 0;
		uint32_t totalFrames = 0;
		float endPoint = 0.0f;
		bool isLooping = false;
		float loopStartPoint = 0.0f;

		float volume = 1.0f;

		void* decoder = nullptr;
	};

	class Audio
	{
	public:
		static Ref<Audio> Create(const std::filesystem::path& filepath);
		~Audio();

		void Play();
		void Stop();

		void LoopInSeconds(float startPoint = 0.0f, float endPoint = 0.0f);
		void LoopInMiliseconds(float startPoint = 0.0f, float endPoint = 0.0f);

		void SetVolume(float volume);

		bool& IsLooping() { return mSource.isLooping; }

		virtual void SeekInSeconds(float timeInSeconds) = 0;
		virtual void SeekInMiliseconds(float timeInMiliseconds) = 0;
	private:
		virtual AudioSource CreateAudioSource() = 0;
	public:
		bool isPlaying = false;
	protected:
		ma_device mDevice;
		AudioSource mSource;
		std::filesystem::path mFilePath;
	};
}