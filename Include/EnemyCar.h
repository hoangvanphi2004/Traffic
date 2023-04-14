#pragma once

#include<SDL.h>
#include<string>

#include "def.h"
#include "Car.h"
#include "Materials.h"
#include "SceneComponent.h"

class EnemyCar: public Car, public SceneComponent{
private:
    int carType = 1;
public:
    EnemyCar(float x, float y, int carType, Direction moveDirection);

    void run();

    void render();

    bool futureCarCollider(EnemyCar* otherCar, float time);
};
