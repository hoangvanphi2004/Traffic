#include "../Include/def.h"
#include <bits/stdc++.h>

Direction opposite(Direction direction){
    Direction oppositeDirection;
    switch(direction){
    case LEFT:
        oppositeDirection = RIGHT;
        break;
    case UP:
        oppositeDirection = DOWN;
        break;
    case RIGHT:
        oppositeDirection = LEFT;
        break;
    case DOWN:
        oppositeDirection = UP;
        break;
    default:
        oppositeDirection = DEFAULT;
        break;
    }
    return oppositeDirection;
}

int changeDirectionToNumber(Direction direction){
    switch(direction){
    case LEFT:
        return 0;
        break;
    case UP:
        return 1;
        break;
    case RIGHT:
        return 2;
        break;
    case DOWN:
        return 3;
        break;
    default:
        return 4;
        break;
    }
}

Direction changeNumberToDirection(int number){
    switch(number){
    case 0:
        return LEFT;
        break;
    case 1:
        return UP;
        break;
    case 2:
        return RIGHT;
        break;
    case 3:
        return DOWN;
        break;
    default:
        return DEFAULT;
        break;
    }
}
