#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "State.h"

class GameOverState : public State {
public:
    GameOverState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // GAME_OVER_STATE_H