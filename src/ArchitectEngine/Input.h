#ifndef _INPUT_H
#define  _INPUT_H

#include <SDL2/SDL.h>
#include <vector>
#include "Component.h"

class Input : Component
{
public:
	bool isKey(int _key);
	bool isKeyPressed(int _key);
	bool isKeyReleased(int _key);

	bool handleInput(SDL_Event* _event);

private:
	std::vector<int> keys, pressedKeys, releasedKeys;
};

#endif
