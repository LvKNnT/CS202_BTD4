#ifndef HERO_SELECTION_STATE_H
#define HERO_SELECTION_STATE_H

#include <string>

#include "../../logic/hero/HeroUnits.h"
#include "State.h"

class HeroSelectionState : public State {
public:
    HeroSelectionState();
    void draw() const override;
    void update(Event::Type event) override;
    void handleInput() override;

private:
    std::shared_ptr<PanelElement> quincyButton;
    std::shared_ptr<PanelElement> benjaminButton;
    std::shared_ptr<PanelElement> rosaliaButton;
    std::shared_ptr<PanelElement> etienneButton;
    std::shared_ptr<PanelElement> heroInfoText;
};

#endif // HERO_SELECTION_STATE_H