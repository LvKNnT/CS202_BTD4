#ifndef MAP_SELECTION_STATE_H
#define MAP_SELECTION_STATE_H

#include "State.h"

class MapSelectionState : public State {
private:
    int curMap;
    static const int maxMap = 6;
    std::shared_ptr<PanelElement> nextMapButton;
    std::shared_ptr<PanelElement> previousMapButton;
    std::shared_ptr<PanelElement> ChooseMapButton[maxMap];
    std::shared_ptr<PanelElement> mapName[maxMap];
public:
    MapSelectionState();
    void draw() const override;
    void update(Event::Type event) override;
};

#endif // MAP_SELECTION_STATE_H