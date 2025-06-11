#ifndef MAP_SELECTION_STATE_H
#define MAP_SELECTION_STATE_H

#include "State.h"

class MapSelectionState : public State {
public:
    MapSelectionState();
    void draw() const override;
};

#endif // MAP_SELECTION_STATE_H