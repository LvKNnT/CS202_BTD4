#include "SoundLoader.h"

void SoundLoader::loadSound(std::string name, std::string path) {
    Sound newSound = LoadSound(path.c_str());
    if(newSound.frameCount == 0 || newSound.stream.buffer == nullptr) {
        std::cout<<"Error: Failed to load sound"<<path<<"\n";
        return;
    }
    
    sounds[name] = newSound;
}

Sound &SoundLoader::getSound(std::string name) {
    auto it = sounds.find(name);
    if(it != sounds.end()) return it->second;
    std::cout<<"Warning: sound "<<name<<" not found\n";
    static Sound empty = {0};
    return empty;
}

SoundLoader::~SoundLoader() {
    for(auto &sound:sounds) {
        UnloadSound(sound.second);
    }
}
