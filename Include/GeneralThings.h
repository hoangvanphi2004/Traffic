#pragma once

#include<SDL.h>

#include "Materials.h"
#include "Button.h"

// This class create general things like button, music, etc.
class GeneralThings{
public:
    static GeneralThings* gameGeneralThings;
    Mix_Music* menuSoundTrack;
    Mix_Music* gameSoundTrack;
    Mix_Music* carAccident;
    Mix_Chunk* changeLight;

    Button* playButton;
    Button* helpButton;
    Button* quitButton;
    Button* mainMenuButton;
    Button* resumeButton;
    Button* playAgainButton;
    Button* backButton;
public:
    void loadGeneralThings();
};
