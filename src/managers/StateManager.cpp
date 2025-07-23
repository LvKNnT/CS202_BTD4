#include "StateManager.h"

void StateManager::initialize() {
    mainMenuState = std::make_shared<MainMenuState>();
    mapSelectionState = std::make_shared<MapSelectionState>();
    optionsState = std::make_shared<OptionsState>();
    gameState = std::make_shared<GameState>();
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
            break;
        case Event::Type::ToGameState:
            stateStack.pushState(gameState);
            break;
        case Event::Type::NewGame:
            gameState = std::make_shared<GameState>();
            break;
        case Event::Type::Continue: 
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

