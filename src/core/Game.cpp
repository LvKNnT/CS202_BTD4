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

void Game::loadLoadingStateContent() {
    textureManager.loadTexture("LoadingStateBackground", "../assets/states/LoadingScreen.png");
    fontManager.loadFont("LoadingStateFont", "../assets/font/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf", 30);
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadMusic("BTD5Theme", "../assets/sounds/music/Jazz Theme - Bloons TD 5.mp3"); 
}

void Game::LoadContent()
{
    loadTexture();
    loadTowerTexture();
    loadFont();
    loadSound();
    loadAnimationTexture();
    loadingDone = true;
}

void Game::loadTexture() {
    // Load UI
    textureManager.loadTextureDraw("MainMenu", "../assets/states/MainMenu.png");
    textureManager.loadTextureDraw("MainMenuButton", "../assets/UI/MainMenuButton.png");
    textureManager.loadTextureDraw("Table", "../assets/UI/Table.png");
    textureManager.loadTextureDraw("XButton", "../assets/UI/XButton.png");
    textureManager.loadTextureDraw("NextButton", "../assets/UI/Next.png");
    textureManager.loadTextureDraw("PreviousButton", "../assets/UI/Previous.png");
    textureManager.loadTextureDraw("PreviousUpButton", "../assets/UI/PreviousUp.png");
    textureManager.loadTextureDraw("NextDownButton", "../assets/UI/NextDown.png");
    textureManager.loadTextureDraw("GameStateButton", "../assets/UI/GameStateButton.png");
    textureManager.loadTextureDraw("Start", "../assets/UI/Start.png");
    textureManager.loadTextureDraw("Setting", "../assets/UI/Setting.png");
    textureManager.loadTextureDraw("Replay", "../assets/UI/Replay.png");
    textureManager.loadTextureDraw("HP", "../assets/UI/HP.png");
    textureManager.loadTextureDraw("Cash", "../assets/UI/Cash.png");
    textureManager.loadTextureDraw("Box", "../assets/UI/Box.png");
    textureManager.loadTextureDraw("Home", "../assets/UI/Home.png");
    textureManager.loadTextureDraw("Tick", "../assets/UI/Tick.png");
    textureManager.loadTextureDraw("Untick", "../assets/UI/Untick.png");
    textureManager.loadTextureDraw("FastForward", "../assets/UI/FastForward.png");
    textureManager.loadTextureDraw("OkButton", "../assets/UI/OkButton.png");
    textureManager.loadTextureDraw("Play", "../assets/UI/Play.png");
    textureManager.loadTextureDraw("PurpleRect", "../assets/UI/PurpleRect.png");
    textureManager.loadTextureDraw("LeftWhiteTriangle", "../assets/UI/LeftWhiteTriangle.png");
    textureManager.loadTextureDraw("RightWhiteTriangle", "../assets/UI/RightWhiteTriangle.png");
    textureManager.loadTextureDraw("RedRect", "../assets/UI/RedRect.png");
    textureManager.loadTextureDraw("GreenRect", "../assets/UI/GreenRect.png");
    textureManager.loadTextureDraw("GreyRect", "../assets/UI/GreyRect.png");
    textureManager.loadTextureDraw("Info", "../assets/UI/Info.png");
    textureManager.loadTextureDraw("Victory", "../assets/UI/Victory.png");
    textureManager.loadTextureDraw("GameOver", "../assets/UI/GameOver.png");
    
    
    //Sound
    textureManager.loadTextureDraw("Volume100", "../assets/UI/Volume100.png");
    textureManager.loadTextureDraw("Volume80", "../assets/UI/Volume80.png");
    textureManager.loadTextureDraw("Volume60", "../assets/UI/Volume60.png");
    textureManager.loadTextureDraw("Volume40", "../assets/UI/Volume40.png");
    textureManager.loadTextureDraw("Volume20", "../assets/UI/Volume20.png");
    textureManager.loadTextureDraw("Volume0", "../assets/UI/Volume0.png");
    
    // Load maps
    textureManager.loadTextureDraw("MonkeyLaneThumb", "../assets/map/Monkey_lane_thumb.png");
    textureManager.loadTextureDraw("JungleThumb", "../assets/map/Jungle_thumb.png");
    textureManager.loadTextureDraw("CommingSoon", "../assets/map/CommingSoon.png");
    textureManager.loadTextureDraw("CommingSoon2", "../assets/map/CommingSoon2.png");
    textureManager.loadTextureDraw("GameStateBackground", "../assets/states/GameStateBackground.png");

    // Load mode icons
    textureManager.loadTextureDraw("Easy", "../assets/mode/Easy.png");
    textureManager.loadTextureDraw("Medium", "../assets/mode/Medium.png");
    textureManager.loadTextureDraw("Hard", "../assets/mode/Hard.png");
    textureManager.loadTextureDraw("Standard", "../assets/mode/Standard.png");
    textureManager.loadTextureDraw("Reverse", "../assets/mode/Reverse.png");
    textureManager.loadTextureDraw("AlternateBloons", "../assets/mode/AlternateBloons.png");
    textureManager.loadTextureDraw("Impoppable", "../assets/mode/Impoppable.png");
    textureManager.loadTextureDraw("Apopalyse", "../assets/mode/Apopalypse.png");
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
    drawLoadingScren();
}

void Game::loadSound() {
    // for loadSound() we need to pass number of maxSounds or default will be 1 

    // SFX
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("NormalBloon", "../assets/sounds/sfx/NormalBloon.wav", 20); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("CeramicBloon", "../assets/sounds/sfx/CeramicBloon.wav", 10); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("PurpleBloon", "../assets/sounds/sfx/PurpleBloon.wav", 10); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("LeadBloon", "../assets/sounds/sfx/LeadBloon.wav", 10); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("MOABBloon", "../assets/sounds/sfx/MOABBloon.wav", 10); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("DestroyingMOABBloon", "../assets/sounds/sfx/DestroyingMOABBloon.wav", 1); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("Cash", "../assets/sounds/sfx/Cash.wav"); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("Placing", "../assets/sounds/sfx/PLacing.wav"); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("Upgrade", "../assets/sounds/sfx/Upgrade.wav"); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("Victory", "../assets/sounds/sfx/Victory.wav"); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("GameOver", "../assets/sounds/sfx/GameOver.wav"); 
    std::dynamic_pointer_cast<AudioManager>(audioManager)->loadSound("SugoiSugoi", "../assets/sounds/sfx/Sugoi Sugoi!.wav"); 
    
    // Music
    drawLoadingScren();
}

void Game::loadTowerTexture() {
     // Load tower
    textureManager.loadTextureDraw("Dart Monkey Icon", "../assets/tower/Dart_Monkey_Mobile.png");
    textureManager.loadTextureDraw("Bomb Shooter Icon", "../assets/tower/Boom_Shooter/Bomb_Shooter.png");
    textureManager.loadTextureDraw("Ninja Monkey Icon", "../assets/tower/Ninja_Monkey/Ninja_Monkey.png");
    textureManager.loadTextureDraw("Dart Monkey Info", "../assets/tower/Dart_Monkey/000-DartMonkey.png");
    textureManager.loadTextureDraw("Bomb Shooter Info", "../assets/tower/Boom_Shooter/Bomb_Shooter_Icon.png");
    textureManager.loadTextureDraw("Ninja Monkey Info", "../assets/tower/Ninja_Monkey/BTD6_Ninja_Monkey.png");
    textureManager.loadTextureDraw("CrossbowMasterUpgradeIcon", "../assets/tower/Dart_Monkey/CrossbowMasterUpgradeIcon.png");
    textureManager.loadTextureDraw("Sharp Shots Upgrade Icon", "../assets/tower/Dart_Monkey/SharpShotsUpgradeIcon.png");
}

void Game::loadAnimationTexture() {
    // Load all animation textures
    drawLoadingScren();
}

void Game::drawLoadingScren() {
    Game::Instance().render();
    BeginDrawing();
    EndDrawing();
}

void Game::UnloadContent() {
    textureManager.unloadContent();
    fontManager.unloadContent();
    std::static_pointer_cast<AudioManager>(audioManager)->unload();
    gameLogic.unLoad();
}

void Game::initialize() {
    stateManager = std::make_unique<StateManager>();
    //std::static_pointer_cast<StateManager>(stateManager)->initialize();
    std::static_pointer_cast<AudioManager>(audioManager)->initialize();
    MyMusic gameTheme("BTD5Theme");
    gameTheme.start();
}

void Game::render() {
    std::static_pointer_cast<StateManager>(stateManager)->draw();
}

void Game::update(float deltaTime) {
    std::static_pointer_cast<StateManager>(stateManager)->handleInput();
    std::static_pointer_cast<AudioManager>(audioManager)->updateMusic();
    animationManager.update();
}

void Game::requestExit() {
    exit = true;
}

bool Game::isExit() const {
    return exit;
}

bool Game::isLoadingDone() const {
    return loadingDone;
}

TextureManager &Game::getTextureManager() {
    return textureManager;
}

AnimationManager &Game::getAnimationManager() {
    return animationManager;
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
