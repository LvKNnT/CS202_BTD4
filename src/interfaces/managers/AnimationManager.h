#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "raylib.h"
#include "../Animation.h"

#include <unordered_map>
#include <string>

class AnimationManager {
private:
    std::unordered_map<std::string, Animation> animations;
public:
    void loadAllAnimationTextures(std::string name, std::string path, int numFrames);
    void addAnimation(const std::string& name, const Animation& animation);
    void startAnimation(const std::string& name);
    void stopAnimation(const std::string& name);
    void update();
};

#endif // ANIMATION_MANAGER_H