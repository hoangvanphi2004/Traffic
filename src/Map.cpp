#include "../Include/Map.h"

int Map::spawnTime = 400;
int Map::minimumNumberOfHoles = 3;

Map::Map(SceneComponent* background, Direction direction) : background(background){
    previousTimeSpawn = 0;
    this->direction = direction;
    srand(time(NULL));
    blockRectangles.push_back(new SceneComponent(background->x, background->y, "block1"));
    blockRectangles.push_back(new SceneComponent(background->x + background->getWidth() - blockRectangles.front()->getWidth(), background->y, "block1"));
    blockRectangles.push_back(new SceneComponent(background->x, background->y + background->getHeight() - blockRectangles.front()->getHeight(), "block1"));
    blockRectangles.push_back(new SceneComponent(background->x + background->getWidth() - blockRectangles.front()->getWidth(), background->y + background->getHeight() - blockRectangles.front()->getHeight(), "block1"));

    blockRoadPositionX[2] = background->getWidth() - 10;
    blockRoadPositionY[3] = background->getHeight() - 10;
    createHolesAndCandys();
}

void Map::renderBackground(){
    background->render();
    for(auto holeOrCandy: holesAndCandys){
        if(
            holeOrCandy->sceneComponentName == "hole" ||
            (holeOrCandy->sceneComponentName == "coin" && candyCoin == true) ||
            (holeOrCandy->sceneComponentName == "showDirection" && candyShowDirection== true) ||
            (holeOrCandy->sceneComponentName == "rainbow" && candyRainbow == true)
        ){
            holeOrCandy->render();
        }
    }
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
    for(auto holeOrCandy: holesAndCandys){
        holeOrCandy->translateView(direction, velocity);
    }
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

bool Map::checkAnyFutureCarCollider(EnemyCar* enemyCar){
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

bool Map::checkAnyHoleAndCandyCollider(SceneComponent* holeOrCandy){
    for(auto other: holesAndCandys){
        if(checkSceneComponentCollider(holeOrCandy, other)){
            return true;
        }
    }
    return false;
}

bool Map::checkSceneComponentCollider(SceneComponent* sceneComponent1, SceneComponent* sceneComponent2){
    if(sceneComponent1->x >= sceneComponent2->x + sceneComponent2->getWidth() || sceneComponent1->x + sceneComponent1->getWidth() <= sceneComponent2->x) return false;
    if(sceneComponent1->y >= sceneComponent2->y + sceneComponent2->getHeight() || sceneComponent1->y + sceneComponent1->getHeight() <= sceneComponent2->y) return false;
    return true;
}

void Map::createHolesAndCandys(){
    // List all position holes and candys can be placed
    int stx = background->x + 90;
    int enx = background->x + background->getWidth() - 90;

    while(stx < enx){
        int sty = background->y + 60;
        int eny = background->y + background->getHeight() - 60;
        while(sty < eny){
            if((600 < stx - background->x && stx - background->x < 1240) || (340 < sty - background->y && sty - background->y < 650)){
                canBePlacedPosition.push_back({stx, sty});
            }
            sty += 180;
        }
        stx += 140;
    }
    random_shuffle(canBePlacedPosition.begin(), canBePlacedPosition.end());

    int numberOfHoles = minimumNumberOfHoles + rand() % 4;

    SceneComponent* hole;
    for(int i = 0; i < numberOfHoles; i++){
        hole = new SceneComponent(canBePlacedPosition.back().first, canBePlacedPosition.back().second, "hole");
        canBePlacedPosition.pop_back();
        holesAndCandys.push_back(hole);
    }

    SceneComponent* coin = new SceneComponent(canBePlacedPosition.back().first, canBePlacedPosition.back().second, "coin");
    canBePlacedPosition.pop_back();
    holesAndCandys.push_back(coin);
    SceneComponent* showDirection = new SceneComponent(background->x + background->getWidth() / 2, background->y + background->getHeight() / 2, "showDirection");
    canBePlacedPosition.pop_back();
    holesAndCandys.push_back(showDirection);
    SceneComponent* rainbow = new SceneComponent(canBePlacedPosition.back().first, canBePlacedPosition.back().second, "rainbow");
    canBePlacedPosition.pop_back();
    holesAndCandys.push_back(rainbow);
}

bool Map::indentifyCandy(std::string candyName){
    if(candyName == "coin"){
        return candyCoin;
    }
    if(candyName == "showDirection"){
        return candyShowDirection;
    }
    if(candyName == "rainbow"){
        return candyRainbow;
    }
}

void Map::createEnemyCar(int roadLanes, int x, int y, Direction direction){
        chosenEnemyCar = new EnemyCar(x, y, rand() % 3 + 1, direction);
        if(SDL_GetTicks() - previousTimeSpawn > spawnTime && !checkAnyFutureCarCollider(chosenEnemyCar)){
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
            // Top Map
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
            // Bottom Map
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
            background->x + blockRoadPositionX[0] - 250,
            background->y + blockRoadPositionY[0] - 110,
            lightType
        );
    }
    if(direction == UP){
        return new SceneComponent(
            background->x + blockRoadPositionX[1] + Materials::gameMaterials->materials["block2"].w + 55,
            background->y + blockRoadPositionY[1] - 150,
            lightType
        );
    }
    if(direction == RIGHT){
        return new SceneComponent(
            background->x + blockRoadPositionX[2] + 250,
            background->y + blockRoadPositionY[2] + Materials::gameMaterials->materials["block3"].h + 35,
            lightType
        );
    }
    if(direction == DOWN){
        return new SceneComponent(
            background->x + blockRoadPositionX[3] - 90,
            background->y + blockRoadPositionY[3] + 150,
            lightType
        );
    }
}

void Map::addBlock(){
    // Add invisible wall to prevent player from going out the recent map
    if(nextDirection != LEFT){
        // Check if left is the previous direction, create a space for player car
        // The same for other directions
        if(previousDirection != LEFT){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[0],
                background->y + blockRoadPositionY[0],
                "block3"
            ));
            lights.push_back(createLight("redLight", LEFT));
        }else if(previousDirection != DEFAULT){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[0] - 30,
                background->y + blockRoadPositionY[0],
                "block3"
            ));
        }
    }
    if(nextDirection != UP){
        if(previousDirection != UP){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[1],
                background->y + blockRoadPositionY[1],
                "block2"
            ));
            lights.push_back(createLight("redLight", UP));
        }else if(previousDirection != DEFAULT){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[1],
                background->y + blockRoadPositionY[1] - 30,
                "block2"
            ));
        }
    }
    if(nextDirection != RIGHT){
        if(previousDirection != RIGHT){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[2],
                background->y + blockRoadPositionY[2],
                "block3"
            ));
            lights.push_back(createLight("redLight", RIGHT));
        }else if(previousDirection != DEFAULT){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[2] + 30,
                background->y + blockRoadPositionY[2],
                "block3"
            ));
        }
    }
    if(nextDirection != DOWN){
        if(previousDirection != DOWN){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[3],
                background->y + blockRoadPositionY[3],
                "block2"
            ));
            lights.push_back(createLight("redLight", DOWN));
        }else if(previousDirection != DEFAULT){
            blockRectangles.push_back(new SceneComponent(
                background->x + blockRoadPositionX[3],
                background->y + blockRoadPositionY[3] + 30,
                "block2"
            ));
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
