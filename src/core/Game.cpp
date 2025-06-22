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
    textureManager.loadTexture("Table", "assets/UI/Table.png");
    textureManager.loadTexture("XButton", "assets/UI/XButton.png");
    textureManager.loadTexture("NextButton", "assets/UI/Next.png");
    textureManager.loadTexture("PreviousButton", "assets/UI/Previous.png");
    textureManager.loadTexture("PreviousUpButton", "assets/UI/PreviousUp.png");
    textureManager.loadTexture("NextDownButton", "assets/UI/NextDown.png");
    textureManager.loadTexture("GameStateButton", "assets/UI/GameStateButton.png");
    textureManager.loadTexture("Start", "assets/UI/Start.png");
    textureManager.loadTexture("Setting", "assets/UI/Setting.png");
    textureManager.loadTexture("HP", "assets/UI/HP.png");
    textureManager.loadTexture("Cash", "assets/UI/Cash.png");
    textureManager.loadTexture("Box", "assets/UI/Box.png");
    textureManager.loadTexture("Home", "assets/UI/Home.png");
    textureManager.loadTexture("Tick", "assets/UI/Tick.png");
    textureManager.loadTexture("Untick", "assets/UI/Untick.png");
    textureManager.loadTexture("FastForward", "assets/UI/FastForward.png");
    //Sound
    textureManager.loadTexture("Volume5", "assets/UI/Volume5.png");
    textureManager.loadTexture("Volume4", "assets/UI/Volume4.png");
    textureManager.loadTexture("Volume3", "assets/UI/Volume3.png");
    textureManager.loadTexture("Volume2", "assets/UI/Volume2.png");
    textureManager.loadTexture("Volume1", "assets/UI/Volume1.png");
    textureManager.loadTexture("Volume0", "assets/UI/Volume0.png");
    
    // Load maps
    textureManager.loadTexture("MonkeyLaneThumb", "assets/map/Monkey_lane_thumb.png");
    textureManager.loadTexture("JungleThumb", "assets/map/Jungle_thumb.png");
    textureManager.loadTexture("CommingSoon", "assets/map/CommingSoon.png");
    textureManager.loadTexture("CommingSoon2", "assets/map/CommingSoon2.png");
    textureManager.loadTexture("GameStateBackground", "assets/states/GameStateBackground.jpg");

    // Load fonts
    fontManager.loadFont("Big", "assets/font/Luckiest_Guy/LuckiestGuy-Regular.ttf", 60);
    fontManager.loadFont("Medium-Big", "assets/font/Squada_One/SquadaOne-Regular.ttf", 45);
    fontManager.loadFont("Medium", "assets/font/Squada_One/SquadaOne-Regular.ttf", 30);
    //fontManager.loadFont("Small", "assets/font/Luckiest_Guy/LuckiestGuy-Regular.ttf", 15);
    fontManager.loadFont("Small", "assets/font/Source_Sans_3/static/SourceSans3-Medium.ttf", 20);
    //fontManager.loadFont("SmallBold", "assets/font/Source_Sans_3/assets/font/Source_Sans_3/static/SourceSans3-Bold.ttf", 20);

    // Load tower
    textureManager.loadTexture("DartMonkeyIcon", "assets/tower/Dart_Monkey_Mobile.png");
    textureManager.loadTexture("BombTowerIcon", "assets/tower/Bomb_Tower_2.png");
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
