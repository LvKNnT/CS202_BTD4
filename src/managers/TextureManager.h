#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <set>
#include <string>
#include <iostream>

#include "raylib.h"

class TextureManager {
private:
    std::map<std::string, Texture> textures;

public:
    ~TextureManager();
    void loadTexture(std::string name, std::string path);
    void unloadAllTextures();
    Texture &getTexture(std::string name);
};

#endif // TEXTUREMANAGER_H