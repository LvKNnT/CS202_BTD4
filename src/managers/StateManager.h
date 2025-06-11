#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>

#include "../interfaces/states/StateStack.h"
#include "../interfaces/states/MainMenuState.h"
#include "../interfaces/states/MapSelectionState.h"
#include "../core/IObserver.h"
#include "../core/Event.h"

class StateManager : public IObserver {
private:
    StateStack stateStack;
    std::unique_ptr<State> mainMenuState;
    std::unique_ptr<State> mapSelectionState;

public:
    void initialize() override;
    void draw() const override;
    void handleInput() override;
    void update(Event::Type event) override;
};

#endif // STATE_MANAGER_H