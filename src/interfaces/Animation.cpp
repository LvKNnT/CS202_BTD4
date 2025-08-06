#include "Animation.h"
#include "../core/Game.h"

Animation::Animation(const std::string& name, Vector2 position, int height, int width, int numFrames, float frameTime, bool isLooped)
    : name(name), position(position), height(height), width(width), numFrames(numFrames), frameTime(frameTime), isLooped(isLooped),
      currentFrame(0), elapsedTime(0.0f), rotation(0.0f), isPlaying(false) {
    for(int i = 0; i < numFrames; i++) {
        Texture2D frame = Game::Instance().getTextureManager().getTexture(name + std::to_string(i));
        frames.push_back(frame);
    }
}

Animation::~Animation() {

}

void Animation::update() {
    if(!isPlaying || frames.empty()) return;
    elapsedTime += GetFrameTime();
    if(elapsedTime >= frameTime) {
        if(currentFrame == numFrames - 1 && !isLooped) {
            isPlaying = false;
            return;
        }

        currentFrame = (currentFrame + 1) % numFrames;
        elapsedTime -= frameTime;
    }
}

void Animation::draw() const{
    if(!isPlaying || frames.empty()) return;

    float scale = std::min(((float) width / frames[currentFrame].width), ( (float) height / frames[currentFrame].height));
    DrawTextureEx(frames[currentFrame], position, rotation, scale, WHITE);
}

void Animation::setPosition(Vector2 newPosition) {
    position = newPosition;
}

void Animation::setRotation(float newRotation) {
    rotation = newRotation;
}

void Animation::start() {
    currentFrame = 0;
    elapsedTime = 0.0f;
    isPlaying = true;
}

void Animation::stop() {
    currentFrame = 0;
    elapsedTime = 0.0f;
    isPlaying = false;
}