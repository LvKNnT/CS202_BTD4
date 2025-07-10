#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"

class GameState : public State {
public:
    GameState();
    void draw() const override;
};

#endif // GAME_STATE_H