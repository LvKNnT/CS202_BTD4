#include "StateStack.h"

int StateStack::getSize() const {
    return (int) states.size();
}

void StateStack::pushState(std::shared_ptr<State> state)
{
    states.push_back(std::move(state));
    drawPreviousStates = false;
}

void StateStack::popState() {
    if(states.empty()) return;
    drawPreviousStates = false;
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
    drawPreviousStates = false;
}

void StateStack::setdrawPreviousStates(bool _drawPreviousStates) {
    drawPreviousStates = _drawPreviousStates;
}

void StateStack::update(Event::Type event) {
    if (!states.empty()) {
        states.back()->update(event);
    }
}

void StateStack::draw() const {
    if (!states.empty()) {
        if(drawPreviousStates) {
            for(int i = 0; i < (int) states.size() - 1; i++) {
                states[i]->draw();
            }
        }
        if(states.back()) states.back()->draw();
    }
}

void StateStack::handleInput() {
    if (!states.empty()) {
        if(states.back()) states.back()->handleInput();
    }
}
