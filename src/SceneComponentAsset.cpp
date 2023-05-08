#include "../Include/SceneComponentAsset.h"
#include "../Include/def.h"

SceneComponentAsset::SceneComponentAsset(){
    renderBackground = new Map(
        new SceneComponent(
            (SCREEN_WIDTH - Materials::gameMaterials->materials["background"].w) / 2,
            (SCREEN_HEIGHT - Materials::gameMaterials->materials["background"].h) / 2,
             "background"
        ),
        DEFAULT
    );
    // Left render background
    aroundRenderBackground[0] = new Map(
        new SceneComponent(
            (SCREEN_WIDTH - Materials::gameMaterials->materials["background"].w) / 2 - Materials::gameMaterials->materials["background"].w,
            (SCREEN_HEIGHT - Materials::gameMaterials->materials["background"].h) / 2,
             "background"
        ),
        LEFT
    );
    // Right render background
    aroundRenderBackground[2] = new Map(
        new SceneComponent(
            (SCREEN_WIDTH - Materials::gameMaterials->materials["background"].w) / 2 + Materials::gameMaterials->materials["background"].w,
            (SCREEN_HEIGHT - Materials::gameMaterials->materials["background"].h) / 2,
             "background"
        ),
        RIGHT
    );
    // Top render background
    aroundRenderBackground[1] = new Map(
        new SceneComponent(
            (SCREEN_WIDTH - Materials::gameMaterials->materials["background"].w) / 2,
            (SCREEN_HEIGHT - Materials::gameMaterials->materials["background"].h) / 2 - Materials::gameMaterials->materials["background"].h,
             "background"
        ),
        UP
    );
    // Bottom render background
    aroundRenderBackground[3] = new Map(
        new SceneComponent(
            (SCREEN_WIDTH - Materials::gameMaterials->materials["background"].w) / 2,
            (SCREEN_HEIGHT - Materials::gameMaterials->materials["background"].h) / 2 + Materials::gameMaterials->materials["background"].h,
             "background"
        ),
        DOWN
    );

    renderBackground->spawnBlockRoads();
}

void SceneComponentAsset::render(){
    renderBackground->renderBackground();
    for(int i = 0; i < 4; i++){
        aroundRenderBackground[i]->renderBackground();
    }

    renderBackground->renderSceneComponents();
}

void SceneComponentAsset::translateView(Direction direction, int velocity){
    renderBackground->translateView(direction, velocity);
    for(int i = 0; i < 4; i++){
        aroundRenderBackground[i]->translateView(direction, velocity);
    }
}

void SceneComponentAsset::createNewLeft(){
    aroundRenderBackground[0] = new Map(
        new SceneComponent(
            renderBackground->background->x - Materials::gameMaterials->materials["background"].w,
            renderBackground->background->y,
             "background"
        ),
        LEFT
    );

}

void SceneComponentAsset::createNewRight(){
    aroundRenderBackground[2] = new Map(
        new SceneComponent(
            renderBackground->background->x + Materials::gameMaterials->materials["background"].w,
            renderBackground->background->y,
             "background"
        ),
        RIGHT
    );
}

void SceneComponentAsset::createNewTop(){
    aroundRenderBackground[1] = new Map(
        new SceneComponent(
            renderBackground->background->x,
            renderBackground->background->y - Materials::gameMaterials->materials["background"].h,
             "background"
        ),
        UP
    );
}

void SceneComponentAsset::createNewBottom(){
    aroundRenderBackground[3] = new Map(
        new SceneComponent(
            renderBackground->background->x,
            renderBackground->background->y + Materials::gameMaterials->materials["background"].h,
             "background"
        ),
        DOWN
    );
}

void SceneComponentAsset::push(int firstPoint, int secondPoint, Direction direction){
    // an example : If we go left (go from right to left) -> first point is right, second point is left

    // Center -> First point
    aroundRenderBackground[firstPoint] = renderBackground;
    aroundRenderBackground[firstPoint]->direction = opposite(direction);

    // Second point -> Center
    renderBackground = aroundRenderBackground[secondPoint];
    renderBackground->direction = DEFAULT;

    // Move old renderBackground data to new renderBackground data
    renderBackground->enemyCars = aroundRenderBackground[firstPoint]->enemyCars;
    aroundRenderBackground[firstPoint]->enemyCars.clear();
    renderBackground->previousDirection = opposite(direction);
    renderBackground->previousLight = aroundRenderBackground[firstPoint]->nextLight;
    renderBackground->spawnBlockRoads();
}

void SceneComponentAsset::goLeft(){
    push(2, 0, LEFT);

    // Create new left
    createNewLeft();
    // Create new top
    createNewTop();
    // Create new bottom
    createNewBottom();
}

void SceneComponentAsset::goRight(){
    push(0, 2, RIGHT);

    // Create new right
    createNewRight();
    // Create new top
    createNewTop();
    // Create new bottom
    createNewBottom();
}

void SceneComponentAsset::goUp(){
    push(3, 1, UP);

    // Create new left
    createNewLeft();
    // Create new right
    createNewRight();
    // Creat new top
    createNewTop();
}

void SceneComponentAsset::goDown(){
    push(1, 3, DOWN);

    // Create new left
    createNewLeft();
    // Create new right
    createNewRight();
    // Create new bottom
    createNewBottom();
}

void SceneComponentAsset::turnCandyOn(std::string candyName){
    if(candyName == "coin"){
        aroundRenderBackground[changeDirectionToNumber(renderBackground->nextDirection)]->candyCoin = true;
    }
    if(candyName == "showDirection"){
        aroundRenderBackground[changeDirectionToNumber(renderBackground->nextDirection)]->candyShowDirection = true;
    }
    if(candyName == "rainbow"){
        aroundRenderBackground[changeDirectionToNumber(renderBackground->nextDirection)]->candyRainbow = true;
    }
}
