#include "TextureManager.h"

TextureManager::~TextureManager(){
    for(auto &texture:textures) {
        UnloadTexture(texture.second);
    }
    textures.clear();
}

void TextureManager::loadTexture(std::string name, std::string path) {
    Texture newTexture = LoadTexture(path.c_str());
    if(newTexture.id == 0) {
        std::cerr<<"Error: Failed to load texture from "<<path<<"\n";
        return;
    }
    textures[name] = newTexture;
}

Texture &TextureManager::getTexture(std::string name) {
    auto it = textures.find(name);
    if (it != textures.end()) return it->second;
    static Texture empty = { 0 };
    std::cerr << "Warning: Texture " << name << " not found!\n";
    return empty;
}
