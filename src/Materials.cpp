#include "../Include/Materials.h"

Materials* Materials::gameMaterials = new Materials();

void Materials::loadMaterials(){
    loadMaterial("background", "../Traffic/Assets/Background.png");
    loadMaterial("playerHorizontal", "../Traffic/Assets/PlayerHorizontal.png");
    loadMaterial("playerVertical", "../Traffic/Assets/PlayerVertical.png");
    for(int i = 1; i <= 3; i++){
        loadMaterial("car" + std::to_string(i) + "Horizontal", "../Traffic/Assets/Car" + std::to_string(i) + "Horizontal.png");
        loadMaterial("car" + std::to_string(i) + "Vertical", "../Traffic/Assets/Car" + std::to_string(i) + "Vertical.png");
        loadMaterial("block" + std::to_string(i), "../Traffic/Assets/Block" + std::to_string(i) + ".png");
    }
    loadMaterial("redLight", "../Traffic/Assets/RedLight.png");
    loadMaterial("greenLight", "../Traffic/Assets/GreenLight.png");
    loadMaterial("yellowLight", "../Traffic/Assets/YellowLight.png");
}

void Materials::loadMaterial(std::string materialName, std::string path){
    SDL_Surface* surface;
    surface = IMG_Load(path.c_str());
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0));
    materials[materialName].texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(materials[materialName].texture, NULL, NULL, &materials[materialName].w, &materials[materialName].h);

    SDL_FreeSurface(surface);
}

void Materials::render(std::string materialName, float x, float y, SDL_RendererFlip flip){
    SDL_Rect camera;
    camera.x = x;
    camera.y = y;
    camera.w = materials[materialName].w;
    camera.h = materials[materialName].h;
    SDL_RenderCopyEx(renderer, materials[materialName].texture, NULL, &camera, NULL, NULL, flip);
}

void Materials::print(){
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderPresent(renderer);
}

void Materials::clean(){
    SDL_RenderClear(renderer);
}

void Materials::destroy(){
    SDL_DestroyTexture(materials["background"].texture);
    SDL_DestroyTexture(materials["playerHorizontal"].texture);
    SDL_DestroyTexture(materials["playerVertical"].texture);
    for(int i = 1; i <= 3; i++){
        SDL_DestroyTexture(materials["car" + std::to_string(i) + "Horizontal", "../GoHome/Assets/Car"].texture);
        SDL_DestroyTexture(materials["car" + std::to_string(i) + "Horizontal", "../GoHome/Assets/Car"].texture);
        SDL_DestroyTexture(materials["block" + std::to_string(i)].texture);
    }
    SDL_DestroyTexture(materials["redLight"].texture);
    SDL_DestroyTexture(materials["greenLight"].texture);
    SDL_DestroyTexture(materials["yellowLight"].texture);
}
