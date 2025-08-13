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
            stateStack.pushState(difficultySelectionState);
            stateStack.setdrawPreviousStates(true);
            mapType = MapType::MonkeyLane;
            Game::Instance().getGameLogic().init(MapType::MonkeyLane);
            break;
        case Event::Type::ToJungleLane:
            stateStack.pushState(difficultySelectionState);
            stateStack.setdrawPreviousStates(true);
            mapType = MapType::Jungle;
            Game::Instance().getGameLogic().init(MapType::Jungle);
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
            break;
        case Event::Type::Continue: 
            break;
        case Event::Type::Resume:
            if(canResume) stateStack.pushState(gameState);
            break;
        case Event::Type::StandardMode:
            Game::Instance().getGameLogic().init(ModeType::Classic);
            break;
        case Event::Type::AlternateBloonsMode:
            Game::Instance().getGameLogic().init(ModeType::Alternative);
            break;
        case Event::Type::ReverseMode:
            Game::Instance().getGameLogic().init(static_cast<MapType>(static_cast<int>(mapType) + 1));
            Game::Instance().getGameLogic().init(ModeType::Reverse);
            break;
        case Event::Type::ApopalyseMode:
            Game::Instance().getGameLogic().init(ModeType::Apopalypse);
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
                switch(event) {
                    case Event::Type::ToEasyModeSelection:
                        Game::Instance().getGameLogic().init(Difficulty::Easy);
                        break;
                    case Event::Type::ToMediumModeSelection:
                        Game::Instance().getGameLogic().init(Difficulty::Medium);
                        break;
                    case Event::Type::ToHardModeSelection:
                        Game::Instance().getGameLogic().init(Difficulty::Hard);
                        break;
                    case Event::Type::ToImpoppableModeSelection:
                        Game::Instance().getGameLogic().init(Difficulty::Impoppable);
                        break;
                }
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

void StateManager::setMode(std::string _mode){ 
    mode = _mode;
}

std::string StateManager::getMode() const {
    return mode;
}

void StateManager::setModeInfo(std::string _modeInfo) {
    modeInfo = _modeInfo;
}

std::string StateManager::getModeInfo() const {
    return modeInfo;
}
