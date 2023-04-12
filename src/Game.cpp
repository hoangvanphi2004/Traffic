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
        Materials::gameMaterials->clean();
        if(!playerCar->checkBackground()) Car::velocity += 2;
        sceneComponentAsset->render();
        playerCar->render();
        Materials::gameMaterials->print();
        /*if(playerCar->checkAnyAccident()){
            close();
        }*/
    }
    close();
}

Game::Game(const char *title, int screen_width, int screen_height){
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Traffic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    Materials::gameMaterials->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Materials::gameMaterials->loadMaterials();
    sceneComponentAsset = new SceneComponentAsset();
    playerCar = new PlayerCar(sceneComponentAsset);
}

void Game::close(){
    Materials::gameMaterials->destroy();

    SDL_DestroyWindow(window);

    SDL_Quit();
}


