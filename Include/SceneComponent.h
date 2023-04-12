#pragma once

#include <SDL.h>
#include <iostream>

#include "def.h"
#include "Materials.h"

class SceneComponent{
public:
    std::string sceneComponentName;
    int x, y;
public:
    SceneComponent(){};
    SceneComponent(int x, int y, std::string SceneComponentName);

    int getWidth();
    int getHeight();

    void render();
    void translateView(Direction direction, int velocity);
};
