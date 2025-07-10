#ifndef SOUND_LOADER_H
#define SOUND_LOADER_H

#include <unordered_map>
#include <iostream>

#include "raylib.h"

class SoundLoader{
private:
    std::unordered_map<std::string, Sound> sounds;

public:
    void loadSound(std::string name, std::string path);
    Sound& getSound(std::string name);
    ~SoundLoader();
};

#endif // SOUND_LOADER_H