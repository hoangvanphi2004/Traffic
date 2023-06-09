#include "../Include/EnemyCar.h"

EnemyCar::EnemyCar(float x, float y, int carType, Direction moveDirection) : Car("car" + std::to_string(carType)){
    this->carType = carType;
    this->x = x;
    this->y = y;
    std::string materialName = carName;
    if(moveDirection == LEFT || moveDirection == RIGHT){
        materialName += "Horizontal";
    }else{
        materialName += "Vertical";
    }
    this->w = Materials::gameMaterials->materials[materialName].w;
    this->h = Materials::gameMaterials->materials[materialName].h;
    this->moveDirection = moveDirection;
}

void EnemyCar::run(){
    recentVelocity = velocity;
    switch(moveDirection){
    case LEFT:
        x -= recentVelocity;
        break;
    case UP:
        y -= recentVelocity;
        break;
    case RIGHT:
        x += recentVelocity;
        break;
    case DOWN:
        y += recentVelocity;
        break;
    default:
        break;
    }
}

void EnemyCar::render(){
    Car::render(x, y);
}

bool EnemyCar::futureCarCollider(EnemyCar* otherCar, float time){
    float addX = moveDirection == LEFT ? -time : (moveDirection == RIGHT ? time : 0);
    float addOtherCarX = otherCar->moveDirection == LEFT ? -time : (otherCar->moveDirection == RIGHT ? time : 0);
    float addY = moveDirection == UP ? -time : (moveDirection == DOWN ? time : 0);
    float addOtherCarY = otherCar->moveDirection == UP ? -time : (otherCar->moveDirection == DOWN ? time : 0);

    if(x + addX > otherCar->x + otherCar->w + addOtherCarX || x + w + addX < otherCar->x + addOtherCarX) return false;
    if(y + addY > otherCar->y + otherCar->h + addOtherCarY || y + h + addY < otherCar->y + addOtherCarY) return false;
    return true;
}
