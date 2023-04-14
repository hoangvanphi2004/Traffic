#include "../Include/Game.h"

Game::Game(const char *title, int screen_width, int screen_height){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Traffic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    Materials::gameMaterials->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Materials::gameMaterials->loadMaterials();
    sceneComponentAsset = new SceneComponentAsset();
    playerCar = new PlayerCar(sceneComponentAsset);
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

void Game::menuScreen(){
    Car::velocity = startVelocity;
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            playButton->handleEvent(&event);
            helpButton->handleEvent(&event);
            quitButton->handleEvent(&event);
        }
        goBackToMainMenu = false;
        playerCar->x = SCREEN_WIDTH / 2;
        playerCar->y = SCREEN_HEIGHT / 2;
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();

        sceneComponentAsset->render();
        Materials::gameMaterials->render(
            "gameName",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["gameName"].w) / 2,
            50, SDL_FLIP_NONE);
        playButton->render();
        helpButton->render();
        quitButton->render();

        if(playButton->isClicked == true){
            sceneComponentAsset = new SceneComponentAsset();
            playerCar = new PlayerCar(sceneComponentAsset);
            runningScreen();
            sceneComponentAsset = new SceneComponentAsset();
            playerCar = new PlayerCar(sceneComponentAsset);
            playButton->isClicked = false;
        }
        if(helpButton->isClicked == true){
            helpScreen();
            helpButton->isClicked = false;
        }
        if(quitButton->isClicked == true){
            close();
            quitButton->isClicked = false;
        }
        Materials::gameMaterials->print();
    }
    close();
}

void Game::helpScreen(){
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            backButton->handleEvent(&event);
        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();

        sceneComponentAsset->render();
        Materials::gameMaterials->render(
            "helpBoard",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["helpBoard"].w) / 2,
            40,
            SDL_FLIP_NONE
        );
        backButton->render();

        if(backButton->isClicked == true){
            backButton->isClicked = false;
            break;
        }
        Materials::gameMaterials->print();
    }
}

void Game::runningScreen(){
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            if(event.key.keysym.sym == SDLK_ESCAPE){
                pauseScreen();
            }
            playerCar->movement(event);

        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();
        if(!playerCar->checkBackground()) {
            increasingTime -= 1;
            Map::spawnTime -= 1;
            if(increasingTime == 0){
                increasingTime = 3;
                Car::velocity += 1;
            }
        }

        sceneComponentAsset->render();
        playerCar->render();

        Materials::gameMaterials->print();
        if(playerCar->checkAnyAccident()){
            gameOverScreen();
            if(goBackToMainMenu == true){
                break;
            }
        }
    }
}

void Game::pauseScreen(){
    previousVelocity = Car::velocity;
    Car::velocity = 0;
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            resumeButton->handleEvent(&event);
        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();

        sceneComponentAsset->render();
        playerCar->render();
        resumeButton->render();

        if(resumeButton->isClicked == true){
            Car::velocity = previousVelocity;
            resumeButton->isClicked = false;
            break;
        }
        Materials::gameMaterials->print();
    }
}

void Game::gameOverScreen(){
    Car::velocity = 0;
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            playAgainButton->handleEvent(&event);
            mainMenuButton->handleEvent(&event);
        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();

        sceneComponentAsset->render();
        Materials::gameMaterials->render(
            "pauseBoard",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["pauseBoard"].w) / 2,
            80,
            SDL_FLIP_NONE
        );
        playAgainButton->render();
        mainMenuButton->render();

        if(playAgainButton->isClicked == true){
            sceneComponentAsset = new SceneComponentAsset();
            playerCar = new PlayerCar(sceneComponentAsset);
            playAgainButton->isClicked = false;
            Car::velocity = startVelocity;
            break;
        }
        if(mainMenuButton->isClicked == true){
            goBackToMainMenu = true;
            mainMenuButton->isClicked = false;
            Car::velocity = startVelocity;
            break;
        }
        Materials::gameMaterials->print();
    }
}

void Game::close(){
    Materials::gameMaterials->destroy();

    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}


