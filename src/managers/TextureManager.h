#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <string>
#include <iostream>
#include "raylib.h"

class TextureMananger {
private:
    std::unordered_map<std::string, Texture> textures;

public:
    ~TextureMananger();
    void loadTexture(std::string name, std::string path);
    Texture getTexture(std::string name);
};

#endif // TEXTUREMANAGER_H