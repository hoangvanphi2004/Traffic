#include "../Include/GeneralThings.h"

GeneralThings* GeneralThings::gameGeneralThings = new GeneralThings();

void GeneralThings::loadGeneralThings(){
    menuSoundTrack = Mix_LoadMUS("../Traffic/Assets/MenuSoundTrack.mp3");
    gameSoundTrack = Mix_LoadMUS("../Traffic/Assets/GameSoundTrack.mp3");
    carAccident = Mix_LoadMUS("../Traffic/Assets/CarAccident.mp3");
    changeLight = Mix_LoadWAV("../Traffic/Assets/ChangeLight.mp3");

    playButton = new Button(
        "play",
        (SCREEN_WIDTH - Materials::gameMaterials->materials["buttonIn1"].w) / 2,
        240,
        1
    );
    helpButton = new Button(
        "help",
        (SCREEN_WIDTH - Materials::gameMaterials->materials["buttonIn1"].w) / 2,
        400,
        1
    );
    quitButton = new Button(
        "quit",
        (SCREEN_WIDTH - Materials::gameMaterials->materials["buttonIn1"].w) / 2,
        560,
        1
    );
    resumeButton = new Button(
        "resume",
        (SCREEN_WIDTH - Materials::gameMaterials->materials["buttonIn2"].w) / 2,
        (SCREEN_HEIGHT - Materials::gameMaterials->materials["buttonIn2"].h) / 2 + 100,
        2
    );
    playAgainButton = new Button(
        "playAgain",
        40,
        SCREEN_HEIGHT - Materials::gameMaterials->materials["buttonIn2"].h - 40,
        2
    );
    mainMenuButton = new Button(
        "mainMenu",
        SCREEN_WIDTH - Materials::gameMaterials->materials["buttonIn2"].w - 40,
        SCREEN_HEIGHT - Materials::gameMaterials->materials["buttonIn2"].h - 40,
        2
    );
    backButton = new Button(
        "back",
        SCREEN_WIDTH - Materials::gameMaterials->materials["buttonIn2"].w - 40,
        SCREEN_HEIGHT - Materials::gameMaterials->materials["buttonIn2"].h - 40,
        2
    );
}
