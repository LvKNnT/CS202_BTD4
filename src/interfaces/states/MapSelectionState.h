#ifndef MAP_SELECTION_STATE_H
#define MAP_SELECTION_STATE_H

#include "State.h"

class MapSelectionState : public State {
private:
    int curMap;
    PanelElement* nextMapButtonPtr;
    PanelElement* previousMapButtonPtr;
    PanelElement* ChooseMonkeyLaneButtonPtr;
    PanelElement* ChooseJungleButtonPtr;
    PanelElement* CommingSoonButtonPtr;
public:
    MapSelectionState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // MAP_SELECTION_STATE_H