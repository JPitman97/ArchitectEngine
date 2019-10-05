#ifndef _DUMMY_H
#define _DUMMY_H

#include <iostream>
#include <SDL2/SDL.h>

class dummy
{
public:
	dummy();
	~dummy();
	void openWindow();

private:
	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
};

#endif
