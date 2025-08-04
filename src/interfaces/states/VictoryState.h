#ifndef VICTORY_STATE_H
#define VICTORY_STATE_H

#include "State.h"

class VictoryState : public State {
public:
    VictoryState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // VICTORY_STATE_H