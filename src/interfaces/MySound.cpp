#include "MySound.h"
#include "../core/Game.h"

MySound::MySound(std::string _name) : name(_name) {
}

std::string MySound::getName() const{
    return name;
}

void MySound::start() {
    PlaySound(Game::Instance().getSoundLoader().getSound(name));
}

void MySound::stop() {
    StopSound(Game::Instance().getSoundLoader().getSound(name));
}

void MySound::setSoundVolume(float volume) {
    SetSoundVolume(Game::Instance().getSoundLoader().getSound(name), volume);
}
