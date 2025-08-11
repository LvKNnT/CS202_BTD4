#include "AnimationManager.h"
#include "../../core/Game.h"

void AnimationManager::loadAllAnimationTextures(std::string name, std::string path, int numFrames) {
    for(int i = 0; i < numFrames; i++) {
        Game::Instance().getTextureManager().loadTextureDraw(name + std::to_string(i), path + "/" + name + std::to_string(i) + ".png");
    }
}

void AnimationManager::addAnimation(const Animation &animation) {
    animations.push_back(animation);
}

void AnimationManager::update() {
    std::reverse(animations.begin(), animations.end());
    while(!animations.empty() && animations.back().isAnimationPlaying() == false) {
        animations.pop_back();
    }
    std::reverse(animations.begin(), animations.end());
    for(auto &animation:animations) animation.update();
}

void AnimationManager::draw() const {
    for(auto &animation:animations) animation.draw();
}
