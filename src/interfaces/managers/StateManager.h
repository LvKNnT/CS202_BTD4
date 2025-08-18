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
#include "../states/VictoryState.h"
#include "../states/LoadingState.h"
#include "../states/HeroSelectionState.h"
#include "../../logic/Map/MapUnits.h"
#include "../../logic/mode/ModeUnits.h"
#include "../../logic/level/DifficultyUnits.h"
#include "../IObserver.h"
#include "../Event.h"

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
    std::shared_ptr<State> victoryState;
    std::shared_ptr<State> loadingState;
    std::shared_ptr<State> heroSelectionState;

    ModeType modeType;
    Difficulty difficultyType;
    MapType mapType;

    bool canResume;
    bool isNewGame;
    bool isContinue;
    bool isLoadingDone;

public:
    StateManager();
    void initialize();
    void draw() const;
    void handleInput();
    void update(Event::Type event) override;
    
    void setMap(MapType _mapType);
    MapType getMap() const;
    void setDifficulty(Difficulty _difficultyType);
    Difficulty getDifficulty() const;
    void setMode(ModeType _modeType);
    ModeType getMode() const;

    bool canLoadGame(MapType mapType) const;
};

#endif // STATE_MANAGER_H