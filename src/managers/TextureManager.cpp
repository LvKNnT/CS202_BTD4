#include "TextureManager.h"

TextureMananger::~TextureMananger(){
    for(auto &texture:textures) {
        UnloadTexture(texture.second);
    }
    textures.clear();
}

void TextureMananger::loadTexture(std::string name, std::string path) {
    Texture newTexture = LoadTexture(path.c_str());
    if(newTexture.id == 0) {
        std::cerr<<"Error: Failed to load texture from "<<path<<"\n";
        return;
    }
    textures[name] = newTexture;
}

Texture TextureMananger::getTexture(std::string name) {
    return textures[name];
}
