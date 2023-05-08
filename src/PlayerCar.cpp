#include "../Include/PlayerCar.h"

PlayerCar::PlayerCar(SceneComponentAsset* sceneComponents) : Car("player"){
    this->sceneComponents = sceneComponents;
    w = Materials::gameMaterials->materials[carName + "Vertical"].w;
    h = Materials::gameMaterials->materials[carName + "Vertical"].h;
};

void PlayerCar::movement(SDL_Event& event){
    if(event.key.repeat == 0){
        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
            case SDLK_LEFT:
            case SDLK_a:
                addKey(LEFT);
                countKeyPress += 1;
                recentVelocity = velocity;
                break;
            case SDLK_UP:
            case SDLK_w:
                addKey(UP);
                countKeyPress += 1;
                recentVelocity = velocity;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                addKey(RIGHT);
                countKeyPress += 1;
                recentVelocity = velocity;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                addKey(DOWN);
                countKeyPress += 1;
                recentVelocity = velocity;
                break;
            default:
                break;
            }
        }
        if(event.type == SDL_KEYUP){
            switch(event.key.keysym.sym){
            case SDLK_LEFT:
            case SDLK_a:
                removeKey(LEFT);
                countKeyPress -= 1;
                if(countKeyPress == 0){
                    recentVelocity = 0;
                }
                break;
            case SDLK_UP:
            case SDLK_w:
                removeKey(UP);
                countKeyPress -= 1;
                if(countKeyPress == 0){
                    recentVelocity = 0;
                }
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                removeKey(RIGHT);
                countKeyPress -= 1;
                if(countKeyPress == 0){
                    recentVelocity = 0;
                }
                break;
            case SDLK_DOWN:
            case SDLK_s:
                removeKey(DOWN);
                countKeyPress -= 1;
                if(countKeyPress == 0){
                    recentVelocity = 0;
                }
                break;
            default:
                break;
            }
        }
    }
}

void PlayerCar::addKey(Direction direction){
    keyPress.push_back(direction);
    readingKey += 1;
    moveDirection = direction;
}

void PlayerCar::removeKey(Direction direction){
    // Iterate over each element
    for(int i = 0; i < readingKey; i++){
        if(keyPress[i] == direction){
            keyPress[i] = DEFAULT;
        }
    }
    while(keyPress[readingKey - 1] == DEFAULT && readingKey > 0){
        readingKey -= 1;
        keyPress.pop_back();
    }
    if(readingKey == 0){
        moveDirection = direction;
    }else{
        moveDirection = keyPress[readingKey - 1];
    }
}

void PlayerCar::translateTheMovement(){
    if(recentVelocity != 0){
        recentVelocity = velocity;
    }
    // keep player a bit far from the block to make the next render doesnt collider with player
    // this distance equal to 10
    int addX = moveDirection == LEFT ? -10 : (moveDirection == RIGHT ? 10 : 0);
    int addY = moveDirection == UP ? -10 : (moveDirection == DOWN ? 10 : 0);

    this->x = (SCREEN_WIDTH - w) / 2 + addX;
    this->y = (SCREEN_HEIGHT - h) / 2 + addY;
    if(moveDirection != DEFAULT){
        sceneComponents->translateView(moveDirection, recentVelocity);
        //Check if player can make the next move
        if(checkBlock()){
            if(moveDirection == LEFT){
                sceneComponents->translateView(opposite(moveDirection), recentBlock->x + recentBlock->getWidth() - x);
            }
            if(moveDirection == RIGHT){
                sceneComponents->translateView(opposite(moveDirection), x + w - recentBlock->x);
            }
            if(moveDirection == UP){
                sceneComponents->translateView(opposite(moveDirection), recentBlock->y + recentBlock->getHeight() - y);
            }
            if(moveDirection == DOWN){
                sceneComponents->translateView(opposite(moveDirection), y + h - recentBlock->y);
            }
        }
    }
}

void PlayerCar::render(){
    this->x = (SCREEN_WIDTH - w) / 2;
    this->y = (SCREEN_HEIGHT - h) / 2;
    Car::render(x, y);
}

bool PlayerCar::checkBlock(){
    for(auto block: sceneComponents->renderBackground->blockRectangles){
        if(sceneComponentCollider(block)){
            recentBlock = block;
            return true;
        }
    }
    return false;
}

bool PlayerCar::checkAnyAccident(){
    for(auto enemyCar: sceneComponents->renderBackground->enemyCars){
        if(enemyCarCollider(enemyCar)){
            return true;
        }
    }
    for(auto holeOrCandy: sceneComponents->renderBackground->holesAndCandys){
        if(holeOrCandy->sceneComponentName == "hole" && sceneComponentCollider(holeOrCandy)){
            return true;
        }
    }
    return false;
}

bool PlayerCar::enemyCarCollider(EnemyCar* enemyCar){
    if(x >= enemyCar->x + enemyCar->w || x + w <= enemyCar->x) return false;
    if(y >= enemyCar->y + enemyCar->h || y + h <= enemyCar->y) return false;
    return true;
}

bool PlayerCar::checkBackground(){
    if(!sceneComponentCollider(sceneComponents->renderBackground->background)){
        // Iterate over around background clockwise
        for(int i = 0; i < 4; i++){
            if(sceneComponentCollider(sceneComponents->aroundRenderBackground[i]->background)){
                if(i == 0){
                    sceneComponents->goLeft();
                }
                if(i == 1){
                    sceneComponents->goUp();
                }
                if(i == 2){
                    sceneComponents->goRight();
                }
                if(i == 3){
                    sceneComponents->goDown();
                }
            }
        }
        return false;
    }
    return true;
}

bool PlayerCar::sceneComponentCollider(SceneComponent* sceneComponent){
    if(x >= sceneComponent->x + sceneComponent->getWidth() || x + w <= sceneComponent->x) return false;
    if(y >= sceneComponent->y + sceneComponent->getHeight() || y + h <= sceneComponent->y) return false;
    return true;
}

bool PlayerCar::checkCandyCollider(std::string candyName){
    for(auto holeOrCandy: sceneComponents->renderBackground->holesAndCandys){
        if(holeOrCandy->sceneComponentName == candyName && sceneComponentCollider(holeOrCandy) && sceneComponents->renderBackground->indentifyCandy(candyName)){
            return true;
        }
    }
    return false;
}
