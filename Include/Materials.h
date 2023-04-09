#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<SDL.h>
#include<SDL_image.h>

#include "def.h"

struct Material{
    SDL_Texture* texture;
    int w, h;
};

class Materials{
public:
    SDL_Renderer* renderer;
    std::map<std::string, Material> materials;
public:
    void loadMaterials();

    void loadMaterial(std::string materialName, std::string path);

    void render(std::string materialName, int x, int y, SDL_RendererFlip flip);

    void print();
    void clean();

    void destroy();

};

