#ifndef LOADING_STATE_H
#define LOADING_STATE_H

#include "State.h"

class LoadingState : public State {
public:
    LoadingState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // LOADING_STATE_H