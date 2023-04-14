#include "../Include/Button.h"

Button::Button(std::string buttonName, int x, int y, int buttonType) : buttonName(buttonName), x(x), y(y), buttonType(buttonType){
    w = Materials::gameMaterials->materials[("buttonIn" + std::to_string(buttonType)).c_str()].w;
    h = Materials::gameMaterials->materials[("buttonIn" + std::to_string(buttonType)).c_str()].h;
}

bool Button::handleEvent(SDL_Event* event){
    if(status == true){
        if(event->type == SDL_MOUSEBUTTONDOWN){
            isClicked = true;
        }
    }
}

void Button::render(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(x < this->x || x > this->x + this->w){
        status = false;
    }else if(y < this->y || y > this->y + this->h){
        status = false;
    }else{
        status = true;
    }
    if(status){
        Materials::gameMaterials->render(
            ("buttonIn" + std::to_string(buttonType)).c_str(),
            this->x, this->y, SDL_FLIP_NONE);
    }else{
        Materials::gameMaterials->render(
            ("buttonOut" + std::to_string(buttonType)).c_str(),
            this->x, this->y, SDL_FLIP_NONE);
    }
    Materials::gameMaterials->render(
        buttonName,
        this->x + (this->w - Materials::gameMaterials->materials[buttonName].w) / 2,
        this->y + (this->h - Materials::gameMaterials->materials[buttonName].h) / 2,
        SDL_FLIP_NONE
    );
}
