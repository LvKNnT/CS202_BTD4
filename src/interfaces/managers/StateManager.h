#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>
#include <string>

#include "../states/StateStack.h"
#include "../states/MainMenuState.h"
#include "../states/MapSelectionState.h"
#include "../states/OptionsState.h"
#include "../states/GameState.h"
#include "../states/AreYouSureState.h"
#include "../states/DifficultySelectionState.h"
#include "../states/SpecificModeSelectionState.h"
#include "../states/GameOverState.h"
#include "../../logic/Map/MapUnits.h"
#include "../../core/IObserver.h"
#include "../../core/Event.h"

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
    std::shared_ptr<State> gameOverState;

    bool canResume;
    std::string mode;
    std::string modeInfo;
    bool isNewGame;
    MapType mapType;

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