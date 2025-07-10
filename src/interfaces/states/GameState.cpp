#include "GameState.h"
#include "../../core/Game.h"
#include <fstream>

GameState::GameState() : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb")) { 
    // Temporary only
    Game::Instance().getGameLogic().init();
}

void GameState::draw() const {
    // Temporary only
    Game::Instance().getGameLogic().update();
    Game::Instance().getGameLogic().draw();
}