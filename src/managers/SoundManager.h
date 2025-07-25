#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <map>
#include <memory>

#include "../interfaces/SoundChannel.h"
#include "../core/IObserver.h"
#include "../core/Event.h"

class SoundManager : public IObserver{
public:
    enum class SoundType {
        SFXSound, 
        MusicSound, 
        OtherSounds
    };

private:
    std::map<SoundType, std::unique_ptr<SoundChannel>> soundChannels;

public:
    SoundManager();
    void setVolume(SoundType soundType, float _volume);
    void toggleMute(SoundType soundType);
    void playSound(SoundType soundType, std::string soundName);
    void increaseVolume(SoundType soundType);
    void decreaseVolume(SoundType soundType);
    int getVolume(SoundType soundType) const;

    void update(Event::Type event) override;
    void draw() const;
    void initialize();
    void handleInput();
};

#endif // SOUND_MANAGER_H