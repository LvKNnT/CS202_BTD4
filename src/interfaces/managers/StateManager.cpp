#include "StateManager.h"
#include "../../core/Game.h"

void StateManager::initialize() {
    isNewGame = false;
    mainMenuState = std::make_shared<MainMenuState>();
    mapSelectionState = std::make_shared<MapSelectionState>();
    optionsState = std::make_shared<OptionsState>();
    areYouSureState = std::make_shared<AreYouSureState>();
    difficultySelectionState = std::make_shared<DifficultySelectionState>();
    //specificModeSelectionState = std::make_shared<SpecificModeSelectionState>();
    stateStack.pushState(mainMenuState);
}

void StateManager::draw() const {
    stateStack.draw();
}

void StateManager::handleInput() {
    stateStack.handleInput();
}

void StateManager::update(Event::Type event) {
    switch(event) {
        case Event::Type::ToMapSelection:
            stateStack.pushState(mapSelectionState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::ToOptions:
            stateStack.pushState(optionsState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::CancelCurrentState:
            stateStack.popState();
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::ToMonkeyLane:
            stateStack.pushState(difficultySelectionState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::ToAreYouSure:
            stateStack.pushState(areYouSureState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::BackHome:
            while(stateStack.getSize() > 1) {
                stateStack.popState();
            }
            
            // Reset Game Logic - hmmm maybe because we dont have new game actually
            Game::Instance().getGameLogic().unactiveTickFast();
            break;
        case Event::Type::ToGameState:
            if(isNewGame) gameState = std::make_shared<GameState>();
            stateStack.pushState(gameState);
            break;
        case Event::Type::NewGame:
            isNewGame = true;
            break;
        case Event::Type::Continue: 
            break;
        case Event::Type::Resume:
            stateStack.pushState(gameState);
            break;
        default:
            if(Event::Type::ToEasyModeSelection <= event && event <= Event::Type::ToImpoppableModeSelection) {
                specificModeSelectionState = std::make_shared<SpecificModeSelectionState>();
                stateStack.pushState(specificModeSelectionState);
                stateStack.update(event);
                stateStack.setdrawPreviousStates(true);
                break;
            }
            stateStack.update(event);
            break;
    }
}

void StateManager::setMode(std::string _mode){ 
    mode = _mode;
}

std::string StateManager::getMode() const {
    return mode;
}

void StateManager::setModeInfo(std::string _modeInfo) {
    modeInfo = _modeInfo;
}

std::string StateManager::getModeInfo() const {
    return modeInfo;
}
