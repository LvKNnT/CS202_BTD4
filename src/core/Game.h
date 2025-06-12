#ifndef GAME_H
#define GAME_H

#include <memory>

#include "../managers/TextureManager.h"
#include "../managers/FontManager.h"
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
    void requestExit();
    bool isExit() const;

    TextureManager &getTextureManager();
    FontManager &getFontManager();
    std::shared_ptr<IObserver> getStateManager();
private:
    bool exit; // for exit 

    // Managers
    TextureManager textureManager;
    FontManager fontManager;
    // pointer for observer pattern
    std::shared_ptr<IObserver> stateManager;    
};

#endif // GAME_H