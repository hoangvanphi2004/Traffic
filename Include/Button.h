#pragma once
#include<SDL.h>

#include "Materials.h"

class Button{
public:
    bool isClicked = false;

private:
    int x, y, w, h;
    int buttonType = 1;
    std::string buttonName;
    bool status = false;
public:
    Button(std::string buttonName, int x, int y, int buttonType);

    bool handleEvent(SDL_Event* event);

    void render();
};
