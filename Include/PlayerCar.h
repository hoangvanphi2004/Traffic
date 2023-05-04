#pragma once

#include <SDL.h>
#include <vector>

#include "Car.h"
#include "Materials.h"
#include "def.h"
#include "EnemyCar.h"
#include "SceneComponentAsset.h"
#include "SceneComponent.h"

class PlayerCar: public Car{
public:
    int x, y;
private:
    int countKeyPress = 0;
    int readingKey = 0;
    std::vector<Direction> keyPress;

    SceneComponent* recentBlock;
    SceneComponentAsset* sceneComponents;
public:
    PlayerCar(SceneComponentAsset* sceneComponents);

    void movement(SDL_Event& event);
    // Some more method to make player movement more smoth
    void addKey(Direction direction);
    void removeKey(Direction direction);

    void render();
    bool checkBlock();

    bool checkAnyAccident();
    bool enemyCarCollider(EnemyCar* enemyCar);

    // This methods check if we get out of recent map
    bool checkBackground();
    bool sceneComponentCollider(SceneComponent* sceneComponent);
};
