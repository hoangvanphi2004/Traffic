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
public:
    SceneComponentAsset();

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

