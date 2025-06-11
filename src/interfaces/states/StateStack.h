#ifndef STATE_STACK_H
#define STATE_STACK_H

#include <memory>
#include <vector>

#include "State.h"

class StateStack {
private:
    std::vector<std::unique_ptr<State>> states;
    bool drawPreviousState;

public:
    StateStack() : drawPreviousState(false) {}
    void pushState(std::unique_ptr<State> state);
    std::unique_ptr<State> popState();
    State* currentState();
    void clear();
    void setdrawPreviousState(bool _drawPreviousState);

    void update();
    void draw() const;
    void handleInput();
};

#endif // STATE_STACK_H