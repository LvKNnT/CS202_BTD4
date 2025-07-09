#ifndef SOUND_CHANNEL_H
#define SOUND_CHANNEL_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "MySound.h"

class SoundChannel {
private:
    float volume;
    float preVolume; // For mute sound
    bool isMuted;
    std::vector<MySound> soundList;    

public:
    SoundChannel(): volume(100.0f), preVolume(0.0f), isMuted(false) {}
    void setVolume(float _volume);
    void toggleMute();  
    void playSound(std::string soundName);
    int getVolume() const;
    void increaseVolume();
    void decreaseVolume();
};

class SFXSound : public SoundChannel {
public:
    SFXSound() : SoundChannel() {}
};

class MusicSound : public SoundChannel {
public:
    MusicSound() : SoundChannel() {}
}; 

class OtherSounds : public SoundChannel {
public:
    OtherSounds() : SoundChannel() {}
};

#endif // SOUND_CHANNEL_H