#ifndef STATE_STACK_H
#define STATE_STACK_H

#include <memory>
#include <vector>

#include "State.h"

class StateStack {
private:
    std::vector<std::unique_ptr<State>> states;

public:
    void pushState(std::unique_ptr<State> state);
    void popState();
    std::unique_ptr<State> currentState();
    void clear();

    void update();
    void draw();
    void handleInput();
};

#endif // STATE_STACK_H