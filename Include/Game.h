#pragma once

#include<SDL.h>
#include<iostream>

#include "PlayerCar.h"
#include "SceneComponentAsset.h"
#include "GeneralThings.h"

class Game{
private:
    SDL_Window* window;

    SDL_Event event;
    bool quit = false;

    //This variable count number of round from the last round that car speed increase
    int increasingTime = 5;
    int previousVelocity = 0;
    int startVelocity = 2;

    int score = 0;
    int highScore = 0;

    // Candy status !!!!!!
    bool showDirectionStatus = false;
    bool beEnternalStatus = false;

    // Rainbow candy service
    bool invisible = false;
    int changeVisibilityTime = 200;
    Uint32 changeVisibilityPoint;
    int beEnternalTime = 8000;
    int beEnternalStartTime;
    int warning = 2000;

    bool goBackToMainMenu = false;

    PlayerCar* playerCar;
    SceneComponentAsset* sceneComponentAsset;

public:
    Game(const char *title, int screen_with, int screen_height);

    void menuScreen();

    void helpScreen();

    void runningScreen();

    void pauseScreen();

    void gameOverScreen();

    void close();
};
