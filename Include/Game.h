#pragma once

#include<SDL.h>
#include<SDL_ttf.h>
#include<vector>
#include<iostream>

#include "PlayerCar.h"
#include "Materials.h"
#include "Car.h"
#include "EnemyCar.h"
#include "Map.h"
#include "Button.h"

class Game{
private:
    SDL_Window* window;

    SDL_Event event;
    bool quit = false;
    int increasingTime = 3;
    int previousVelocity = 0;
    int startVelocity = 2;

    bool goBackToMainMenu = false;

    PlayerCar* playerCar;
    SceneComponentAsset* sceneComponentAsset;
    Button* playButton;
    Button* helpButton;
    Button* quitButton;
    Button* mainMenuButton;
    Button* resumeButton;
    Button* playAgainButton;
    Button* backButton;
public:
    Game(const char *title, int screen_with, int screen_height);

    void menuScreen();

    void helpScreen();

    void runningScreen();

    void pauseScreen();

    void gameOverScreen();

    void close();
};
