#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>

#include "../interfaces/states/StateStack.h"
#include "../interfaces/states/MainMenuState.h"
#include "../interfaces/states/MapSelectionState.h"
#include "../interfaces/states/OptionsState.h"
#include "../interfaces/states/GameState.h"
#include "../interfaces/states/AreYouSureState.h"
#include "../interfaces/states/ModeSelectionState.h"
#include "../interfaces/states/EasyModeSelectionState.h"
#include "../core/IObserver.h"
#include "../core/Event.h"

class StateManager : public IObserver {
private:
    StateStack stateStack;
    std::shared_ptr<State> mainMenuState;
    std::shared_ptr<State> mapSelectionState;
    std::shared_ptr<State> gameState;
    std::shared_ptr<State> optionsState;
    std::shared_ptr<State> areYouSureState;
    std::shared_ptr<State> modeSelectionState;
    std::shared_ptr<State> easyModeSelectionState;
    std::shared_ptr<State> mediumModeSelectionState;
    std::shared_ptr<State> hardModeSelectionState;

public:
    void initialize() override;
    void draw() const;
    void handleInput() override;
    void update(Event::Type event) override;
};

#endif // STATE_MANAGER_H