#include "SoundPool.h"

SoundPool::SoundPool(std::string name, std::string path, int maxSounds)
    : maxSounds(maxSounds), currentIndex(0) {
    for(int i = 0; i < maxSounds; i++) {
        Sound sound = LoadSound(path.c_str());
        if (sound.stream.buffer == nullptr) {
            std::cerr<<"Failed to load sound: "<<name<<" from path: "<<path<<"\n";
        } else {
            sounds.push_back(sound);
        }
    }
}

bool SoundPool::isSoundPlaying() {
    for(auto sound:sounds) {
        if(IsSoundPlaying(sound)) return 1;
    }
    return 0;
}

void SoundPool::playSound()
{
    if (!sounds.empty()) {
        PlaySound(sounds[currentIndex]);
        currentIndex = (currentIndex + 1) % sounds.size();
    }
}

void SoundPool::stopSound() {
    if (!sounds.empty()) {
        StopSound(sounds[currentIndex]);
    }
}

void SoundPool::setVolume(float volume) {
    for (auto& sound:sounds) {
        SetSoundVolume(sound, volume);
    }
}

void SoundPool::unloadSound() {
    for (auto& sound:sounds) {
        UnloadSound(sound);
    }
    sounds.clear();
    currentIndex = 0;
}
