#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <map>
#include <vector>
#include <memory>

#include "../audio/AudioChannel.h"
#include "../../core/IObserver.h"
#include "../../core/Event.h"

enum class AudioType {
    MusicSound, 
    SFXSound 
};

class AudioManager : public IObserver{
private:
    std::map<AudioType, std::shared_ptr<AudioChannel>> audioChannels;

public:
    AudioManager();
    void loadSound(std::string name, std::string path, int maxSounds = 1);
    void loadMusic(std::string name, std::string path);
    void unload(); // unload all audio channels
    void play(AudioType audioType, std::string name);
    void stop(AudioType audioType, std::string name);
    void increaseVolume(AudioType audioType);
    void decreaseVolume(AudioType audioType);
    void mute(AudioType audioType);
    void unmute(AudioType audioType);
    int getVolume(AudioType audioType) const;

    void update(Event::Type event) override;
    void updateMusic(); // for music 
    void initialize();
};

#endif // AUDIO_MANAGER_H