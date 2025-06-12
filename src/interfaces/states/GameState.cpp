#include "GameState.h"
#include "../../core/Game.h"

GameState::GameState() : State(Properties::screenHeight, Properties::screenWidth, Game::Instance().getTextureManager().getTexture("MonkeyLaneThumb")) { 
}

void GameState::draw() const {
    DrawTextureEx(background, (Vector2) {0, 0}, 0.0f, 1.0, WHITE);
}