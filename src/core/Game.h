#ifndef GAME_H
#define GAME_H

#include <memory>

#include "../managers/TextureManager.h"
#include "../managers/StateManager.h"
#include "../interfaces/states/StateStack.h"
#include "../interfaces/states/MainMenuState.h"
#include "../interfaces/states/LoadingState.h"
#include "IObserver.h"

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

    TextureManager &getTextureManager();
    std::shared_ptr<IObserver> getStateManager();

private:
    // Managers
    TextureManager textureManager;
    std::shared_ptr<IObserver> stateManager;    
};

#endif // GAME_H