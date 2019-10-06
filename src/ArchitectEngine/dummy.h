#ifndef _DUMMY_H
#define _DUMMY_H

#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

class dummy {
public:
    dummy();

    ~dummy();

    void openWindow();

private:
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
};

#endif
