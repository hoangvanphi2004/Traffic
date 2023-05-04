#pragma once

#include<string>
#include<map>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include "def.h"
struct Material{
    SDL_Texture* texture;
    int w, h;
};

class Materials{
public:
    static Materials* gameMaterials;

    SDL_Renderer* renderer;
    std::map<std::string, Material> materials;
    TTF_Font* generalFont;
public:
    void loadMaterials();

    void loadMaterial(std::string materialName, std::string path);
    TTF_Font* loadFont(std::string path, int fontSize);
    void loadText(std::string name, std:: string text, bool textColor);
    void loadScore(int score);

    void renderScore();

    void render(std::string materialName, float x, float y, SDL_RendererFlip flip);

    void print();
    void clean();

    void destroy();

};

