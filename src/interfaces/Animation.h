#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"
#include "PanelElement.h"

#include <string>
#include <vector>

class Animation : public PanelElement {
private:
    std::string name;
    float rotation;
    bool isLooped;
    bool isPlaying;
    
    int currentFrame;
    int numFrames;
    float frameTime;
    float elapsedTime;

public:
    Animation() = default;
    // The name is the name of animation textures we want to play 
    Animation(const std::string &name, Vector2 position, float rotation, int heght, int width, int numFrames, float frameTime, bool isLooped = false);
    Animation(const std::string &name, int heght, int width, int numFrames, float frameTime, bool isLooped = false);
    ~Animation();

    void setPosition(Vector2 newPosition);
    void setRotation(float newRotation);
    bool isAnimationPlaying() const;
    void update() override;
    void draw() const;
    void start();
    void stop();
};

#endif // ANIMATION_H