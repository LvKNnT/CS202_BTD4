#include "Game.h"

Game &Game::Instance() {
    static Game instance;
    return instance;
}

Game::Game() {
}

Game::~Game() {
}

void Game::LoadContent() {
    // Load texture
    textureManager.loadTexture("MonkeyLaneThumb", "assets/map/Monkey_lane_thumb.png");
    textureManager.loadTexture("MainMenu", "assets/states/MainMenu.png");
    textureManager.loadTexture("MainMenuButton", "assets/UI/MainMenuButton.png");
    textureManager.loadTexture("MapSelectionBackground", "assets/UI/MapSelectionBackground.png");
    textureManager.loadTexture("XButton", "assets/UI/XButton.png");
    textureManager.loadTexture("NextButton", "assets/UI/Next.png");
    textureManager.loadTexture("PreviousButton", "assets/UI/Previous.png");
}

void Game::UnloadContent() {
    
}

void Game::initialize() {
    stateManager = std::make_shared<StateManager>();
    stateManager->initialize();
}

void Game::render() {
    stateManager->draw();
}

void Game::update(float deltaTime) {
    stateManager->handleInput();
}

TextureManager &Game::getTextureManager() {
    return textureManager;
}

std::shared_ptr<IObserver> Game::getStateManager() {
    return stateManager;
}
