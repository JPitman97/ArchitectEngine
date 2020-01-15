#include "Input.h"
#include <iostream>

bool Input::isKey(int _key)
{
	for (auto& k : keys)
		if (k == _key)
			return true;

	return false;
}

bool Input::isKeyPressed(int _key)
{
	for (auto& k : pressedKeys)
		if (k == _key)
			return true;

	return false;
}

bool Input::isKeyReleased(int _key)
{
	for (auto& k : releasedKeys)
		if (k == _key)
			return true;

	return false;
}

bool Input::handleInput(SDL_Event* _event)
{
	pressedKeys.clear();
	releasedKeys.clear();

	while (SDL_PollEvent(_event))
	{
		switch (_event->type)
		{
		case SDL_KEYDOWN:
			{
				std::cout << "Key pressed: " << static_cast<char>(_event->key.keysym.sym) << std::endl;
				pressedKeys.push_back(_event->key.keysym.sym);
				if (std::find(keys.begin(), keys.end(), _event->key.keysym.sym) != keys.end()) {
					//Do nothing
					std::cout << "Ignoring key: " << static_cast<char>(_event->key.keysym.sym) << std::endl;
				}
				else
					keys.push_back(_event->key.keysym.sym);

				break;
			}
		case SDL_KEYUP:
			{
				std::cout << "Key released: " << static_cast<char>(_event->key.keysym.sym) << std::endl;
				releasedKeys.push_back(_event->key.keysym.sym);
				for (int i = 0; i < keys.size(); i++)
				{
					if (keys.at(i) == _event->key.keysym.sym)
						keys.erase(keys.begin() + i);
				}
				break;
			}
		case SDL_QUIT:
			{
				return false;  
				break;
			}
		default: ;
		}
	}
	return true;
}
