#include "../Include/Game.h"

Game::Game(const char *title, int screen_width, int screen_height){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Traffic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    Materials::gameMaterials->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

    Materials::gameMaterials->loadMaterials();
    GeneralThings::gameGeneralThings->loadGeneralThings();
    sceneComponentAsset = new SceneComponentAsset();
    playerCar = new PlayerCar(sceneComponentAsset);
}

void Game::menuScreen(){
    Map::renderHoles = false;
    freopen("highScore.txt", "r", stdin);
    std::cin >> highScore;
    Car::velocity = startVelocity;
    Mix_PlayMusic(GeneralThings::gameGeneralThings->menuSoundTrack, -1);
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            GeneralThings::gameGeneralThings->playButton->handleEvent(&event);
            GeneralThings::gameGeneralThings->helpButton->handleEvent(&event);
            GeneralThings::gameGeneralThings->quitButton->handleEvent(&event);
        }
        goBackToMainMenu = false;
        playerCar->x = SCREEN_WIDTH / 2;
        playerCar->y = SCREEN_HEIGHT / 2;
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();

        // Render Part
        sceneComponentAsset->render();
        Materials::gameMaterials->render(
            "gameName",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["gameName"].w) / 2,
            50, SDL_FLIP_NONE);
        GeneralThings::gameGeneralThings->playButton->render();
        GeneralThings::gameGeneralThings->helpButton->render();
        GeneralThings::gameGeneralThings->quitButton->render();

        // Interaction
        if(GeneralThings::gameGeneralThings->playButton->isClicked == true){
            Mix_HaltMusic();
            sceneComponentAsset = new SceneComponentAsset();
            playerCar = new PlayerCar(sceneComponentAsset);
            runningScreen();
            Map::renderHoles = false;
            sceneComponentAsset = new SceneComponentAsset();
            playerCar = new PlayerCar(sceneComponentAsset);
            Mix_PlayMusic(GeneralThings::gameGeneralThings->menuSoundTrack, -1);
            GeneralThings::gameGeneralThings->playButton->isClicked = false;
        }
        if(GeneralThings::gameGeneralThings->helpButton->isClicked == true){
            helpScreen();
            GeneralThings::gameGeneralThings->helpButton->isClicked = false;
        }
        if(GeneralThings::gameGeneralThings->quitButton->isClicked == true){
            close();
            GeneralThings::gameGeneralThings->quitButton->isClicked = false;
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
            GeneralThings::gameGeneralThings->backButton->handleEvent(&event);
        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();

        // Render Part
        sceneComponentAsset->render();
        Materials::gameMaterials->render(
            "helpBoard",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["helpBoard"].w) / 2,
            40,
            SDL_FLIP_NONE
        );
        GeneralThings::gameGeneralThings->backButton->render();

        // Interaction
        if(GeneralThings::gameGeneralThings->backButton->isClicked == true){
            GeneralThings::gameGeneralThings->backButton->isClicked = false;
            break;
        }
        Materials::gameMaterials->print();
    }
}

void Game::runningScreen(){
    Map::renderHoles = true;
    score = 0;
    Mix_PlayMusic(GeneralThings::gameGeneralThings->gameSoundTrack, -1);
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
        playerCar->translateTheMovement();
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();

        // Core game logic
        Map::playerMoveDirection = PlayerCar::moveDirectionStatus;
        Map::playerVelocity = PlayerCar::recentVelocityStatus;

        if(playerCar->checkCandyCollider("coin")){
            Mix_PlayChannel(-1, GeneralThings::gameGeneralThings->coinSound, 0);
            score += scoreForCoin + rand() % 4;
            sceneComponentAsset->renderBackground->candyCoin = false;
        }
        if(playerCar->checkCandyCollider("showDirection")){
            Mix_PlayChannel(-1, GeneralThings::gameGeneralThings->showDirectionSound, 0);
            sceneComponentAsset->renderBackground->candyShowDirection = false;
            showDirectionStatus = true;
        }
        if(playerCar->checkCandyCollider("rainbow")){
            Mix_PlayMusic(GeneralThings::gameGeneralThings->eternalMusic, -1);
            sceneComponentAsset->renderBackground->candyRainbow = false;
            beEnternalStatus = true;
            changeVisibilityTime = 200;
            changeVisibilityPoint = SDL_GetTicks();
            beEnternalStartTime = changeVisibilityPoint;
        }
        if(!playerCar->checkBackground()) {
            showDirectionStatus &= 0;

            Mix_PlayChannel(-1, GeneralThings::gameGeneralThings->changeLight, 0);
            increasingTime -= 1;
            if(increasingTime % 4 == 3){
                theMapHaveCoin = rand() % 4;
            }
            if(increasingTime % 4 == theMapHaveCoin){
                sceneComponentAsset->turnCandyOn("coin");
            }
            if(increasingTime % 6 == 3){
                theMapHaveShowDirection = rand() % 6;
            }
            if(increasingTime % 6 == theMapHaveShowDirection){
                sceneComponentAsset->turnCandyOn("showDirection");
            }
            if(increasingTime == firstIncreasingTime / 2){
                sceneComponentAsset->turnCandyOn("rainbow");
                Map::minimumNumberOfHoles += 1;
            }
            if(increasingTime == 0){
                firstIncreasingTime += firstIncreasingTime * 3 / 4;
                increasingTime = firstIncreasingTime;
                Car::velocity += 1;
                score += 1;
                Map::spawnTime = std::max(Map::spawnTime - 20, 100);
                Map::minimumNumberOfHoles += 1;
            }
            Map::minimumNumberOfHoles = std::min(Map::minimumNumberOfHoles, 15);
            scoreForCoin += 1;
            score += 1;
        }
        Materials::gameMaterials->loadScore(score);

        // Render Part
        sceneComponentAsset->render();
        if(beEnternalStatus){
            if(!invisible){
                playerCar->render();
            }
            if(SDL_GetTicks() - changeVisibilityPoint >= changeVisibilityTime){
                changeVisibilityPoint = SDL_GetTicks();
                invisible ^= 1;
            }
            if(SDL_GetTicks() - beEnternalStartTime >= beEnternalTime){
                changeVisibilityTime = 40;
                if(SDL_GetTicks() - beEnternalStartTime >= beEnternalTime + warning){
                    Mix_PlayMusic(GeneralThings::gameGeneralThings->gameSoundTrack, -1);
                    beEnternalStatus = false;
                    changeVisibilityTime = 200;
                }
            }
        }else{
            playerCar->render();
        }
        Materials::gameMaterials->renderScore();
        if(showDirectionStatus){
            switch(sceneComponentAsset->renderBackground->nextDirection){
                case LEFT:
                    Materials::gameMaterials->render(
                        "left",
                        (SCREEN_WIDTH - Materials::gameMaterials->materials["left"].w) / 2 - 100,
                        (SCREEN_HEIGHT - Materials::gameMaterials->materials["left"].h) / 2,
                        SDL_FLIP_NONE
                    );
                    break;
                case UP:
                    Materials::gameMaterials->render(
                        "up",
                        (SCREEN_WIDTH - Materials::gameMaterials->materials["up"].w) / 2,
                        (SCREEN_HEIGHT - Materials::gameMaterials->materials["up"].h) / 2 - 100,
                        SDL_FLIP_NONE
                    );
                    break;
                case RIGHT:
                    Materials::gameMaterials->render(
                        "right",
                        (SCREEN_WIDTH- Materials::gameMaterials->materials["right"].w) / 2 + 100,
                        (SCREEN_HEIGHT - Materials::gameMaterials->materials["right"].h) / 2,
                        SDL_FLIP_NONE
                    );
                    break;
                case DOWN:
                    Materials::gameMaterials->render(
                        "down",
                        (SCREEN_WIDTH - Materials::gameMaterials->materials["down"].w) / 2,
                        (SCREEN_HEIGHT - Materials::gameMaterials->materials["down"].h) / 2 + 100,
                        SDL_FLIP_NONE
                    );
                    break;
                default:
                    break;
            }
        }

        // Interaction
        Materials::gameMaterials->print();
        if(playerCar->checkAnyAccident() && !beEnternalStatus){
            Mix_PlayMusic(GeneralThings::gameGeneralThings->carAccident, 0);
            gameOverScreen();
            Mix_HaltMusic();
            Mix_PlayMusic(GeneralThings::gameGeneralThings->gameSoundTrack, -1);
            if(goBackToMainMenu == true){
                break;
            }
        }
    }
}

void Game::pauseScreen(){
    Map::renderHoles = true;
    previousVelocity = Car::velocity;
    Car::velocity = 0;
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            GeneralThings::gameGeneralThings->resumeButton->handleEvent(&event);
        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();
        Materials::gameMaterials->loadScore(score);

        // Render Part
        sceneComponentAsset->render();
        playerCar->render();
        GeneralThings::gameGeneralThings->resumeButton->render();
        Materials::gameMaterials->renderScore();

        // Interaction
        if(GeneralThings::gameGeneralThings->resumeButton->isClicked == true){
            Car::velocity = previousVelocity;
            GeneralThings::gameGeneralThings->resumeButton->isClicked = false;
            break;
        }
        Materials::gameMaterials->print();
    }
}

void Game::gameOverScreen(){
    Map::renderHoles = true;
    Car::velocity = 0;
    highScore = std::max(score, highScore);
    while(!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            GeneralThings::gameGeneralThings->playAgainButton->handleEvent(&event);
            GeneralThings::gameGeneralThings->mainMenuButton->handleEvent(&event);
        }
        sceneComponentAsset->renderBackground->spawnEnemyCar(playerCar->x, playerCar->y);
        Materials::gameMaterials->clean();
        Materials::gameMaterials->loadText("score", std::to_string(score), 0);
        Materials::gameMaterials->loadText("highScore", std::to_string(highScore), 0);

        // Render Part
        sceneComponentAsset->render();
        Materials::gameMaterials->render(
            "pauseBoard",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["pauseBoard"].w) / 2,
            80,
            SDL_FLIP_NONE
        );
        Materials::gameMaterials->render(
            "yourScore",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["yourScore"].w) / 2,
            Materials::gameMaterials->materials["pauseBoard"].h / 2 - 100,
            SDL_FLIP_NONE
        );
        Materials::gameMaterials->render(
            "score",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["score"].w) / 2,
            Materials::gameMaterials->materials["pauseBoard"].h / 2,
            SDL_FLIP_NONE
        );
        Materials::gameMaterials->render(
            "highScoreText",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["highScoreText"].w) / 2,
            Materials::gameMaterials->materials["pauseBoard"].h / 2 + 100,
            SDL_FLIP_NONE
        );
        Materials::gameMaterials->render(
            "highScore",
            (SCREEN_WIDTH - Materials::gameMaterials->materials["highScore"].w) / 2,
            Materials::gameMaterials->materials["pauseBoard"].h / 2 + 200,
            SDL_FLIP_NONE
        );
        GeneralThings::gameGeneralThings->playAgainButton->render();
        GeneralThings::gameGeneralThings->mainMenuButton->render();

        // Interaction
        if(GeneralThings::gameGeneralThings->playAgainButton->isClicked == true){
            // Reset everything
            sceneComponentAsset = new SceneComponentAsset();
            playerCar = new PlayerCar(sceneComponentAsset);
            firstIncreasingTime = 3;
            scoreForCoin = 3;
            GeneralThings::gameGeneralThings->playAgainButton->isClicked = false;
            Car::velocity = startVelocity;
            Map::renderHoles = true;
            score = 0;
            break;
        }
        if(GeneralThings::gameGeneralThings->mainMenuButton->isClicked == true){
            goBackToMainMenu = true;
            GeneralThings::gameGeneralThings->mainMenuButton->isClicked = false;
            Car::velocity = startVelocity;
            break;
        }
        Materials::gameMaterials->print();
    }
}

void Game::close(){
    freopen("highScore.txt", "w", stdout);
    std::cout << highScore;
    Materials::gameMaterials->destroy();

    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}


