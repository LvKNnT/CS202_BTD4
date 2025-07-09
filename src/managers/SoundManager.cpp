#include "SoundManager.h"

SoundManager::SoundManager() {
    soundChannels[SoundManager::SoundType::SFXSound] = std::make_unique<SFXSound>();
    soundChannels[SoundManager::SoundType::MusicSound] = std::make_unique<MusicSound>();
    soundChannels[SoundManager::SoundType::OtherSounds] = std::make_unique<OtherSounds>();
}

void SoundManager::setVolume(SoundType soundType, float _volume) {
    soundChannels[soundType]->setVolume(_volume);
}

void SoundManager::toggleMute(SoundType soundType) {
    soundChannels[soundType]->toggleMute();
}

void SoundManager::playSound(SoundType soundType, std::string soundName) {
    soundChannels[soundType]->playSound(soundName);
}

void SoundManager::increaseVolume(SoundType soundType) {
    soundChannels[soundType]->increaseVolume();
}

void SoundManager::decreaseVolume(SoundType soundType) {
    soundChannels[soundType]->decreaseVolume();
}

int SoundManager::getVolume(SoundType soundType) const {
    return soundChannels.at(soundType)->getVolume();
}

void SoundManager::initialize() {

}

void SoundManager::draw() const {
    
}

void SoundManager::handleInput() {
    
}

void SoundManager::update(Event::Type event) {
    switch(event) {
        case Event::Type::HigherMusic:
            increaseVolume(SoundManager::SoundType::MusicSound);
            break;
        case Event::Type::LowerMusic:
            decreaseVolume(SoundManager::SoundType::MusicSound);
            break;
        case Event::Type::HigherSound:
            increaseVolume(SoundManager::SoundType::SFXSound);
            break;
        case Event::Type::LowerSound:
            decreaseVolume(SoundManager::SoundType::SFXSound);
            break;
    }
}

