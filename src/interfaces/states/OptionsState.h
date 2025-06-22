#ifndef OPTIONS_STATE_H
#define OPTIONS_STATE_H

#include "State.h"

class OptionsState : public State {
public:
    OptionsState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // OPTIONS_STATE_H