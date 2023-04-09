#pragma once

//window screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

enum Direction{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    DEFAULT
};

Direction opposite(Direction direction);

int changeDirectionToNumber(Direction direction);

Direction changeNumberToDirection(int number);
