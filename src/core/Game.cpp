#include "Game.h"

Game &Game::Instance() {
    static Game instance;
    return instance;
}

Game::Game() {
}

Game::~Game()
{
}

void Game::LoadContent() {
    // Since the assets path is fixed, we can load all textures here
    // Temporary disable loading of textures from the assets path

    // for (const auto& file : std::filesystem::recursive_directory_iterator(Properties::assets_path)) {
    //     if (file.is_regular_file() && file.path().extension() != ".md") {
    //         std::string textureName = file.path().stem().string();
    //         std::string texturePath = file.path().string();
            
    //         textureMananger.loadTexture(textureName, texturePath);

    //         // log
    //         std::fstream logFile("../logs/log.txt", std::ios::app | std::ios::out);
    //         logFile << "Loaded texture: " << textureName << " from " << texturePath << "\n";
    //         logFile.close();
    //     }
    // }
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
