#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"

#include <string>
#include <vector>

class Animation {
private:
    std::string name;
    int height;
    int width;
    Vector2 position;
    float rotation;
    bool isLooped;
    bool isPlaying;
    
    int currentFrame;
    int numFrames;
    float frameTime;
    float elapsedTime;
    std::vector<Texture2D> frames;
public:
    Animation() = default;
    Animation(const std::string &name, Vector2 position, int heght, int width, int numFrames, float frameTime, bool isLooped = false);
    ~Animation();

    void setPosition(Vector2 newPosition);
    void setRotation(float newRotation);
    void update();
    void draw() const;
    void start();
    void stop();
};

#endif // ANIMATION_H