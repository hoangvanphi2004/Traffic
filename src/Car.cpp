#include "../Include/Car.h"

Car::Car(Materials* carMaterials, std::string carName){
    this->carMaterials = carMaterials;
    this->carName = carName;
}

void Car::render(int x, int y){
    switch(moveDirection){
    case LEFT:
        this->carMaterials->render(carName + "Horizontal", x, y, SDL_FLIP_NONE);
        w = this->carMaterials->materials[carName + "Horizontal"].w;
        h = this->carMaterials->materials[carName + "Horizontal"].h;
        break;
    case UP:
        this->carMaterials->render(carName + "Vertical", x, y, SDL_FLIP_NONE);
        w = this->carMaterials->materials[carName + "Vertical"].w;
        h = this->carMaterials->materials[carName + "Vertical"].h;
        break;
    case RIGHT:
        this->carMaterials->render(carName + "Horizontal", x, y, SDL_FLIP_HORIZONTAL);
        w = this->carMaterials->materials[carName + "Horizontal"].w;
        h = this->carMaterials->materials[carName + "Horizontal"].h;
        break;
    case DOWN:
        this->carMaterials->render(carName + "Vertical", x, y, SDL_FLIP_VERTICAL);
        w = this->carMaterials->materials[carName + "Vertical"].w;
        h = this->carMaterials->materials[carName + "Vertical"].h;
        break;
    default:
        this->carMaterials->render(carName + "Vertical", x, y, SDL_FLIP_NONE);
        w = this->carMaterials->materials[carName + "Vertical"].w;
        h = this->carMaterials->materials[carName + "Vertical"].h;
        break;
    }
}
