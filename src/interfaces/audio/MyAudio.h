#ifndef MY_AUDIO_H
#define MY_AUDIO_H

#include <string>
#include <memory>

#include "raylib.h"

class MyAudio {
protected:
    std::string name;
public:
    MyAudio(std::string _name) : name(_name) {}
    virtual void start() = 0;
    virtual void stop() = 0;
};

class MySound : public MyAudio {
public:
    MySound(std::string _name) : MyAudio(_name) {}
    void start() override;
    void stop() override;
};

class MyMusic : public MyAudio {
public:
    MyMusic(std::string _name) : MyAudio(_name) {}
    void start() override;
    void stop() override;
};

#endif // MY_AUDIO_H