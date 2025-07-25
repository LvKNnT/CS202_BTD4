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
    void loadTexture(std::string name, std::string path);
    Texture &getTexture(std::string name);
    void unloadContent();
};

#endif // TEXTUREMANAGER_H