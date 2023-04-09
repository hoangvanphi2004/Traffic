#include "../Include/Map.h"

Map::Map(SceneComponent* background, Direction direction) : background(background){
    previousTimeSpawn = 0;
    this->direction = direction;
    srand(time(NULL));
    blockRectangles.push_back(new SceneComponent(background->sceneMaterial, background->x, background->y, "block1"));
    blockRectangles.push_back(new SceneComponent(background->sceneMaterial, background->x + background->getWidth() - blockRectangles.front()->getWidth(), background->y, "block1"));
    blockRectangles.push_back(new SceneComponent(background->sceneMaterial, background->x, background->y + background->getHeight() - blockRectangles.front()->getHeight(), "block1"));
    blockRectangles.push_back(new SceneComponent(background->sceneMaterial, background->x + background->getWidth() - blockRectangles.front()->getWidth(), background->y + background->getHeight() - blockRectangles.front()->getHeight(), "block1"));
    blockRoadPositionX[2] = background->getWidth() - 10;
    blockRoadPositionY[3] = background->getHeight() - 10;
};

void Map::renderBackground(){
    background->render();
}

void Map::renderSceneComponents(){
    for(auto enemyCar: enemyCars){
        enemyCar->run();
        enemyCar->render();
    }
    for(auto blockRectangle: blockRectangles){
        blockRectangle->render();
    }
    if(this->direction == DEFAULT){
        for(auto light: lights){
            light->render();
        }
        if(previousDirection != DEFAULT){
            previousLight->render();
        }
        nextLight->render();
    }
}

void Map::translateView(Direction direction, int velocity){
    for(auto enemyCar: enemyCars){
        enemyCar->translateView(direction, velocity);
    }
    background->translateView(direction, velocity);
    for(auto blockRectangle: blockRectangles){
        blockRectangle->translateView(direction, velocity);
    }
    if(this->direction == DEFAULT){
        for(auto light: lights){
            light->translateView(direction, velocity);
        }
        if(previousDirection != DEFAULT){
            previousLight->translateView(direction, velocity);
        }
        nextLight->translateView(direction, velocity);
    }
}

bool Map::checkAnyFutureCollider(EnemyCar* enemyCar){
    // check if in crossroad have any collider
    for(auto otherEnemyCar: enemyCars){
        int leftCheck, rightCheck;
        if(enemyCar->moveDirection == RIGHT){
            leftCheck = background->x - enemyCar->x;
            rightCheck = leftCheck + background->getWidth();
        }else if(enemyCar->moveDirection == LEFT){
            leftCheck = enemyCar->x - (background->x + background->getWidth());
            rightCheck = leftCheck + background->getWidth();
        }else if(enemyCar->moveDirection == DOWN){
            leftCheck = background->y - enemyCar->y;
            rightCheck = leftCheck + background->getHeight();
            leftCheck -= background->getHeight();
        }else{
            leftCheck = enemyCar->y - (background->y + background->getHeight());
            rightCheck = leftCheck + background->getHeight();
            leftCheck -= background->getHeight();
        }
        for(int i = leftCheck; i <= rightCheck; i++){
            if(enemyCar->futureCarCollider(otherEnemyCar, i)){
                return true;
            }
        }
    }
    return false;
}

void Map::createEnemyCar(int roadLanes, int x, int y, Direction direction){
        chosenEnemyCar = new EnemyCar(background->sceneMaterial, x, y, rand() % 3 + 1, direction);
        if(SDL_GetTicks() - previousTimeSpawn > spawnTime && !checkAnyFutureCollider(chosenEnemyCar)){
            enemyCars.push_back(chosenEnemyCar);
            previousTimeSpawn = SDL_GetTicks();
            turn += 1;
        }
}

void Map::spawnEnemyCar(int x, int y){
    if(opposite(direction) == DEFAULT){
        turn %= 4;
        if(turn == 0){
            chosenRoad = rand() % 2;
            createEnemyCar(2, x - 1000, background->y + left[chosenRoad], RIGHT);
            createEnemyCar(2, x - 1000, background->y + background->getHeight() + left[chosenRoad], RIGHT);
            createEnemyCar(2, x - 1000, background->y - background->getHeight() + left[chosenRoad], RIGHT);
        }
        if(turn == 1){
            chosenRoad = rand() % 6;
            createEnemyCar(6, background->x + up[chosenRoad], y - 700, DOWN);
        }
        if(turn == 2){
            chosenRoad = rand() % 2;
            createEnemyCar(2, x + 1000, background->y + right[chosenRoad], LEFT);
            createEnemyCar(2, x + 1000, background->y + background->getHeight() + right[chosenRoad], LEFT);
            createEnemyCar(2, x + 1000, background->y - background->getHeight() + right[chosenRoad], LEFT);
        }
        if(turn == 3){
            chosenRoad = rand() % 6;
            createEnemyCar(6, background->x + down[chosenRoad], y + 700, UP);
        }
    }
}

void Map::clearEnemyCar(){
    for(auto enemyCar: enemyCars){
        if(enemyCar->x - background->x > background->getWidth()){
            enemyCars.remove(enemyCar);
        }
        if(enemyCar->y - background->y > background->getHeight()){
            enemyCars.remove(enemyCar);
        }
    }
}

SceneComponent* Map::createLight(std::string lightType, Direction direction){
    if(direction == LEFT){
        return new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[0] - 250,
            background->y + blockRoadPositionY[0] - 110,
            lightType
        );
    }
    if(direction == UP){
        return new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[1] + background->sceneMaterial->materials["block2"].w + 55,
            background->y + blockRoadPositionY[1] - 150,
            lightType
        );
    }
    if(direction == RIGHT){
        return new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[2] + 250,
            background->y + blockRoadPositionY[2] + background->sceneMaterial->materials["block3"].h + 35,
            lightType
        );
    }
    if(direction == DOWN){
        return new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[3] - 90,
            background->y + blockRoadPositionY[3] + 150,
            lightType
        );
    }
}

void Map::addBlock(){
    if(nextDirection != LEFT){
        blockRectangles.push_back(new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[0],
            background->y + blockRoadPositionY[0],
            "block3"
        ));
        if(previousDirection != LEFT){
            lights.push_back(createLight("redLight", LEFT));
        }
    }
    if(nextDirection != UP){
        blockRectangles.push_back(new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[1],
            background->y + blockRoadPositionY[1],
            "block2"
        ));
        if(previousDirection != UP){
            lights.push_back(createLight("redLight", UP));
        }
    }
    if(nextDirection != RIGHT){
        blockRectangles.push_back(new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[2],
            background->y + blockRoadPositionY[2],
            "block3"
        ));
        if(previousDirection != RIGHT){
            lights.push_back(createLight("redLight", RIGHT));
        }
    }
    if(nextDirection != DOWN){
        blockRectangles.push_back(new SceneComponent(
            background->sceneMaterial,
            background->x + blockRoadPositionX[3],
            background->y + blockRoadPositionY[3],
            "block2"
        ));
        if(previousDirection != DOWN){
            lights.push_back(createLight("redLight", DOWN));
        }
    }
}

void Map::spawnBlockRoads(){
    nextDirection = changeNumberToDirection(rand() % 4);
    while(nextDirection == previousDirection){
        nextDirection = changeNumberToDirection(rand() % 4);
    }
    addBlock();
    if(previousDirection != DEFAULT){
        previousLight->sceneComponentName = "yellowLight";
    }
    nextLight = createLight("greenLight", nextDirection);
}
