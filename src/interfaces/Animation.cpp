#include "Animation.h"
#include "../core/Game.h"

Animation::Animation(const std::string& name, Vector2 position, float rotation, int height, int width, int numFrames, float frameTime, bool isLooped)
    : PanelElement(height, width, position), name(name), numFrames(numFrames), frameTime(frameTime), isLooped(isLooped),
      currentFrame(0), elapsedTime(0.0f), rotation(rotation), isPlaying(false) {
}

Animation::Animation(const std::string &name, int height, int width, int numFrames, float frameTime, bool isLooped)
    : PanelElement(height, width), name(name), numFrames(numFrames), frameTime(frameTime), isLooped(isLooped),
      currentFrame(0), elapsedTime(0.0f), rotation(0.0f), isPlaying(false) {
}

Animation::~Animation() {

}

void Animation::update() {
    if(!isPlaying || numFrames == 0 || !isAvailable) return;
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
    if(!isPlaying || numFrames == 0) return;
    Texture frame = Game::Instance().getTextureManager().getTexture(name + std::to_string(currentFrame));
    float scale = std::min((static_cast<float>(width) / frame.width), (static_cast<float>(height) / frame.height));
    DrawTextureEx(frame, position, rotation, scale, WHITE);
}

void Animation::setPosition(Vector2 newPosition)
{
    position = newPosition;
}

void Animation::setRotation(float newRotation) {
    rotation = newRotation;
}

bool Animation::isAnimationPlaying() const {
    return isPlaying;
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
