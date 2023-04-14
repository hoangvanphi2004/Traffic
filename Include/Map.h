#pragma once

#include <SDL.h>
#include <list>
#include <ctime>
#include <cstdlib>

#include "def.h"
#include "EnemyCar.h"
#include "SceneComponent.h"

class Map{
public:
    // This direction relative to the center background screen
    //
    //                     up
    //                      ^
    //                      |
    //     left <-- center background --> right
    //                      |
    //                      v
    //                    down
    Direction direction;
    Direction previousDirection = DEFAULT;
    Direction nextDirection = DEFAULT;
private:
    // Spawn enemy position
    int left[2] = {640, 560};
    int up[6] = {650, 702, 754, 806, 858, 910};
    int right[2] = {440, 350};
    int down[6] ={962, 1014, 1066, 1118, 1170, 1222};

    int blockRoadPositionX[4] = {0, 640, 0, 640};
    int blockRoadPositionY[4] = {360, 0, 360, 0};

    int turn = 1;
    int chosenRoad;
    EnemyCar* chosenEnemyCar;
public:
    static int spawnTime;
    Uint32 previousTimeSpawn;

    SceneComponent* nextLight;
    SceneComponent* previousLight;
    std::list <SceneComponent*> lights;

    std::list <EnemyCar*> enemyCars;
    std::list <SceneComponent*> blockRectangles;
    // This component contain the main materials
    SceneComponent* background;
public:
    Map(SceneComponent* background, Direction direction);

    void renderBackground();
    void renderSceneComponents();
    void translateView(Direction direction, int velocity);

    bool checkAnyFutureCollider(EnemyCar* enemyCar);

    void createEnemyCar(int roadLanes, int x, int y, Direction direction);
    void spawnEnemyCar(int x, int y);
    void clearEnemyCar();

    // Fix the light and add the block to the road
    SceneComponent* createLight(std::string color, Direction direction);
    void addBlock();
    void spawnBlockRoads();

};
