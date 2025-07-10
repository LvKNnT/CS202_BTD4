#ifndef GAME_H
#define GAME_H

#include <memory>

// UI/UX
#include "../managers/TextureManager.h"
#include "../managers/FontManager.h"
#include "../managers/StateManager.h"
#include "../managers/SoundLoader.h"
#include "../managers/SoundManager.h"
#include "../interfaces/states/StateStack.h"
#include "../interfaces/states/MainMenuState.h"
#include "../interfaces/states/LoadingState.h"
#include "IObserver.h"

// Logic
#include "../logic/GameLogic.h"

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
    SoundLoader &getSoundLoader();
    std::shared_ptr<IObserver> getSoundManager();
    std::shared_ptr<IObserver> getStateManager();

    GameLogic &getGameLogic();
private:
    bool exit; // for exit 

    // Managers
    TextureManager textureManager;
    FontManager fontManager;
    SoundLoader soundLoader;
    // pointer for observer pattern
    std::shared_ptr<IObserver> soundManager;
    std::shared_ptr<IObserver> stateManager;    

    GameLogic gameLogic;
};

#endif // GAME_H