#ifndef _AUDIOCOMPONENT_H
#define _AUDIOCOMPONENT_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <AL/al.h>
#include <AL/alc.h>
#include "Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>

///This class handles audio loading and playing.
///
///This class allows users to play their own sounds on entities
class AudioComponent : public Component
{
public:
	///This constructor creates the audio device and context.
	///
	///This constructor creates all the objects needed as well as specifying a default sound location.
	AudioComponent();
	///This destructor destroys the device and context to avoid memory leaks.
	///
	///This destructor cleans up the audio component when it's destroyed.
	~AudioComponent();

	///This method checks to see whether a sound is playing, if so it blocks others.
	///
	///This method avoids multiple audio clips playing at the same time from one source.
	void onTick() override;

	///This method plays an audio clip from the file name.
	///
	///This method takes a file name and plays the audio clip.
	///@param _filename This is the name of the audioclip
	void playAudio(const std::string& _filename);

private:
	///This method loads the ogg file and sets data relating to it.
	///
	///This method loads and stores the sound information from the ogg file.
	///@param fileName This is the filename of the audio clip
	///@param buffer This is the audio buffer for the audio clip
	///@param format This is the format of the audio clip
	///@param freq This is the frequency of the audio clip
	void load_ogg(const std::string& fileName, std::vector<char>& buffer, ALenum &format, ALsizei &freq);

	ALCdevice* device;
	ALCcontext* context{};
	ALuint bufferId = 0;
	ALuint sourceId = 0;

	bool canPlay = true;
};

#endif