#ifndef MODE_SELECTION_STATE_H
#define MODE_SELECTION_STATE_H

#include "State.h"

class ModeSelectionState : public State {
public:
    ModeSelectionState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // MODE_SELECTION_STATE_H