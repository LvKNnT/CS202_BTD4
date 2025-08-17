#ifndef AUDIO_CHANNEL_H
#define AUDIO_CHANNEL_H

#include "raylib.h"
#include "SoundPool.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

class AudioChannel {
protected:
    float volume;
    bool isMuted;

public:
    AudioChannel(): volume(1.0f), isMuted(false) {}
    int getVolume() const;
    virtual void setVolume(float _volume) = 0;
    virtual void play(std::string name) = 0;
    virtual void stop(std::string name) = 0;
    virtual void increaseVolume();
    virtual void decreaseVolume();
    virtual bool isAudioPlaying(std::string name) = 0;
    virtual bool isAudioMuted() const;
    virtual void mute() = 0;
    virtual void unmute();
    virtual void unload() = 0;
};

class SoundChannel : public AudioChannel {
private:
    std::unordered_map<std::string, SoundPool> soundList;

public:
    SoundChannel();
    void setVolume(float _volume) override;
    void mute() override;
    bool isAudioPlaying(std::string name) override;
    void load(std::string name, std::string path, int maxSounds = 1);
    void unload() override;
    void play(std::string name) override;
    void stop(std::string name) override;
};

class MusicChannel : public AudioChannel {
private: 
    std::unordered_map<std::string, Music> musicList;

public:
    MusicChannel();
    void setVolume(float _volume) override;
    void mute() override;
    bool isAudioPlaying(std::string name) override;
    void load(std::string name, std::string path);
    void unload() override;
    void update();
    void play(std::string name) override;
    void stop(std::string name) override;
};

#endif // AUDIO_CHANNEL_H