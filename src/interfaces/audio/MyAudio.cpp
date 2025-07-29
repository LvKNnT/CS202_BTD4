#include "MyAudio.h"
#include "../../core/Game.h"

void MySound::start() {
    std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->play(AudioType::SFXSound, name);
}

void MySound::stop() {
    std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->stop(AudioType::SFXSound, name);
}

void MyMusic::start() {
    std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->play(AudioType::MusicSound, name);
}

void MyMusic::stop() {
    std::dynamic_pointer_cast<AudioManager>(Game::Instance().getAudioManager())->stop(AudioType::MusicSound, name);
}
