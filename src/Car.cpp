#include "../Include/Car.h"

float Car::velocity;

Car::Car(std::string carName){
    this->carName = carName;
}

void Car::render(int x, int y){
    switch(moveDirection){
    case LEFT:
        Materials::gameMaterials->render(carName + "Horizontal", x, y, SDL_FLIP_NONE);
        w = Materials::gameMaterials->materials[carName + "Horizontal"].w;
        h = Materials::gameMaterials->materials[carName + "Horizontal"].h;
        break;
    case UP:
        Materials::gameMaterials->render(carName + "Vertical", x, y, SDL_FLIP_NONE);
        w = Materials::gameMaterials->materials[carName + "Vertical"].w;
        h = Materials::gameMaterials->materials[carName + "Vertical"].h;
        break;
    case RIGHT:
        Materials::gameMaterials->render(carName + "Horizontal", x, y, SDL_FLIP_HORIZONTAL);
        w = Materials::gameMaterials->materials[carName + "Horizontal"].w;
        h = Materials::gameMaterials->materials[carName + "Horizontal"].h;
        break;
    case DOWN:
        Materials::gameMaterials->render(carName + "Vertical", x, y, SDL_FLIP_VERTICAL);
        w = Materials::gameMaterials->materials[carName + "Vertical"].w;
        h = Materials::gameMaterials->materials[carName + "Vertical"].h;
        break;
    default:
        Materials::gameMaterials->render(carName + "Vertical", x, y, SDL_FLIP_NONE);
        w = Materials::gameMaterials->materials[carName + "Vertical"].w;
        h = Materials::gameMaterials->materials[carName + "Vertical"].h;
        break;
    }
}
