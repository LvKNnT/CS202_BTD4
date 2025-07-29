#include "Game.h"

Game &Game::Instance() {
    static Game instance;
    return instance;
}

Game::Game() : exit(false) {
    audioManager = std::make_unique<AudioManager>();
}

Game::~Game() {
}

void Game::LoadContent() {
    loadTexture();
    loadFont();
    loadSound();
}

void Game::loadTexture() {
        // Load UI
    textureManager.loadTexture("MainMenu", "../assets/states/MainMenu.png");
    textureManager.loadTexture("MainMenuButton", "../assets/UI/MainMenuButton.png");
    textureManager.loadTexture("Table", "../assets/UI/Table.png");
    textureManager.loadTexture("XButton", "../assets/UI/XButton.png");
    textureManager.loadTexture("NextButton", "../assets/UI/Next.png");
    textureManager.loadTexture("PreviousButton", "../assets/UI/Previous.png");
    textureManager.loadTexture("PreviousUpButton", "../assets/UI/PreviousUp.png");
    textureManager.loadTexture("NextDownButton", "../assets/UI/NextDown.png");
    textureManager.loadTexture("GameStateButton", "../assets/UI/GameStateButton.png");
    textureManager.loadTexture("Start", "../assets/UI/Start.png");
    textureManager.loadTexture("Setting", "../assets/UI/Setting.png");
    textureManager.loadTexture("HP", "../assets/UI/HP.png");
    textureManager.loadTexture("Cash", "../assets/UI/Cash.png");
    textureManager.loadTexture("Box", "../assets/UI/Box.png");
    textureManager.loadTexture("Home", "../assets/UI/Home.png");
    textureManager.loadTexture("Tick", "../assets/UI/Tick.png");
    textureManager.loadTexture("Untick", "../assets/UI/Untick.png");
    textureManager.loadTexture("FastForward", "../assets/UI/FastForward.png");
    textureManager.loadTexture("OkButton", "../assets/UI/OkButton.png");
    textureManager.loadTexture("Play", "../assets/UI/Play.png");
    textureManager.loadTexture("PurpleRect", "../assets/UI/PurpleRect.png");
    textureManager.loadTexture("LeftWhiteTriangle", "../assets/UI/LeftWhiteTriangle.png");
    textureManager.loadTexture("RightWhiteTriangle", "../assets/UI/RightWhiteTriangle.png");
    textureManager.loadTexture("RedRect", "../assets/UI/RedRect.png");
    textureManager.loadTexture("GreenRect", "../assets/UI/GreenRect.png");
    textureManager.loadTexture("GreyRect", "../assets/UI/GreyRect.png");
    textureManager.loadTexture("Info", "../assets/UI/Info.png");
    
    //Sound
    textureManager.loadTexture("Volume100", "../assets/UI/Volume100.png");
    textureManager.loadTexture("Volume80", "../assets/UI/Volume80.png");
    textureManager.loadTexture("Volume60", "../assets/UI/Volume60.png");
    textureManager.loadTexture("Volume40", "../assets/UI/Volume40.png");
    textureManager.loadTexture("Volume20", "../assets/UI/Volume20.png");
    textureManager.loadTexture("Volume0", "../assets/UI/Volume0.png");
    
    // Load maps
    textureManager.loadTexture("MonkeyLaneThumb", "../assets/map/Monkey_lane_thumb.png");
    textureManager.loadTexture("JungleThumb", "../assets/map/Jungle_thumb.png");
    textureManager.loadTexture("CommingSoon", "../assets/map/CommingSoon.png");
    textureManager.loadTexture("CommingSoon2", "../assets/map/CommingSoon2.png");
    textureManager.loadTexture("GameStateBackground", "../assets/states/GameStateBackground.png");

    // Load tower
    textureManager.loadTexture("Dart Monkey Icon", "../assets/tower/Dart_Monkey_Mobile.png");
    textureManager.loadTexture("Bomb Tower Icon", "../assets/tower/Bomb_Tower_2.png");
    textureManager.loadTexture("Dart Monkey Info", "../assets/tower/Dart_Monkey/000-DartMonkey.png");
    textureManager.loadTexture("CrossbowMasterUpgradeIcon", "../assets/tower/Dart_Monkey/CrossbowMasterUpgradeIcon.png");
    textureManager.loadTexture("Sharp Shots Upgrade Icon", "../assets/tower/Dart_Monkey/SharpShotsUpgradeIcon.png");

    // Load mode icons
    textureManager.loadTexture("Easy", "../assets/mode/Easy.png");
    textureManager.loadTexture("Medium", "../assets/mode/Medium.png");
    textureManager.loadTexture("Hard", "../assets/mode/Hard.png");
    textureManager.loadTexture("Standard", "../assets/mode/Standard.png");
    textureManager.loadTexture("Reverse", "../assets/mode/Reverse.png");
    textureManager.loadTexture("AlternateBloons", "../assets/mode/AlternateBloons.png");
    textureManager.loadTexture("Impoppable", "../assets/mode/Impoppable.png");
    textureManager.loadTexture("Apopalyse", "../assets/mode/Apopalypse.png");
}

void Game::loadFont() {
    // Load fonts
    fontManager.loadFont("Big", "../assets/font/Luckiest_Guy/LuckiestGuy-Regular.ttf", 60);
    fontManager.loadFont("Medium-Big", "../assets/font/Squada_One/SquadaOne-Regular.ttf", 45);
    fontManager.loadFont("Medium", "../assets/font/Squada_One/SquadaOne-Regular.ttf", 30);
    //fontManager.loadFont("Small", "../assets/font/Luckiest_Guy/LuckiestGuy-Regular.ttf", 15);
    fontManager.loadFont("SmallBold", "../assets/font/Luckiest_Guy/LuckiestGuy-Regular.ttf", 20);
    fontManager.loadFont("Small", "../assets/font/Source_Sans_3/static/SourceSans3-Medium.ttf", 20);
    fontManager.loadFont("SupperSmallBold", "../assets/font/Source_Sans_3/static/SourceSans3-Bold.ttf", 20);
    fontManager.loadFont("SuperSmall", "../assets/font/Source_Sans_3/static/SourceSans3-Medium.ttf", 15);
    //fontManager.loadFont("SmallBold", "../assets/font/Source_Sans_3/../assets/font/Source_Sans_3/static/SourceSans3-Bold.ttf", 20);
}

void Game::loadSound() {
    // for loadSound() we need to pass number of maxSounds or default will be 1 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("Kuru Kuru", "../assets/sounds/music/Kuru Kururin.wav", 2); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadMusic("Kuru Kuru", "../assets/sounds/music/Kuru Kururin.wav");
}

void Game::UnloadContent() {
    textureManager.unloadContent();
    fontManager.unloadContent();
    std::static_pointer_cast<AudioManager>(audioManager)->unload();
    gameLogic.unLoad();
}

void Game::initialize() {
    stateManager = std::make_unique<StateManager>();
    std::static_pointer_cast<StateManager>(stateManager)->initialize();
    std::static_pointer_cast<AudioManager>(audioManager)->initialize();
}

void Game::render() {
    std::static_pointer_cast<StateManager>(stateManager)->draw();
}

void Game::update(float deltaTime) {
    std::static_pointer_cast<StateManager>(stateManager)->handleInput();
    std::static_pointer_cast<AudioManager>(audioManager)->updateMusic();
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

std::shared_ptr<IObserver> Game::getAudioManager() {
    return audioManager;
}

std::shared_ptr<IObserver> Game::getStateManager() {
    return stateManager;
}

GameLogic &Game::getGameLogic() {
    return gameLogic;
}
