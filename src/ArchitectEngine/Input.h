#ifndef _INPUT_H
#define  _INPUT_H

#include <SDL2/SDL.h>
#include <vector>
#include "Component.h"

///This class handles inputs.
///
///This class handles whether keys are pressed, released or held, and is used within InputComponent.
class Input : Component
{
public:
	///This method checks if a key is held.
	///
	///This method checks to see if a key has been held for more than one tick.
	///@param _key This is the key to check for.
	bool isKey(int _key);
	///This method checks if a key is pressed.
	///
	///This method checks to see if a key has been pressed.
	///@param _key This is the key to check for.
	bool isKeyPressed(int _key);
	///This method checks if a key is released.
	///
	///This method checks to see if a key has been released for more than one tick.
	///@param _key This is the key to check for.
	bool isKeyReleased(int _key);

	///This method checks for input from SDL and stores the key's.
	///
	///This method checks for SDL events and stores the key's if they are pressed.
	///@param _event This is the event to check for.
	bool handleInput(SDL_Event* _event);

private:
	std::vector<int> keys, pressedKeys, releasedKeys;
};

#endif
