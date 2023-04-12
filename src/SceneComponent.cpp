#include "../Include/SceneComponent.h"

SceneComponent::SceneComponent(int x, int y, std::string sceneComponentName){
    this->x = x;
    this->y = y;
    this->sceneComponentName = sceneComponentName;
}

int SceneComponent::getWidth(){
    return Materials::gameMaterials->materials[sceneComponentName].w;
}

int SceneComponent::getHeight(){
    return Materials::gameMaterials->materials[sceneComponentName].h;
}

void SceneComponent::render(){
    Materials::gameMaterials->render(sceneComponentName, x, y, SDL_FLIP_NONE);
}

void SceneComponent::translateView(Direction direction, int velocity){
    Direction oppositeDirection = opposite(direction);
    switch(oppositeDirection){
    case LEFT:
        x -= velocity;
        break;
    case UP:
        y -= velocity;
        break;
    case RIGHT:
        x += velocity;
        break;
    case DOWN:
        y += velocity;
        break;
    default:
        break;
    }
}
