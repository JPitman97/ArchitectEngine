#include "dummy.h"

dummy::dummy()
{
}

dummy::~dummy()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void dummy::openWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error("Failed to initialize SDL2");
	}

	window = SDL_CreateWindow("SDL2 Minimal Example",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		throw std::runtime_error("Failed to create SDL2 window");
	}

	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	SDL_UpdateWindowSurface(window);
}
