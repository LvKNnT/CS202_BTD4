#include "TextureManager.h"

TextureManager::~TextureManager(){
    unloadAllTextures();
}

void TextureManager::loadTexture(std::string name, std::string path) {
    if(textures.find(name) != textures.end()) {
        std::cerr << "Warning: Texture " << name << " already loaded!\n";
        return;
    }

    Texture newTexture = LoadTexture(path.c_str());
    if(newTexture.id == 0) {
        std::cerr<<"Error: Failed to load texture from "<<path<<"\n";
        return;
    }
    SetTextureFilter(newTexture, TEXTURE_FILTER_POINT);
    textures[name] = newTexture;
}

void TextureManager::unloadAllTextures() {
    for(auto &texture : textures) {
        UnloadTexture(texture.second);
    }
    textures.clear();
}

Texture &TextureManager::getTexture(std::string name) {
    auto it = textures.find(name);
    if (it != textures.end()) return it->second;
    static Texture empty = { 0 };
    std::cerr << "Warning: Texture " << name << " not found!\n";
    return empty; 
}
