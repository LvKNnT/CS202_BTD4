#include "StateStack.h"

void StateStack::pushState(std::shared_ptr<State> state) {
    states.push_back(std::move(state));
    drawPreviousState = false;
}

void StateStack::popState() {
    if(states.empty()) return;
    drawPreviousState = false;
    states.pop_back();
}

// State* StateStack::currentState() {
//     if (!states.empty()) {
//         return states.back().get();
//     }
//     return nullptr;
// }

void StateStack::clear() {
    states.clear();
    drawPreviousState = false;
}

void StateStack::setdrawPreviousState(bool _drawPreviousState) {
    drawPreviousState = _drawPreviousState;
}

void StateStack::update(Event::Type event) {
    if (!states.empty()) {
        states.back()->update(event);
    }
}

void StateStack::draw() const {
    if (!states.empty()) {
        if(drawPreviousState && (int) states.size() >= 2) {
            states[(int) states.size() - 2]->draw();
        } 
        if(states.back()) states.back()->draw();
    }
}

void StateStack::handleInput() {
    if (!states.empty()) {
        if(states.back()) states.back()->handleInput();
    }
}
