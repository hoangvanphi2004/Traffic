#pragma once

#include<SDL.h>
#include<iostream>

#include "Materials.h"
#include "def.h"

class Car{
public:
    int w, h;
    Direction moveDirection = DEFAULT;
    static float velocity;
protected:
    float recentVelocity = 0;
    std::string carName;
protected:
    void render(int x, int y);
public:
    Car(std::string carName);
};
