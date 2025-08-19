#include "StateManager.h"
#include "../../core/Game.h"
#include "../audio/MyAudio.h"

StateManager::StateManager()
{
    isNewGame = false;
    canResume = false;
    isLoadingDone = false;
    loadingState = std::make_shared<LoadingState>();
    stateStack.pushState(loadingState);
}

void StateManager::initialize()
{
    mainMenuState = std::make_shared<MainMenuState>();
    mapSelectionState = std::make_shared<MapSelectionState>();
    optionsState = std::make_shared<OptionsState>();
    areYouSureState = std::make_shared<AreYouSureState>();
    difficultySelectionState = std::make_shared<DifficultySelectionState>();
    gameOverState = std::make_shared<GameOverState>();
    victoryState = std::make_shared<VictoryState>();
    heroSelectionState = std::make_shared<HeroSelectionState>();
    stateStack.pushState(mainMenuState);
}

void StateManager::draw() const {
    stateStack.draw();
}

void StateManager::handleInput() {
    stateStack.handleInput();
    if(!isLoadingDone && Game::Instance().isLoadingDone()) {
        isLoadingDone = true;
        stateStack.popState();
        initialize();
    }
}

void StateManager::update(Event::Type event) {
    // Initialize sound
    MySound victorySound("Victory");
    MySound gameOverSound("GameOver");
    MySound secretVictorySound("SugoiSugoi");

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
            setMap(MapType::MonkeyLane);
            if(isNewGame) {
                stateStack.pushState(difficultySelectionState);
                stateStack.setdrawPreviousStates(true);
                Game::Instance().getGameLogic().init(mapType);
            }
            if(isContinue && Game::Instance().getGameLogic().canLoadGame(mapType)) {
                canResume = true;
                Game::Instance().getGameLogic().loadGame(mapType);
                gameState = std::make_shared<GameState>();
                stateStack.pushState(gameState);
            }
            break;
        case Event::Type::ToJungleLane:
            setMap(MapType::Jungle);
            if(isNewGame) {
                stateStack.pushState(difficultySelectionState);
                stateStack.setdrawPreviousStates(true);
                Game::Instance().getGameLogic().init(mapType);
            }
            if(isContinue && Game::Instance().getGameLogic().canLoadGame(mapType)) {
                canResume = true;
                Game::Instance().getGameLogic().loadGame(mapType);
                gameState = std::make_shared<GameState>();
                stateStack.pushState(gameState);
            }
            break;
        case Event::Type::ToRinkRevenge:
            setMap(MapType::RinkRevenge);
            if(isNewGame) {
                stateStack.pushState(difficultySelectionState);
                stateStack.setdrawPreviousStates(true);
                Game::Instance().getGameLogic().init(mapType);
            }
            if(isContinue && Game::Instance().getGameLogic().canLoadGame(mapType)) {
                canResume = true;
                Game::Instance().getGameLogic().loadGame(mapType);
                gameState = std::make_shared<GameState>();
                stateStack.pushState(gameState);
            }
            break;
        case Event::Type::ToDuneSea:
            setMap(MapType::DuneSea);
            if(isNewGame) {
                stateStack.pushState(difficultySelectionState);
                stateStack.setdrawPreviousStates(true);
                Game::Instance().getGameLogic().init(mapType);
            }
            if(isContinue && Game::Instance().getGameLogic().canLoadGame(mapType)) {
                canResume = true;
                Game::Instance().getGameLogic().loadGame(mapType);
                gameState = std::make_shared<GameState>();
                stateStack.pushState(gameState);
            }
            break;
        case Event::Type::ToAttackOnBloon:
            setMap(MapType::AttackOnBloon);
            if(isNewGame) {
                stateStack.pushState(difficultySelectionState);
                stateStack.setdrawPreviousStates(true);
                Game::Instance().getGameLogic().init(mapType);
            }
            if(isContinue && Game::Instance().getGameLogic().canLoadGame(mapType)) {
                canResume = true;
                Game::Instance().getGameLogic().loadGame(mapType);
                gameState = std::make_shared<GameState>();
                stateStack.pushState(gameState);
            }
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
            canResume = true;
            if(isNewGame) gameState = std::make_shared<GameState>();
            stateStack.pushState(gameState);
            break;
        case Event::Type::NewGame:
            isNewGame = true;
            isContinue = false;
            break;
        case Event::Type::Continue:
            isContinue = true;
            isNewGame = false;
            Game::Instance().getGameLogic().loadAutoSave();
            break;
        case Event::Type::Resume:
            if(canResume) stateStack.pushState(gameState);
            break;
        case Event::Type::StandardMode:
            setMode(ModeType::Classic);
            Game::Instance().getGameLogic().init(ModeType::Classic);
            break;
        case Event::Type::AlternateBloonsMode:
            setMode(ModeType::Alternative);
            Game::Instance().getGameLogic().init(ModeType::Alternative);
            break;
        case Event::Type::ReverseMode:
            setMode(ModeType::Reverse);
            Game::Instance().getGameLogic().init(static_cast<MapType>(static_cast<int>(mapType) + 1));
            Game::Instance().getGameLogic().init(ModeType::Reverse);
            break;
        case Event::Type::ApopalyseMode:
            setMode(ModeType::Apopalypse);
            Game::Instance().getGameLogic().init(ModeType::Apopalypse);
            break;
        case Event::Type::ToHeroSelection:
            stateStack.pushState(heroSelectionState);
            stateStack.setdrawPreviousStates(true);
            break;
        case Event::Type::ClickedQuincy:
            Game::Instance().getGameLogic().init(HeroType::Quincy);
            break;
        case Event::Type::ClickedBenjamin:
            Game::Instance().getGameLogic().init(HeroType::Benjamin);
            break;
        case Event::Type::ClickedRosalia:
            Game::Instance().getGameLogic().init(HeroType::Rosalia);
            break;
        case Event::Type::ClickedEtienne:
            Game::Instance().getGameLogic().init(HeroType::Etienne);
            break;
        case Event::Type::ToGameOver:
            canResume = false;
            stateStack.pushState(gameOverState);
            stateStack.setdrawPreviousStates(true);
            gameOverSound.start();
            break;
        case Event::Type::ToVictory:
            canResume = false;
            stateStack.pushState(victoryState);
            stateStack.setdrawPreviousStates(true);
            if(Utils::rand(1, 100) > 5) victorySound.start();
            else secretVictorySound.start(); 
            break;
        case Event::Type::Replay:
            stateStack.popState();
            Game::Instance().getGameLogic().replay();
            break;
        case Event::Type::StartRound:
            Game::Instance().getGameLogic().startPlayRound();
            break;
        default:
            if(Event::Type::ToEasyModeSelection <= event && event <= Event::Type::ToImpoppableModeSelection) {
                stateStack.update(event);
                Game::Instance().getGameLogic().init(difficultyType);
                specificModeSelectionState = std::make_shared<SpecificModeSelectionState>();
                stateStack.pushState(specificModeSelectionState);
                stateStack.setdrawPreviousStates(true);
                break;
            }
            stateStack.update(event);
            break;
    }
}

void StateManager::setMap(MapType _mapType) {
    mapType = _mapType;
}

MapType StateManager::getMap() const {
    return mapType;
}

void StateManager::setDifficulty(Difficulty _difficultyType) {
    difficultyType = _difficultyType;
}

Difficulty StateManager::getDifficulty() const {
    return difficultyType;
}

void StateManager::setMode(ModeType _modeType) {
    modeType = _modeType;
}

ModeType StateManager::getMode() const {
    return modeType;
}

bool StateManager::canLoadGame(MapType mapType) const {
    return isContinue && Game::Instance().getGameLogic().canLoadGame(mapType);
}
