#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <string>

#include "../interfaces/states/StateStack.h"
#include "../interfaces/states/MainMenuState.h"
#include "../interfaces/states/MapSelectionState.h"
#include "../interfaces/states/OptionsState.h"
#include "../interfaces/states/GameState.h"
#include "../interfaces/states/AreYouSureState.h"
#include "../interfaces/states/DifficultySelectionState.h"
#include "../interfaces/states/SpecificModeSelectionState.h"
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
    std::shared_ptr<State> difficultySelectionState;
    std::shared_ptr<State> specificModeSelectionState;

private:
    std::string mode;
    std::string modeInfo;
    bool isNewGame;

public:
    void initialize();
    void draw() const;
    void handleInput();
    void update(Event::Type event) override;
    
    void setMode(std::string _mode);
    std::string getMode() const;
    void setModeInfo(std::string _modeInfo);
    std::string getModeInfo() const;
};

#endif // STATE_MANAGER_H