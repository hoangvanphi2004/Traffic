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

    loadMaterial("hole", "../Traffic/Assets/Hole.png");
    loadMaterial("coin", "../Traffic/Assets/Coin.png");
    loadMaterial("showDirection", "../Traffic/Assets/ShowDirection.png");
    loadMaterial("rainbow", "../Traffic/Assets/Rainbow.png");

    loadMaterial("left", "../Traffic/Assets/Left.png");
    loadMaterial("up", "../Traffic/Assets/Up.png");
    loadMaterial("right", "../Traffic/Assets/Right.png");
    loadMaterial("down", "../Traffic/Assets/Down.png");

    loadMaterial("gameName", "../Traffic/Assets/GameName.png");

    loadMaterial("buttonIn1", "../Traffic/Assets/ButtonIn1.png");
    loadMaterial("buttonOut1", "../Traffic/Assets/ButtonOut1.png");
    loadMaterial("buttonIn2", "../Traffic/Assets/ButtonIn2.png");
    loadMaterial("buttonOut2", "../Traffic/Assets/ButtonOut2.png");

    loadMaterial("pauseBoard", "../Traffic/Assets/PauseBoard.png");
    loadMaterial("helpBoard", "../Traffic/Assets/HelpBoard.png");

    generalFont = loadFont("../Traffic/Assets/GeneralFont.ttf", 50);
    loadText("play", "Play", 1);
    loadText("help", "Help", 1);
    loadText("quit", "Quit", 1);
    loadText("yourScore", "Your score :", 0);
    loadText("highScoreText", "High score :", 0);


    generalFont = loadFont("../Traffic/Assets/GeneralFont.ttf", 25);
    loadText("mainMenu", "Main menu", 1);
    loadText("resume", "Resume", 1);
    loadText("playAgain", "Play again", 1);
    loadText("back", "Back", 1);

}

void Materials::loadMaterial(std::string materialName, std::string path){
    SDL_Surface* surface;
    surface = IMG_Load(path.c_str());
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0));
    materials[materialName].texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(materials[materialName].texture, NULL, NULL, &materials[materialName].w, &materials[materialName].h);

    SDL_FreeSurface(surface);
}

TTF_Font* Materials::loadFont(std::string path, int fontSize){
    return TTF_OpenFont(path.c_str(), fontSize);
}

void Materials::loadText(std::string name, std::string text, bool textColor){
    SDL_Surface* surface;
    SDL_Color color;
    if(textColor){
        color = {0, 0, 0};
    }else{
        color = {0xFF, 0xFF, 0xFF};
    }
    surface = TTF_RenderText_Solid(generalFont, text.c_str(), color);
    materials[name].texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(materials[name].texture, NULL, NULL, &materials[name].w, &materials[name].h);

    SDL_FreeSurface(surface);
}

void Materials::loadScore(int score){
    generalFont = loadFont("../Traffic/Assets/GeneralFont.ttf", 50);
    loadText("score", std::to_string(score), 0);
    TTF_SetFontOutline(generalFont, 2);
    loadText("outlineScore", std::to_string(score), 1);
    TTF_SetFontOutline(generalFont, 0);
}

void Materials::renderScore(){
    gameMaterials->render(
        "score",
        (SCREEN_WIDTH - Materials::gameMaterials->materials["score"].w) / 2,
        40,
        SDL_FLIP_NONE
    );
    gameMaterials->render(
        "outlineScore",
        (SCREEN_WIDTH - Materials::gameMaterials->materials["outlineScore"].w) / 2,
        40,
        SDL_FLIP_NONE
    );
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
    for(auto &value: materials){
        SDL_DestroyTexture(value.second.texture);
    }
}
