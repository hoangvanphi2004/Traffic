#pragma once

#include <SDL.h>

#include "Materials.h"
#include "EnemyCar.h"
#include "Map.h"
#include "SceneComponent.h"

class SceneComponentAsset{
public:
    Map* renderBackground;
    Map* aroundRenderBackground[4];
    Materials* materials;
    int addVelocityValue = 0;
public:
    SceneComponentAsset(Materials* materials);

    void render();
    void translateView(Direction direction, int velocity);

    void createNewLeft();
    void createNewRight();
    void createNewTop();
    void createNewBottom();

    void goLeft();
    void goRight();
    void goUp();
    void goDown();

    void addVelocity();
};

