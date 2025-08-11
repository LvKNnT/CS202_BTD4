#include "AudioManager.h"
#include "../audio/MyAudio.h"
#include "../../core/Game.h"

AudioManager::AudioManager() {
    audioChannels[AudioType::MusicSound] = std::make_shared<MusicChannel>();
    audioChannels[AudioType::SFXSound] = std::make_shared<SoundChannel>();
}

void AudioManager::loadSound(std::string name, std::string path, int maxSounds) {
    if (audioChannels.count(AudioType::SFXSound) > 0) {
        std::dynamic_pointer_cast<SoundChannel>(audioChannels[AudioType::SFXSound])->load(name, path, maxSounds);
    } else {
        std::cerr <<"SFXSound channel not found.\n";
    }
}

void AudioManager::loadMusic(std::string name, std::string path) {
    if (audioChannels.count(AudioType::MusicSound) > 0) {
        std::dynamic_pointer_cast<MusicChannel>(audioChannels[AudioType::MusicSound])->load(name, path);
    } else {
        std::cerr <<"MusicSound channel not found.\n";
    }
}

void AudioManager::initialize() {
    // play something
    //MyMusic mm("Kuru Kuru"); // declare MyMusic or MySound (in MyAudio.h) with the name of the sound 
    //mm.start();
    // MySound ms("Kuru Kuru");
    // ms.start();
}

void AudioManager::unload() {
    for(auto &channel:audioChannels) {
        channel.second->unload();
    }
    audioChannels.clear();
}

void AudioManager::play(AudioType audioType, std::string name) {
    if (audioChannels.count(audioType) > 0) {
        audioChannels[audioType]->play(name);
    } else {
        std::cerr << "Audio type "<< static_cast<int>(audioType)<<" not found.\n";
    }
}

void AudioManager::stop(AudioType audioType, std::string name) {
    if (audioChannels.count(audioType) > 0) {
        audioChannels[audioType]->stop(name);
    } else {
        std::cerr<<"Audio type "<<static_cast<int>(audioType)<<" not found.\n";
    }
}

void AudioManager::increaseVolume(AudioType audioType) {
    audioChannels[audioType]->increaseVolume();
}

void AudioManager::decreaseVolume(AudioType audioType) {
    audioChannels[audioType]->decreaseVolume();
}

void AudioManager::mute(AudioType audioType) {
    audioChannels[audioType]->mute();
}

void AudioManager::unmute(AudioType audioType) {
    audioChannels[audioType]->unmute();
}

int AudioManager::getVolume(AudioType audioType) const {
    return audioChannels.at(audioType)->getVolume();
}

bool AudioManager::isAudioPlaying(AudioType audioType, std::string name) {
    return audioChannels[audioType]->isAudioPlaying(name);
}

void AudioManager::updateMusic() {
    std::dynamic_pointer_cast<MusicChannel>(audioChannels[AudioType::MusicSound])->update();
}

void AudioManager::update(Event::Type event) {
    switch(event) {
        case Event::Type::HigherMusic:
            increaseVolume(AudioType::MusicSound);
            break;
        case Event::Type::LowerMusic:
            decreaseVolume(AudioType::MusicSound);
            break;
        case Event::Type::HigherSound:
            increaseVolume(AudioType::SFXSound);
            break;
        case Event::Type::LowerSound:
            decreaseVolume(AudioType::SFXSound);
            break;
        case Event::Type::MuteMusic:
            mute(AudioType::MusicSound);
            break;
        case Event::Type::UnmuteMusic:
            unmute(AudioType::MusicSound);
            break;
        case Event::Type::MuteSound:
            mute(AudioType::SFXSound);
            break;
        case Event::Type::UnmuteSound:
            unmute(AudioType::SFXSound);
            break;
    }
}

