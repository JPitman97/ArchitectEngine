#include "AudioComponent.h"
#include "stb_vorbis/stb_vorbis.h"
#include <iostream>

AudioComponent::AudioComponent()
{
	/*
   * Initialize OpenAL audio system
   */

   //Open up the OpenAL device
	device = alcOpenDevice(NULL);

	/*if (device == nullptr)
	{
		throw std::exception();
	}*/

	// Create audio context
	context = alcCreateContext(device, NULL);

	if (context == NULL)
	{
		alcCloseDevice(device);
		throw std::exception();
	}

	// Set as current context
	if (!alcMakeContextCurrent(context))
	{
		alcDestroyContext(context);
		alcCloseDevice(device);
		throw std::exception();
	}

	// Generally not needed. Translate sources instead
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);

	/*
	 * Create OpenAL sound buffer
	 */
	ALuint bufferId = 0;
	alGenBuffers(1, &bufferId);
}

AudioComponent::~AudioComponent()
{
	/*
 * Clean up OpenAL data.
 *
 * Note: Do not free the buffer before the source using it has been freed.
 *       Use a std::shared_ptr to hold onto you sound buffer class from source class.
 *
 * Note: Make sure current context has been set to NULL before deleting context.
 *       Make sure context destroyed before closing device.
 */
	if (stop == false)
	{
		alDeleteSources(1, &sourceId);
		alDeleteBuffers(1, &bufferId);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
		stop = true;
	}
}

void AudioComponent::onTick()
{
	/*
	 * Wait for sound to finish
	 *
	 * Note: You will generally want to check within your onTick functions
	 *       and get the SoundSource component to remove itself when complete.
	 */
	ALint state = 0;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

	if (state == AL_STOPPED)
		canPlay = true;
	/*else
		canPlay = true;*/
}

void AudioComponent::playAudio(const std::string& _filename)
{
	try
	{
		if (canPlay)
		{
			canPlay = false;
			/*
			* Create OpenAL sound buffer
			*/
			bufferId = 0;
			alGenBuffers(1, &bufferId);

			ALenum format = 0;
			ALsizei freq = 0;
			std::vector<char> bufferData;
			load_ogg(_filename, bufferData, format, freq);

			if (!bufferData.empty())
			{
				alBufferData(bufferId, format, &bufferData.at(0),
					static_cast<ALsizei>(bufferData.size()), freq);
			}
			else { throw std::exception("Failed to play audio, is the file path correct?"); }

			/*
			 * Create OpenAL sound source
			 */
			sourceId = 0;
			alGenSources(1, &sourceId);

			alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
			alSourcei(sourceId, AL_BUFFER, bufferId);
			alSourcePlay(sourceId);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void AudioComponent::load_ogg(const std::string& fileName, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
{
	try
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename(
			fileName.c_str(), &channels, &sampleRate, &output);

		if (samples == -1)
		{
			throw std::exception("Samples failed to initialise, are you sure the audio file path is correct?");
		}

		// Record the sample rate required by OpenAL
		freq = sampleRate;

		// Record the format required by OpenAL
		if (channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;

			// Force format to be mono (Useful for positional audio)
			// format = AL_FORMAT_MONO16;
			// freq *= 2;
		}

		// Allocate enough space based on short (two chars) multipled by the number of
		// channels and length of clip
		buffer.resize(sizeof(*output) * channels * samples);
		memcpy(&buffer.at(0), output, buffer.size());

		// Clean up the read data
		free(output);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}