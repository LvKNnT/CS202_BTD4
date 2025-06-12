#include "Game.h"

Game &Game::Instance() {
    static Game instance;
    return instance;
}

Game::Game() : exit(false) {
}

Game::~Game() {
}

void Game::LoadContent() {
    // Load UI
    textureManager.loadTexture("MainMenu", "assets/states/MainMenu.png");
    textureManager.loadTexture("MainMenuButton", "assets/UI/MainMenuButton.png");
    textureManager.loadTexture("MapSelectionBackground", "assets/UI/MapSelectionBackground.png");
    textureManager.loadTexture("XButton", "assets/UI/XButton.png");
    textureManager.loadTexture("NextButton", "assets/UI/Next.png");
    textureManager.loadTexture("PreviousButton", "assets/UI/Previous.png");
    
    // Load maps
    textureManager.loadTexture("MonkeyLaneThumb", "assets/map/Monkey_lane_thumb.png");
    textureManager.loadTexture("JungleThumb", "assets/map/Jungle_thumb.png");
    textureManager.loadTexture("CommingSoon", "assets/map/CommingSoon.png");
    textureManager.loadTexture("CommingSoon2", "assets/map/CommingSoon2.png");

    // Load fonts
    fontManager.loadFont("Big", "assets/font/Luckiest_Guy/LuckiestGuy-Regular.ttf", 60);
    fontManager.loadFont("Medium", "assets/font/Squada_One/SquadaOne-Regular.ttf", 30);
    fontManager.loadFont("Small", "assets/font/Source_Sans_3/SourceSans3-VariableFont_wght.ttf", 15);
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

void Game::requestExit() {
    exit = true;
}

bool Game::isExit() const {
    return exit;
}

TextureManager &Game::getTextureManager() {
    return textureManager;
}

FontManager &Game::getFontManager() {
    return fontManager;
}

std::shared_ptr<IObserver> Game::getStateManager() {
    return stateManager;
}
