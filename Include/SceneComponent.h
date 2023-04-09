#pragma once

#include <SDL.h>
#include <iostream>

#include "def.h"
#include "Materials.h"

class SceneComponent{
public:
    std::string sceneComponentName;
    int x, y;
    Materials* sceneMaterial;
public:
    SceneComponent(){};
    SceneComponent(Materials* sceneMaterial, int x, int y, std::string SceneComponentName);

    int getWidth();
    int getHeight();

    void render();
    void translateView(Direction direction, int velocity);
};
