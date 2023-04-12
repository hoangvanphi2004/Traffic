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

void SceneComponentAsset::goLeft(){
    // Center -> Right
    aroundRenderBackground[2] = renderBackground;
    aroundRenderBackground[2]->direction = RIGHT;
    // Left -> Center
    renderBackground = aroundRenderBackground[0];
    renderBackground->direction = DEFAULT;
    // Move old renderBackground data to new renderBackground data
    renderBackground->enemyCars = aroundRenderBackground[2]->enemyCars;
    aroundRenderBackground[2]->enemyCars.clear();
    renderBackground->previousDirection = RIGHT;
    renderBackground->previousLight = aroundRenderBackground[2]->nextLight;
    // Create new left
    createNewLeft();
    // Create new top
    createNewTop();
    // Create new bottom
    createNewBottom();
}

void SceneComponentAsset::goRight(){
    // Center -> Left
    aroundRenderBackground[0] = renderBackground;
    aroundRenderBackground[0]->direction = LEFT;
    // Right -> Center
    renderBackground = aroundRenderBackground[2];
    renderBackground->direction = DEFAULT;
    // Move old renderBackground data to new renderBackground data
    renderBackground->enemyCars = aroundRenderBackground[0]->enemyCars;
    aroundRenderBackground[0]->enemyCars.clear();
    renderBackground->previousDirection = LEFT;
    renderBackground->previousLight = aroundRenderBackground[0]->nextLight;
    // Create new right
    createNewRight();
    // Create new top
    createNewTop();
    // Create new bottom
    createNewBottom();
}

void SceneComponentAsset::goUp(){
    // Center -> Bottom
    aroundRenderBackground[3] = renderBackground;
    aroundRenderBackground[3]->direction = DOWN;
    // Top -> Center
    renderBackground = aroundRenderBackground[1];
    renderBackground->direction = DEFAULT;
    // Move old renderBackground data to new renderBackground data
    renderBackground->enemyCars = aroundRenderBackground[3]->enemyCars;
    aroundRenderBackground[3]->enemyCars.clear();
    renderBackground->previousDirection = DOWN;
    renderBackground->previousLight = aroundRenderBackground[3]->nextLight;
    // Create new left
    createNewLeft();
    // Create new right
    createNewRight();
    // Creat new top
    createNewTop();
}

void SceneComponentAsset::goDown(){
    // Center -> Top
    aroundRenderBackground[1] = renderBackground;
    aroundRenderBackground[1]->direction = UP;
    // Bottom -> Center
    renderBackground = aroundRenderBackground[3];
    renderBackground->direction = DEFAULT;
    // Move old renderBackground data to new renderBackground data
    renderBackground->enemyCars = aroundRenderBackground[1]->enemyCars;
    aroundRenderBackground[1]->enemyCars.clear();
    renderBackground->previousDirection = UP;
    renderBackground->previousLight = aroundRenderBackground[1]->nextLight;
    // Create new left
    createNewLeft();
    // Create new right
    createNewRight();
    // Create new bottom
    createNewBottom();
}
