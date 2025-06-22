#include "StateManager.h"

void StateManager::initialize() {
    mainMenuState = std::make_shared<MainMenuState>();
    mapSelectionState = std::make_shared<MapSelectionState>();
    optionsState = std::make_shared<OptionsState>();
    gameState = std::make_shared<GameState>();
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
        case Event::Type::MainMenuToMapSelection:
            stateStack.pushState(mapSelectionState);
            stateStack.setdrawPreviousState(true);
            break;
        case Event::Type::ToOptions:
            stateStack.pushState(optionsState);
            stateStack.setdrawPreviousState(true);
            break;
        case Event::Type::CancelCurrentState:
            stateStack.popState();
            break;
        case Event::Type::MoveNext:
            stateStack.update(event);
            break;
        case Event::Type::MovePrevious:
            stateStack.update(event);
            break;
        case Event::Type::MapSelectionToMonkeyLane:
            stateStack.popState();
            stateStack.pushState(gameState);
            break;
    }
}

