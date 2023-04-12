#pragma once

#include<SDL.h>
#include<vector>
#include<iostream>

#include "PlayerCar.h"
#include "Materials.h"
#include "Car.h"
#include "EnemyCar.h"
#include "Map.h"

class Game{
private:
    SDL_Window* window;

    SDL_Event event;
    bool quit = false;

    PlayerCar* playerCar;
    SceneComponentAsset* sceneComponentAsset;
public:
    Game(const char *title, int screen_with, int screen_height);

    void menuScreen();

    void runningScreen();

    void close();
};
