#include "StateStack.h"

void StateStack::pushState(std::unique_ptr<State> state) {
    states.push_back(std::move(state));
}

void StateStack::popState() {
    if (!states.empty()) {
        states.pop_back();
    }
}

std::unique_ptr<State> StateStack::currentState() {
    if (!states.empty()) {
        return std::move(states.back());
    }
    return nullptr;
}

void StateStack::clear() {
    states.clear();
}

void StateStack::update() {
    if (!states.empty()) {
        states.back()->update();
    }
}

void StateStack::draw() {
    if (!states.empty()) {
        states.back()->draw();
    }
}

void StateStack::handleInput() {
    if (!states.empty()) {
        states.back()->handleInput();
    }
}
