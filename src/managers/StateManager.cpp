#include "StateManager.h"

void StateManager::initialize() {
    mainMenuState = std::make_unique<MainMenuState>();
    mapSelectionState = std::make_unique<MapSelectionState>();
    gameState = std::make_unique<GameState>();
    stateStack.pushState(std::move(mainMenuState));
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
            stateStack.pushState(std::move(mapSelectionState));
            stateStack.setdrawPreviousState(true);
            break;
        case Event::Type::CancelMapSelection:
            mapSelectionState = stateStack.popState();
            break;
        case Event::Type::MoveNext:
            stateStack.update(event);
            break;
        case Event::Type::MovePrevious:
            stateStack.update(event);
            break;
        case Event::Type::MapSelectionToMonkeyLane:
            mapSelectionState = stateStack.popState();
            stateStack.pushState(std::move(gameState));
            break;
    }
}

