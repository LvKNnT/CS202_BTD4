#ifndef EASY_MODE_SELECTION_STATE_H
#define EASY_MODE_SELECTION_STATE_H

#include "State.h"

class EasyModeSelectionState : public State {
public:
    EasyModeSelectionState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // EASY_MODE_SELECTION_STATE_H