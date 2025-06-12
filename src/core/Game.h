#ifndef GAME_H
#define GAME_H

#include "../utils/Properties.h"
#include <filesystem>
#include <fstream>
#include "../managers/TextureManager.h"

class Game {
public:
    static Game& Instance();

    Game();
    ~Game();

    void LoadContent();
    void UnloadContent();

    void initialize();
    void render();
    void update(float deltaTime);

    TextureMananger &getTextureManager();

private:
    TextureMananger textureMananger;
    
};

#endif // GAME_H