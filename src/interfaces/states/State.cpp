#include "State.h"

State::State(int _height, int _width, const Texture &_background)
    : height(_height), width(_width), background(_background) {
}

void State::onButtonClick(std::shared_ptr<Button> button) {
}

void State::draw() const {
    DrawTextureEx(background, {0.0}, 0.0f, std::max((float) Properties::screenWidth / background.width, (float) Properties::screenHeight / background.height), WHITE);
    if (panel) {
        panel->draw();
    }
}

void State::update(Event::Type event) {
}

void State::handleInput() {
    if(panel) panel->handleInput();
}