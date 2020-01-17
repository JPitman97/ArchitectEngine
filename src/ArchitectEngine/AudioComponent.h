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

class AudioComponent : public Component
{
public:
	AudioComponent();
	~AudioComponent();

	void onTick() override;

	void playAudio(const std::string& _filename);

private:
	void load_ogg(const std::string& fileName, std::vector<char>& buffer, ALenum &format, ALsizei &freq);

	ALCdevice* device;
	ALCcontext* context{};
	ALuint bufferId = 0;
	ALuint sourceId = 0;

	bool canPlay = true;
};

#endif
