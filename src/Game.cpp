#include "../Include/Game.h"

void Game::runningScreen(){
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            playerCar->movement(event);
        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        materials->clean();
        playerCar->checkBackground();
        sceneComponentAsset->render();
        playerCar->render();
        materials->print();
        if(playerCar->checkAnyAccident()){
            close();
        }
    }
    close();
}

Game::Game(const char *title, int screen_width, int screen_height){
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Go Home", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    materials->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    materials->loadMaterials();
    sceneComponentAsset = new SceneComponentAsset(materials);
    playerCar = new PlayerCar(materials, sceneComponentAsset);
}

void Game::close(){
    materials->destroy();

    SDL_DestroyWindow(window);

    SDL_Quit();
}


