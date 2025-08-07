#include "AnimationManager.h"
#include "../../core/Game.h"

void AnimationManager::loadAllAnimationTextures(std::string name, std::string path, int numFrames) {
    for(int i = 0; i < numFrames; i++) {
        Game::Instance().getTextureManager().loadTexture(name + std::to_string(i), path + "/" + name + std::to_string(i) + ".png");
    }
}

void AnimationManager::addAnimation(const std::string &name, const Animation &animation) {
    animations[name] = animation;
}

void AnimationManager::startAnimation(const std::string &name) {
    if(!animations.count(name)) {
        std::cerr<<"Animation with name "<<name <<" does not exist\n";
        return;
    }
    animations[name].start();
}

void AnimationManager::stopAnimation(const std::string &name) {
    if(!animations.count(name)) {
        std::cerr<<"Animation with name "<<name <<" does not exist\n";
        return;
    }
    animations[name].stop();
}

void AnimationManager::update() {
    for(auto &animation:animations) {
        animation.second.update();
    }
}