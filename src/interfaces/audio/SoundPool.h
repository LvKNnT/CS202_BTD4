#ifndef SOUND_POOL_H
#define SOUND_POOL_H

#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>

class SoundPool {
private:
    std::vector<Sound> sounds;
    int maxSounds;
    int currentIndex;

public:
    SoundPool() = default;
    SoundPool(std::string name, std::string path, int maxSounds = 1);
    ~SoundPool() = default;
    bool isSoundPlaying();
    void playSound();
    void stopSound();
    void setVolume(float volume);
    void unloadSound();
};

#endif // SOUND_POOL_H