#include "StateManager.h"

void StateManager::initialize() {
    mainMenuState = std::make_shared<MainMenuState>();
    mapSelectionState = std::make_shared<MapSelectionState>();
    optionsState = std::make_shared<OptionsState>();
    gameState = std::make_shared<GameState>();
    areYouSureState = std::make_shared<AreYouSureState>();
    modeSelectionState = std::make_shared<ModeSelectionState>();
    easyModeSelectionState = std::make_shared<EasyModeSelectionState>();
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
            stateStack.pushState(modeSelectionState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::ToAreYouSure:
            stateStack.pushState(areYouSureState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::BackHome:
            stateStack.popState();
            stateStack.popState();
            stateStack.popState();
            stateStack.popState();
            stateStack.popState();
            break;
        case Event::Type::ToEasyModeSelection:
            stateStack.pushState(easyModeSelectionState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::ToEasyStandardMode:
            stateStack.pushState(gameState);
            break;
        default:
            stateStack.update(event);
            break;
    }
}

