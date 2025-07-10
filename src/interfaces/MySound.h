#ifndef MY_SOUND_H
#define MY_SOUND_H

#include<string>

#include "raylib.h"

class MySound {
private:
    std::string name;
    
public:
    MySound(std::string _name);
    std::string getName() const;
    void start();
    void stop();
    void setSoundVolume(float volume);
};

#endif // SOUND_H