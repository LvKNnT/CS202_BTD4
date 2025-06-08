#include "Game.h"

Game &Game::Instance() {
    static Game instance;
    return instance;
}

Game::Game() {
    textureMananger.loadTexture("MonkeyLaneThumb", "assets/map/Monkey_lane_thumb.png");
}

Game::~Game()
{
}

void Game::LoadContent() {
}

void Game::UnloadContent() {

}

void Game::initialize()
{
}

void Game::render()
{
}

TextureMananger &Game::getTextureManager() {
    return textureMananger;
}
