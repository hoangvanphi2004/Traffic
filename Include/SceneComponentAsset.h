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
    // This method make other stuff move relative to the player
    void translateView(Direction direction, int velocity);

    // Create new map every time the player get out of recent map
    void createNewLeft();
    void createNewRight();
    void createNewTop();
    void createNewBottom();

    // Push everything to new map
    void push(int firstPoint, int secondPoint, Direction direction);

    // Render map depend on the moving direction of the player
    void goLeft();
    void goRight();
    void goUp();
    void goDown();

    // Make the next map have candy
    void turnCandyOn(std::string candyName);
};

