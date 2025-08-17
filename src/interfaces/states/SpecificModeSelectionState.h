#ifndef SPECIFIC_MODE_SELECTION_STATE_H
#define SPECIFIC_MODE_SELECTION_STATE_H

#include <string>

#include "../../logic/level/DifficultyUnits.h"
#include "State.h"

class SpecificModeSelectionState : public State {
public:
    SpecificModeSelectionState();
    void draw() const override;
    void update(Event::Type event) override;
    void handleInput() override;
    
private:
    std::shared_ptr<PanelElement> modeInfoText;
    std::shared_ptr<PanelElement> alternateBloonsButton;
    std::shared_ptr<PanelElement> reverseButton;
    std::shared_ptr<PanelElement> apopalyseButton;
    std::shared_ptr<PanelElement> title;
    
    void setInfo();
};

#endif // SPECIFIC_MODE_SELECTION_STATE_H