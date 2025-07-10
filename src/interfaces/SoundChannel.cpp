#include "SoundChannel.h"

void SoundChannel::setVolume(float _volume) {
    volume = _volume;
    for(auto &sound:soundList) {
        sound.setSoundVolume(volume);
    }
}

void SoundChannel::toggleMute() {
    isMuted ^= 1;
    if(isMuted) {
        preVolume = volume;
        volume = 0.0f;
    } else volume = preVolume;

    setVolume(volume);
}

void SoundChannel::playSound(std::string soundName) {
    if(volume == 0.0f) return;
    auto it = std::find_if(soundList.begin(), soundList.end(),
    [&soundName](const MySound& s) {
        return s.getName() == soundName;
    });
    if(it == soundList.end()) {
        std::cout<<"Warning: sound "<<soundName<<" not found\n";
        return;
    }
    it->start();
}

int SoundChannel::getVolume() const {
    return (int) volume;
}

void SoundChannel::increaseVolume() {
    setVolume(std::min(100.0f, volume + 20.0f));
}

void SoundChannel::decreaseVolume() {
    setVolume(std::max(0.0f, volume - 20.0f));
}
