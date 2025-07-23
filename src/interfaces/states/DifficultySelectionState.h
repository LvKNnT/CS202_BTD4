#ifndef DIFFICULTY_SELECTION_STATE_H
#define DIFFICULTY_SELECTION_STATE_H

#include "State.h"

class DifficultySelectionState : public State {
public:
    DifficultySelectionState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // DIFFICULTY_SELECTION_STATE_H