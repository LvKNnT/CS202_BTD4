#include "AudioChannel.h"

int AudioChannel::getVolume() const {
    return static_cast<int>(volume * 100);
}

void AudioChannel::increaseVolume() {
    setVolume(std::min(1.0f, volume + 0.2f));
}

void AudioChannel::decreaseVolume() {
    setVolume(std::max(0.0f, volume - 0.2f));
}

SoundChannel::SoundChannel() : AudioChannel() {
}

void SoundChannel::setVolume(float _volume) {
    volume = _volume;
    for(auto &sound:soundList) {
        sound.second.setVolume(volume);
    }

}

void SoundChannel::load(std::string name, std::string path, int maxSounds) {
    if(soundList.count(name) > 0) {
        std::cout << "SoundPool with name " << name << " already exists. Unloading old sound pool.\n";
        soundList[name].unloadSound();
    }
    
    SoundPool newSoundPool(name, path, maxSounds);
    soundList[name] = newSoundPool;
}

void SoundChannel::unload() {
    for(auto &sound:soundList) {
        sound.second.unloadSound();
    }
    soundList.clear();
}

void SoundChannel::play(std::string name) {
    if(soundList.count(name) > 0) {
        soundList[name].playSound();
    } else {
        std::cout<<"SoundPool with name "<<name<<" not found.\n";
    }
}

void SoundChannel::stop(std::string name) {
    if(soundList.count(name) > 0) {
        soundList[name].stopSound();
    } else {
        std::cout<<"SoundPool with name "<<name<<" not found.\n";
    }
}

MusicChannel::MusicChannel() : AudioChannel() {
}

void MusicChannel::setVolume(float _volume) {
    volume = _volume;
    for(auto &music:musicList) {
        SetMusicVolume(music.second, volume);
    }
}

void MusicChannel::load(std::string name, std::string path) {
    Music newMusic = LoadMusicStream(path.c_str());
    newMusic.looping = true;
    if(newMusic.frameCount == 0 || newMusic.stream.buffer == nullptr) {
        std::cout<<"Error: Failed to load music"<<path<<"\n";
        UnloadMusicStream(newMusic);
        return;
    }
    
    musicList[name] = newMusic;
}

void MusicChannel::unload() {
    for(auto &music:musicList) {
        if(IsMusicStreamPlaying(music.second)) StopMusicStream(music.second);
        UnloadMusicStream(music.second);
    }
    musicList.clear();
}

void MusicChannel::update() {
    for(auto &music:musicList) {
        UpdateMusicStream(music.second);
    }
}

void MusicChannel::play(std::string name) {
    if(musicList.count(name) > 0) {
        PlayMusicStream(musicList[name]);
    } else {
        std::cout<<"Music with name "<< name<<" not found.\n";
    }
}

void MusicChannel::stop(std::string name) {
    if(musicList.count(name) > 0) {
        StopMusicStream(musicList[name]);
    } else {
        std::cout<<"Music with name "<< name <<" not found.\n";
    }
}
