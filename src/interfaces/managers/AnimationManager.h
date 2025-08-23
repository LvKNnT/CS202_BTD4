#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "raylib.h"
#include "../Animation.h"

#include <unordered_map>
#include <vector>
#include <string>

class AnimationManager {
private:
    std::vector<Animation> animations;
public:
    void loadAllAnimationTextures(std::string name, std::string path, int numFrames);
    void addAnimation(const Animation& animation);
    void update();
    void draw() const;
};

#endif // ANIMATION_MANAGER_H