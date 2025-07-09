#ifndef STATE_STACK_H
#define STATE_STACK_H

#include <memory>
#include <vector>

#include "State.h"

class StateStack {
private:
    std::vector<std::shared_ptr<State>> states;
    bool drawPreviousStates;

public:
    StateStack() : drawPreviousStates(false) {}
    void pushState(std::shared_ptr<State> state);
    void popState();
    //State* currentState();
    void clear();
    void setdrawPreviousStates(bool _drawPreviousStates);

    void update(Event::Type event);
    void draw() const;
    void handleInput();
};

#endif // STATE_STACK_H