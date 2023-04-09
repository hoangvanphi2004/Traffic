#pragma once

#include<SDL.h>
#include<iostream>

#include "Materials.h"
#include "def.h"

class Car{
public:
    int w, h;
    Direction moveDirection = DEFAULT;
    int velocity = 2;
protected:
    int recentVelocity = 0;
    std::string carName;

    Materials* carMaterials;
protected:
    void render(int x, int y);
public:
    Car(Materials* carMaterials, std::string carName);
};
